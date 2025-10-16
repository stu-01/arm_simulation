#pragma once

#include <arm5dof_target_detect/msg/detail/target_detect__struct.hpp>
#include <arm5dof_target_detect/msg/target_detect.hpp>
#include <chrono>
#include <geometry_msgs/msg/point.hpp>
#include <iostream>
#include <memory>
#include <opencv2/core/types.hpp>
#include <opencv2/opencv.hpp>
#include <rclcpp/rclcpp.hpp>

using namespace std::chrono_literals;

// 定义HSV颜色范围的结构体
struct ColorRange {
  cv::Scalar lower;
  cv::Scalar upper;
  std::string name;
  cv::Scalar drawColor; // 绘制时用的BGR颜色
};

// 获取对应颜色的掩膜并绘制轮廓和标签
void detectColor(const cv::Mat &hsv, cv::Mat &output,
                 const ColorRange &colorRange) {
  cv::Mat mask;
  inRange(hsv, colorRange.lower, colorRange.upper, mask);

  // 去噪（可选）
  GaussianBlur(mask, mask, cv::Size(5, 5), 0);

  std::vector<std::vector<cv::Point>> contours;
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
    auto msg = arm5dof_target_detect::msg::TargetDetect();
    msg.red_target_point.x = (double)this->red_target.x;
    msg.red_target_point.y = (double)this->red_target.y;
    msg.blue_target_point.x = (double)this->blue_target.x;
    msg.blue_target_point.y = (double)this->blue_target.y;
    msg.green_target_point.x = (double)this->green_target.x;
    msg.green_target_point.y = (double)this->green_target.y; // 你消息里的字段
    publisher_->publish(msg);
  }

  rclcpp::Publisher<arm5dof_target_detect::msg::TargetDetect>::SharedPtr
      publisher_;
  rclcpp::TimerBase::SharedPtr timer_;

  cv::Point red_target;
  cv::Point blue_target;
  cv::Point green_target;

public:
  ColorNode(cv::Point red, cv::Point blue, cv::Point green)
      : Node("detect_node") {
    this->red_target = red;
    this->blue_target = blue;
    this->green_target = green;

    publisher_ =
        this->create_publisher<arm5dof_target_detect::msg::TargetDetect>(
            "detect_topic", 10);

    timer_ =
        this->create_wall_timer(std::chrono::milliseconds(500),
                                std::bind(&ColorNode::timer_callback, this));
  }
};