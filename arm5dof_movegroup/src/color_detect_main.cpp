#include "../include/arm5dof_movegroup/color_detect.hpp"
#include <memory>

int main(int argc, char **argv) {
  // 检查输入参数
  rclcpp::init(argc, argv);
  auto node = std::make_shared<ColorNode>();
  rclcpp::spin(node);
  cv::destroyAllWindows();
  rclcpp::shutdown();
  return 0;
}
