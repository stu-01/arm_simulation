#include <chrono>
#include <iostream>
#include <memory>
#include <opencv2/opencv.hpp>
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/point.hpp>

using namespace std;
using namespace std::chrono_literals;

// 定义HSV颜色范围的结构体
struct ColorRange {
  cv::Scalar lower;
  cv::Scalar upper;
  string name;
  cv::Scalar drawColor; // 绘制时用的BGR颜色
};

// 获取对应颜色的掩膜并绘制轮廓和标签
void detectColor(const cv::Mat &hsv, cv::Mat &output,
                 const ColorRange &colorRange) {
  cv::Mat mask;
  inRange(hsv, colorRange.lower, colorRange.upper, mask);

  // 去噪（可选）
  GaussianBlur(mask, mask, cv::Size(5, 5), 0);

  vector<vector<cv::Point>> contours;
  findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

  for (size_t i = 0; i < contours.size(); ++i) {
    double area = contourArea(contours[i]);
    if (area > 500) { // 忽略太小的噪声轮廓
      cv::Rect rect = boundingRect(contours[i]);
      rectangle(output, rect, colorRange.drawColor, 2);
      putText(output, colorRange.name, cv::Point(rect.x, rect.y - 5),
              cv::FONT_HERSHEY_SIMPLEX, 0.6, colorRange.drawColor, 2);
    }
  }
}

class ColorNode : public rclcpp::Node {
private:
  void timer_callback() {
    // auto msg = arm5dof_movegroup::msg::ColorDetect();
    // msg.color = "red"; // 你消息里的字段
    // publisher_->publish(msg);
  }
  // rclcpp::Publisher<arm5dof_movegroup::msg::ColorDetect>::SharedPtr publisher_;
  // rclcpp::TimerBase::SharedPtr timer_;

   void timer_callback()
  {
    auto msg = block::msg::ColorDetect();
    msg.color = "red";   // 你消息里的字段
    publisher_->publish(msg);
  }

  rclcpp::Publisher<arm5dof_movegroup::msg::ColorDetect>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;

public:
  ColorNode() : Node("color_node")
  {
    publisher_ = this->create_publisher<arm5dof_movegroup::msg::ColorDetect>("color_topic", 10);
    timer_ = this->create_wall_timer(
      std::chrono::milliseconds(500),
      std::bind(&ColorNode::timer_callback, this)
    );
  }
};

int main(int argc, char **argv) {
  // 检查输入参数
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ColorNode>());
  if (argc < 2) {
    cout << "请提供视频文件路径，如：./color_detect video.mp4" << endl;
    return -1;
  }

  // 打开视频
  cv::VideoCapture cap(argv[1]);
  if (!cap.isOpened()) {
    cout << "无法打开视频文件：" << argv[1] << endl;
    return -1;
  }

  // 定义颜色范围（HSV）
  vector<ColorRange> colorRanges = {
      // 红色有两个范围（环形），这里只示例一个范围
      {cv::Scalar(0, 120, 70), cv::Scalar(10, 255, 255), "Red",
       cv::Scalar(0, 0, 255)},
      // 蓝色
      {cv::Scalar(100, 150, 70), cv::Scalar(130, 255, 255), "Blue",
       cv::Scalar(255, 0, 0)},
      // 绿色
      {cv::Scalar(40, 70, 70), cv::Scalar(80, 255, 255), "Green",
       cv::Scalar(0, 255, 0)}};

  cv::Mat frame;
  while (true) {
    cap >> frame;
    if (frame.empty())
      break;

    cv::Mat hsv;
    cvtColor(frame, hsv, cv::COLOR_BGR2HSV);

    cv::Mat result = frame.clone();

    for (const auto &colorRange : colorRanges) {
      detectColor(hsv, result, colorRange);
    }

    imshow("Color Detection", result);
    if (cv::waitKey(30) == 27)
      break; // 按 ESC 退出
  }

  cap.release();
  cv::destroyAllWindows();
  rclcpp::shutdown();
  return 0;
}
