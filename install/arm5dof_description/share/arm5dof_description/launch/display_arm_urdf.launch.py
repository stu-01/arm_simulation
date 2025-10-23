

import os
# 获取包的路径
from ament_index_python.packages import get_package_share_directory
# Launch相关的配置
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    # 获取arm5dof_description包所在的路径
    pkg_path = get_package_share_directory('arm5dof_description')
    print(f"pkg_path: {pkg_path}")
    # URDF模型的路径
    arm_urdf_path = f"{pkg_path}/urdf/arm5dof_ros.urdf" 
    print("arm_urdf_path")
    print(arm_urdf_path)
    # RVIZ2配置文件路径
    rviz2_config_path = f"{pkg_path}/rviz/display_arm_urdf.rviz" 
    
    # RVIZ2可视化
    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        arguments=['-d', rviz2_config_path],
        output='screen')
    
    # 关节状态发布者
    joint_state_publisher_gui_node = Node(
        package='joint_state_publisher_gui',
        executable='joint_state_publisher_gui',
        name='joint_state_publisher_gui',
        output='screen')
    
    # 机器人状态发布者
    robot_state_publisher_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        output='screen',
        arguments=[arm_urdf_path])
    
    # 创建Launch的描述文件
    ld = LaunchDescription()
    ld.add_action(rviz_node)
    ld.add_action(joint_state_publisher_gui_node)
    ld.add_action(robot_state_publisher_node)
    return ld