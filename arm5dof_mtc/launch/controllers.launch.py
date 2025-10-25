import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import Command, FindExecutable, PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():
    robot_name = "arm5dof"
    description_package='arm5dof_moveit_config'
    description_file='arm5dof.urdf.xacro'

# 加载机器人描述文件，并将其设置为参数
    robot_description_content = Command(
        [
            PathJoinSubstitution([FindExecutable(name="xacro")]),
            " ",
            PathJoinSubstitution(
                [FindPackageShare(description_package),"config",description_file]
                # [FindPackageShare(description_package), "urdf", description_file]
            ),
        ]
    )

    robot_description = {"robot_description": robot_description_content}

    static_tf = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        name='static_transform_publisher',
        output='both',
        arguments=['0', '0', '0', '0', '0', '0', 'world', 'base_link'], # x y z roll pitch yaw frame_id child_frame_id
    )

    robot_state_publisher_node = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        output="both",
        parameters=[robot_description],
    )

    # ros2_control using FakeSystem as hardware
    ros2_controllers_path = os.path.join(
        get_package_share_directory("arm5dof_moveit_config"),
        "config",
        "ros2_controllers.yaml",
    )

    ros2_control_node = Node(
        package="controller_manager",
        executable="ros2_control_node",
        parameters=[ros2_controllers_path],
        remappings=[
            ("/controller_manager/robot_description", "/robot_description"),
        ],
        output="both",
    )

    
    joint_state_broadcaster_spawner = Node(package='controller_manager', executable='spawner',
                              arguments=["joint_state_broadcaster","-c", "/controller_manager"],)
    
    arm_controller_spawner = Node(package='controller_manager', executable='spawner',
                              arguments=["arm_controller","-c", "/controller_manager"],)
    
    hand_controller_spawner = Node(package='controller_manager', executable='spawner',
                              arguments=["hand_controller","-c", "/controller_manager"],)

    return LaunchDescription(
        [
            static_tf,
            robot_state_publisher_node,
            ros2_control_node,
            joint_state_broadcaster_spawner,
            arm_controller_spawner,
            hand_controller_spawner,
        ]
    )