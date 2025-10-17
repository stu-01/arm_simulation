#pragma once

#include <arm5dof_target_detect/msg/detail/target_detect__struct.hpp>
#include <arm5dof_target_detect/msg/target_detect.hpp>
#include <cv_bridge/cv_bridge.h>
#include <geometry_msgs/msg/point.hpp>
#include <geometry_msgs/msg/point_stamped.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/opencv.hpp>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <sensor_msgs/msg/camera_info.hpp>

using namespace std::chrono_literals;

// 定义HSV颜色范围的结构体
struct ColorRange {
  cv::Scalar lower;
  cv::Scalar upper;
  std::string name;
  cv::Scalar drawColor; // 绘制时用的BGR颜色
};

// 获取对应颜色的掩膜并绘制轮廓和标签
cv::Point detectColor(const cv::Mat &hsv, cv::Mat &output,
                      const ColorRange &colorRange);

float get_depth(cv::Point centroid,cv::Mat &latest_depth_image_);

class ColorNode : public rclcpp::Node {
private:
  void timer_callback();
  void image_callback(const sensor_msgs::msg::Image::SharedPtr image_msg);
  void depth_callback(const sensor_msgs::msg::Image::SharedPtr depth_msg);
  rclcpp::Publisher<arm5dof_target_detect::msg::TargetDetect>::SharedPtr
      publisher_;
  rclcpp::TimerBase::SharedPtr timer_;

  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_subscriber_;
  cv::Point centroid_out_red1;
  cv::Point centroid_out_red2;
  cv::Point centroid_out_blue;
  cv::Point centroid_out_green;
  float depth_red1;
  float depth_red2;
  float depth_blue;
  float depth_green;
  geometry_msgs::msg::PointStamped final_position_red1;
  geometry_msgs::msg::PointStamped final_position_red2;
  geometry_msgs::msg::PointStamped final_position_blue;
  geometry_msgs::msg::PointStamped final_position_green;

  std::mutex depth_mutex_;
  const cv::Mat latest_depth_image_;
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr depth_subscriber_;

  rclcpp::Subscription<sensor_msgs::msg::CameraInfo>::SharedPtr info_subscriber_;
  sensor_msgs::msg::CameraInfo camera_info_;

public:
  ColorNode();

  geometry_msgs::msg::PointStamped final_position(cv::Point &centroid,float &depth_z);
};