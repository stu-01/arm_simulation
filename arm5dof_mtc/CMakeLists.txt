cmake_minimum_required(VERSION 3.8)
project(arm5dof_mtc)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(moveit_task_constructor_core REQUIRED)
find_package(rclcpp REQUIRED)
find_package(moveit_core REQUIRED)
find_package(moveit_ros_planning REQUIRED)
find_package(moveit_ros_planning_interface REQUIRED)

add_executable(arm5dof_mtc src/mtc.cpp src/main.cpp)

ament_target_dependencies(arm5dof_mtc
  ament_cmake
  moveit_task_constructor_core
  rclcpp
  moveit_core
  moveit_ros_planning
  moveit_ros_planning_interface
)

target_include_directories(arm5dof_mtc PRIVATE
  include
  # 确保包含 MoveIt 的头文件路径
  ${moveit_core_INCLUDE_DIRS}
  ${moveit_ros_planning_interface_INCLUDE_DIRS}
)

install(TARGETS
  arm5dof_mtc
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
