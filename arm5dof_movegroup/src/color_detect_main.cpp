#include "../include/arm5dof_movegroup/color_detect.hpp"
#include <chrono>
#include <iostream>
#include <memory>
int main(int argc, char **argv) {
  // 检查输入参数
  rclcpp::init(argc, argv);


  // 定义颜色范围（HSV）


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
  // rclcpp::spin(std::make_shared<ColorNode>());

  cap.release();
  cv::destroyAllWindows();
  rclcpp::shutdown();
  return 0;
}
