#include "../include/arm5dof_movegroup/move_group.hpp"
#include <geometry_msgs/msg/detail/point__struct.hpp>

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);

  auto node = std::make_shared<MoveNode>();

  auto const logger = rclcpp::get_logger("target_detect_move_group");

  auto executor = rclcpp::executors::SingleThreadedExecutor();
  executor.add_node(node);

  using ::moveit::planning_interface::MoveGroupInterface;
  auto move_group_interface = MoveGroupInterface(node, "arm5dof");

  auto const red_target_pose = [&]() {
    geometry_msgs::msg::Pose pose;
    pose.orientation.w = 1.0;
    pose.position.x = node->getRedTarget().point.x;
    pose.position.y = node->getRedTarget().point.y;
    pose.position.z = node->getRedTarget().point.z;
    return pose;
  }();

  auto const blue_target_pose = [&]() {
    geometry_msgs::msg::Pose pose;
    pose.orientation.w = 1.0;
    pose.position.x = node->getBlueTarget().point.x;
    pose.position.y = node->getBlueTarget().point.y;
    pose.position.z = node->getBlueTarget().point.z;
    return pose;
  }();

  auto const green_target_pose = [&]() {
    geometry_msgs::msg::Pose pose;
    pose.orientation.w = 1.0;
    pose.position.x = node->getGreenTarget().point.x;
    pose.position.y = node->getGreenTarget().point.y;
    pose.position.z = node->getGreenTarget().point.z;
    return pose;
  }();

  move_group_interface.setPoseTarget(red_target_pose);

  auto const [success, plan] = [&move_group_interface]() {
    MoveGroupInterface::Plan msg;
    auto const ok = static_cast<bool>(move_group_interface.plan(msg));
    return std::make_pair(ok, msg);
  }();

  if (success) {
    move_group_interface.execute(plan);
  } else {
    RCLCPP_ERROR(logger, "planning failed!");
  }
  // if(!success){
  //     RCLCPP_ERROR(logger,"planning failed!");
  // }

  rclcpp::shutdown();
  return 0;
}