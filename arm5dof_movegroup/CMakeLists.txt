cmake_minimum_required(VERSION 3.8)
project(arm5dof_movegroup)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(moveit_ros_planning_interface REQUIRED)
find_package(moveit_visual_tools REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(OpenCV REQUIRED)
find_package(arm5dof_target_detect REQUIRED)
find_package(geometry_msgs)

include_directories(
  ${OpenCV_INCLUDE_DIRS}
)

# 颜色识别节点
add_executable(color_node src/color_detect.cpp src/color_detect_main.cpp)
add_executable(move_group src/move_group.cpp src/move_group_main.cpp)

ament_target_dependencies(color_node
  ament_cmake
  rclcpp
  moveit_ros_planning_interface
  moveit_visual_tools
  rclcpp_action
  arm5dof_target_detect
  geometry_msgs
)

ament_target_dependencies(move_group
  ament_cmake
  rclcpp
  moveit_ros_planning_interface
  moveit_visual_tools
  rclcpp_action
  arm5dof_target_detect
  geometry_msgs
)

target_link_libraries(color_node ${OpenCV_LIBRARIES})
target_link_libraries(move_group ${OpenCV_LIBRARIES})

install(TARGETS
color_node 
move_group
DESTINATION lib/${PROJECT_NAME}
)


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
