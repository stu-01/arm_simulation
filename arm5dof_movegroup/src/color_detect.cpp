#include "../include/arm5dof_movegroup/color_detect.hpp"
#include <opencv2/core/mat.hpp>

cv::Point detectColor(const cv::Mat &hsv, cv::Mat &output,
                 const ColorRange &colorRange) {
  cv::Mat mask;
  inRange(hsv, colorRange.lower, colorRange.upper, mask);

  GaussianBlur(mask, mask, cv::Size(5, 5), 0);

  std::vector<std::vector<cv::Point>> contours;
  findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

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

        return centroid_out;
      }
    }
  }
}

  void ColorNode::timer_callback() {
    auto target_msg = arm5dof_target_detect::msg::TargetDetect();
    target_msg.red_target_point.x = (double)this->red_target.x;
    target_msg.red_target_point.y = (double)this->red_target.y;
    target_msg.blue_target_point.x = (double)this->blue_target.x;
    target_msg.blue_target_point.y = (double)this->blue_target.y;
    target_msg.green_target_point.x = (double)this->green_target.x;
    target_msg.green_target_point.y =
        (double)this->green_target.y; // 你消息里的字段
    publisher_->publish(target_msg);
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
      RCLCPP_ERROR(this->get_logger(), "Depth cv_bridge exception: %s",
                   e.what());
    }
  };
  ColorNode::ColorNode(cv::Point red, cv::Point blue, cv::Point green)
      : Node("detect_node") {

    this->red_target = red;
    this->blue_target = blue;
    this->green_target = green;

    image_subscriber_ = this->create_subscription<sensor_msgs::msg::Image>(
        "camera/image_raw", 10,
        std::bind(&ColorNode::image_callback, this, std::placeholders::_1));

    depth_subscriber_ = this->create_subscription<sensor_msgs::msg::Image>(
        "arm_camera/depth/image_raw", 10,
        std::bind(&ColorNode::depth_callback, this, std::placeholders::_1));

    publisher_ =
        this->create_publisher<arm5dof_target_detect::msg::TargetDetect>(
            "detect_topic", 10);

    timer_ =
        this->create_wall_timer(std::chrono::milliseconds(500),
                                std::bind(&ColorNode::timer_callback, this));
  }
