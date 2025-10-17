#include "../include/arm5dof_movegroup/color_detect.hpp"
#include <opencv2/core/mat.hpp>

// 再创建订阅者，订阅camera_info，
// 在回调函数中得到相机的内参矩阵，
// 再写一个全局函数计算相机坐标系的坐标，再计算世界坐标系的坐标，
// 在image_callback调用该函数，转换成ROS2信息
// 由publisher发布

cv::Point detectColor(const cv::Mat &hsv, cv::Mat &output,
                      const ColorRange &colorRange) {
  cv::Mat mask;
  inRange(hsv, colorRange.lower, colorRange.upper, mask);

  GaussianBlur(mask, mask, cv::Size(5, 5), 0);

  std::vector<std::vector<cv::Point>> contours;
  findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

  cv::Point centroid_out;

  for (size_t i = 0; i < contours.size(); ++i) {
    double area = contourArea(contours[i]);
    if (area > 500) { // 忽略太小的噪声轮廓

      // 2. 【核心】计算矩 (Moments)
      cv::Moments M = cv::moments(contours[i]);

      // 3. 检查零阶矩 M.m00 是否非零，以防除以零
      if (M.m00 > 0) {

        // 4. 【核心】计算质心坐标 (Centroid)
        int cx = static_cast<int>(M.m10 / M.m00);
        int cy = static_cast<int>(M.m01 / M.m00);

        // 5. 将找到的质心赋值给输出参数
        // 注意：这里只取第一个满足面积要求的轮廓的质心
        cv::Point centroid_out = cv::Point(cx, cy);

        cv::Rect rect = boundingRect(contours[i]);
        rectangle(output, rect, colorRange.drawColor, 2);
        putText(output, colorRange.name, cv::Point(rect.x, rect.y - 5),
                cv::FONT_HERSHEY_SIMPLEX, 0.6, colorRange.drawColor, 2);

        // 绘制质心点
        cv::circle(output, centroid_out, 5, colorRange.drawColor, -1);
      }
    }
  }
  return centroid_out;
}

float get_depth(cv::Point &centroid, const cv::Mat &latest_depth_image_) {
  const int window_size = 5;
  const int half_size = window_size / 2; // 2

  float sum_depth = 0.0f;
  int valid_pixel_count = 0;

  // 2. 遍历质心周围的像素区域
  for (int i = -half_size; i <= half_size; ++i) {
    for (int j = -half_size; j <= half_size; ++j) {

      // 计算当前采样的像素坐标
      int current_u = centroid.x + j;
      int current_v = centroid.y + i;

      // 检查坐标是否在深度图像的有效范围内 (边界检查)
      if (current_u >= 0 && current_u < latest_depth_image_.cols &&
          current_v >= 0 && current_v < latest_depth_image_.rows) {
        // 假设深度图像编码是 32FC1 (32-bit float)
        float depth_value = latest_depth_image_.at<float>(current_v, current_u);

        // 3. 【关键】过滤无效/零深度值
        // 零值通常表示“没有数据”或“太近/太远”，应该被忽略
        if (depth_value > 0.05 &&
            depth_value < 10.0) // 假设物块距离在 5cm 到 10m 之间
        {
          sum_depth += depth_value;
          valid_pixel_count++;
        }
      }
    }
  }

  // 4. 计算平均深度
  float average_depth_z = 0.0f;
  if (valid_pixel_count > 0) {
    average_depth_z = sum_depth / valid_pixel_count;
    std::cout << "Average Depth (Z) at centroid:" << average_depth_z
              << "m (from " << valid_pixel_count << "valid pixels)"
              << std::endl;

  } else {
    std::cout << "Could not find valid depth data around the centroid."
              << std::endl;
  }

  return average_depth_z;
}

geometry_msgs::msg::PointStamped ColorNode::final_position(cv::Point &centroid,
                                                           float &depth_z) {
  // 在 image_callback 中读取这些值
  if (camera_info_.k.size() < 9) {
    RCLCPP_WARN(this->get_logger(), "Camera info not fully loaded.");
    return geometry_msgs::msg::PointStamped();
  }
  double fx = camera_info_.k[0]; // 焦距 X
  double fy = camera_info_.k[4]; // 焦距 Y
  double cx = camera_info_.k[2]; // 光心 X
  double cy = camera_info_.k[5]; // 光心 Y

  // 假设 centroid_u, centroid_v 是轮廓的质心像素坐标
  // 假设 depth_z 是经过平均和过滤后的深度值 (单位: 米)

  // 1. 像素到相机坐标系的 X, Y 转换公式
  // X_c = (u - c_x) * Z_c / f_x
  // Y_c = (v - c_y) * Z_c / f_y
  // Z_c = depth_z

  double X_c = (centroid.x - cx) * depth_z / fx;
  double Y_c = (centroid.y - cy) * depth_z / fy;
  double Z_c = depth_z; // 相机坐标系的 Z 轴就是测得的深度

  // 2. 将结果存储为 ROS 2 TF 库的 PointStamped 类型 (相机坐标系下的点)
  geometry_msgs::msg::PointStamped camera_point;
  camera_point.header.frame_id =
      camera_info_.header
          .frame_id; // 通常是 "camera_link" 或 "camera_optical_link"
  camera_point.header.stamp = this->now();
  camera_point.point.x = X_c;
  camera_point.point.y = Y_c;
  camera_point.point.z = Z_c;

   return camera_point;
}

