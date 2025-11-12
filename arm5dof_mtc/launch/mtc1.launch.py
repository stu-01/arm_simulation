# 对应mtc1.cpp
import os
from ament_index_python.packages import get_package_share_directory
from launch.actions import ExecuteProcess
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from moveit_configs_utils import MoveItConfigsBuilder
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument, RegisterEventHandler
from launch.conditions import IfCondition
from launch.event_handlers import OnProcessExit
from launch.substitutions import Command, FindExecutable, PathJoinSubstitution, LaunchConfiguration
from launch_ros.substitutions import FindPackageShare

# 加载了两次move_group节点，大概会出错

def generate_launch_description():
    robot_name = "arm5dof"
    description_package='arm5dof_moveit_config'
    description_file='arm5dof.urdf.xacro'
    
    # arm5dof = IncludeLaunchDescription(
    #             PythonLaunchDescriptionSource([os.path.join(
    #                 get_package_share_directory(package_name),'launch','arm5dof.launch.py'
    #             )]), launch_arguments={'use_sim_time': 'true'}.items()
    # )

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

    # 加载moveit配置
    moveit_config = (MoveItConfigsBuilder(robot_name)
                    #  _moveit_config为什么这里不能写package_name="arm5dof_moveit_config"？
    .robot_description(file_path="config/arm5dof.urdf.xacro")
    .trajectory_execution(file_path="config/moveit_controllers.yaml")
    .planning_pipelines(
        pipelines=["ompl", "chomp", "pilz_industrial_motion_planner"]
    )).to_moveit_configs()


    move_group_capabilities = {
        "capabilities": "move_group/ExecuteTaskSolutionCapability"
    }

    moveit = IncludeLaunchDescription(
                PythonLaunchDescriptionSource([os.path.join(
                    get_package_share_directory(description_package),'launch','demo.launch.py'
                )]), launch_arguments={'use_sim_time': 'true'}.items()
    )
        # RViz
    # rviz_config_file = (
    #     get_package_share_directory("arm5dof_mtc") + "/launch/mtc.rviz"
    # )
    # rviz_node = Node(
    #     package="rviz2",
    #     executable="rviz2",
    #     output="log",
    #     arguments=["-d", rviz_config_file],
    #     parameters=[
    #         moveit_config.robot_description,
    #         moveit_config.robot_description_semantic,
    #         moveit_config.robot_description_kinematics,
    #     ],
    # )


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

    joint_state_broadcaster = Node(package='controller_manager', executable='spawner',
                              arguments=["joint_state_broadcaster","-c", "/controller_manager"],)
    
    arm_controller = Node(package='controller_manager', executable='spawner',
                              arguments=["arm_controller","-c", "/controller_manager"],)
    
    hand_controller = Node(package='controller_manager', executable='spawner',
                              arguments=["hand_controller","-c", "/controller_manager"],)
    
    arm_hand_controller = Node(package='controller_manager', executable='spawner',
                              arguments=["arm_hand_controller","-c", "/controller_manager"],)

    run_move_group_node = Node(
        package="arm5dof_mtc",
        executable="arm5dof_mtc1",
        output="screen",
        parameters=[
            moveit_config.to_dict(),
            move_group_capabilities,
        ],
    )
    
    return LaunchDescription(
        [
            moveit,
            # rviz_node,
            # static_tf,
            # robot_state_publisher,
            # robot_state_publisher_node,
            run_move_group_node,
            # ros2_control_node,
            # joint_state_broadcaster,
            # arm_controller,
            # hand_controller,
            # arm_hand_controller,
        ]
    )