void ColorNode::image_callback(
    const sensor_msgs::msg::Image::SharedPtr image_msg) {
  cv_bridge::CvImagePtr cv_ptr;
  cv_ptr = cv_bridge::toCvCopy(image_msg, sensor_msgs::image_encodings::BGR8);
  cv::Mat frame = cv_ptr->image;
  cv::Mat hsv;
  cv::Mat output = frame.clone();
  cvtColor(frame, hsv, cv::COLOR_BGR2HSV);
  std::vector<ColorRange> colorRanges = {
      // 红色有两个范围
      {cv::Scalar(0, 120, 70), cv::Scalar(10, 255, 255), "Red",
       cv::Scalar(0, 0, 255)},
      {cv::Scalar(0, 120, 70), cv::Scalar(10, 255, 255), "Red",
       cv::Scalar(0, 0, 255)},
      // 蓝色
      {cv::Scalar(100, 150, 70), cv::Scalar(130, 255, 255), "Blue",
       cv::Scalar(255, 0, 0)},
      // 绿色
      {cv::Scalar(40, 70, 70), cv::Scalar(80, 255, 255), "Green",
       cv::Scalar(0, 255, 0)}};
  this->centroid_out_red1 = detectColor(hsv, output, colorRanges[0]);
  this->centroid_out_red2 = detectColor(hsv, output, colorRanges[1]);
  this->centroid_out_blue = detectColor(hsv, output, colorRanges[2]);
  this->centroid_out_green = detectColor(hsv, output, colorRanges[3]);

  this->depth_red1 =
      get_depth(this->centroid_out_red1, this->latest_depth_image_);
  this->depth_red2 =
      get_depth(this->centroid_out_red2, this->latest_depth_image_);
  this->depth_blue =
      get_depth(this->centroid_out_blue, this->latest_depth_image_);
  this->depth_green =
      get_depth(this->centroid_out_green, this->latest_depth_image_);

  this->final_position_red1 =
      final_position(this->centroid_out_red1, this->depth_red1);
  this->final_position_red2 =
      final_position(this->centroid_out_red2, this->depth_red2);
  this->final_position_blue =
      final_position(this->centroid_out_blue, this->depth_blue);
  this->final_position_green =
      final_position(this->centroid_out_green, this->depth_green);

  cv::imshow("Color Detection", output);
  cv::waitKey(1); // 需要调用以更新窗口
}

void ColorNode::depth_callback(
    const sensor_msgs::msg::Image::SharedPtr depth_msg) {
  //
  std::lock_guard<std::mutex> lock(depth_mutex_);
  // 在 ColorNode.hpp 中声明成员变量来缓存深度图像
  cv::Mat latest_depth_image_;
  // 使用 cv_bridge 转换深度图像
  cv_bridge::CvImagePtr cv_ptr;
  // Gazebo 深度图像通常是 32-bit float (32FC1) 或 16-bit unsigned (16UC1)
  // 编码
  try {
    cv_ptr = cv_bridge::toCvCopy(depth_msg, depth_msg->encoding);
    // 使用锁保护，防止在读取时被修改 (对于 ROS2
    // 来说，通常不是严格必需的，但好的实践)
    latest_depth_image_ = cv_ptr->image.clone();
  } catch (cv_bridge::Exception &e) {
    RCLCPP_ERROR(this->get_logger(), "Depth cv_bridge exception: %s", e.what());
  }
};

void ColorNode::timer_callback() {
  arm5dof_target_detect::msg::TargetDetect msg;
  msg.final_position_red1 = this->final_position_red1;
  msg.final_position_red2 = this->final_position_red2; 
  msg.final_position_blue = this->final_position_blue;
  msg.final_position_green = this->final_position_green;
  publisher_->publish(msg);
}

ColorNode::ColorNode()
    : Node("detect_node") {

  image_subscriber_ = this->create_subscription<sensor_msgs::msg::Image>(
      "camera/image_raw", 10,
      std::bind(&ColorNode::image_callback, this, std::placeholders::_1));

  depth_subscriber_ = this->create_subscription<sensor_msgs::msg::Image>(
      "arm_camera/depth/image_raw", 10,
      std::bind(&ColorNode::depth_callback, this, std::placeholders::_1));

  info_subscriber_ = this->create_subscription<sensor_msgs::msg::CameraInfo>(
      "arm_camera/camera_info", 1,
      [this](const sensor_msgs::msg::CameraInfo::SharedPtr camera_info_msg) {
        // 简单地缓存内参，通常只需要订阅一次
        this->camera_info_ = *camera_info_msg;
        this->info_subscriber_.reset(); // 订阅一次后即停止，防止重复处理
      });

  publisher_ = this->create_publisher<arm5dof_target_detect::msg::TargetDetect>(
      "detect_topic", 10);

  timer_ = this->create_wall_timer(std::chrono::milliseconds(500),
                                   std::bind(&ColorNode::timer_callback, this));
}
