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

    # 加载moveit配置
    moveit_config = (MoveItConfigsBuilder(robot_name)
    .robot_description(file_path="config/arm5dof.urdf.xacro")
    .trajectory_execution(file_path="config/moveit_controllers.yaml")
    .planning_pipelines(
        pipelines=["ompl", "chomp", "pilz_industrial_motion_planner"]
    )).to_moveit_configs()


    move_group_capabilities = {
        "capabilities": "move_group/ExecuteTaskSolutionCapability"
    }

    # moveit = IncludeLaunchDescription(
    #             PythonLaunchDescriptionSource([os.path.join(
    #                 get_package_share_directory(description_package),'launch','demo.launch.py'
    #             )]), launch_arguments={'use_sim_time': 'true'}.items()
    # )

    move_group_node = Node(
        package="moveit_ros_move_group",
        executable="move_group",
        output="screen",
        parameters=[moveit_config.to_dict(),
                    move_group_capabilities],
        arguments=["--ros-args", "--log-level", "info"],
    )

        # RViz
    rviz_config_file = (
        get_package_share_directory("arm5dof_mtc") + "/launch/mtc.rviz"
    )
    rviz_node = Node(
        package="rviz2",
        executable="rviz2",
        output="log",
        arguments=["-d", rviz_config_file],
        parameters=[
            moveit_config.robot_description,
            moveit_config.robot_description_semantic,
            moveit_config.robot_description_kinematics,
        ],
    )

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

    run_move_group_node = Node(
        package="arm5dof_mtc",
        executable="arm5dof_mtc",
        output="screen",
        parameters=[
            moveit_config.to_dict(),
            move_group_capabilities,
        ],
    )
    
# Step 1: 确保 ROS 2 Control 启动后，启动第一个 Spawner
    launch_step_1 = RegisterEventHandler(
        OnProcessExit(
            target_action=ros2_control_node,
            on_exit=[joint_state_broadcaster_spawner],
        )
    )

    # Step 2: 确保 Joint State Broadcaster 启动后，启动第二个 Spawner
    launch_step_2 = RegisterEventHandler(
        OnProcessExit(
            target_action=joint_state_broadcaster_spawner,
            on_exit=[arm_controller_spawner],
        )
    )

    # Step 3: 确保 Arm Controller 启动后，启动最后一个 Spawner
    launch_step_3 = RegisterEventHandler(
        OnProcessExit(
            target_action=arm_controller_spawner,
            on_exit=[hand_controller_spawner],
        )
    )

    # Step 4: 确保最后一个控制器 (hand_controller) 启动后，启动 MoveGroup 和 MTC 任务
    launch_step_4 = RegisterEventHandler(
        OnProcessExit(
            target_action=hand_controller_spawner, # <--- 您的代码片段在这里
            on_exit=[
                move_group_node,        # 启动 MoveGroup
                rviz_node,              # 启动 Rviz (因为它依赖 MoveGroup 的配置)
                run_move_group_node,    # 启动 MTC 任务
            ]
        )
    )

    
    # ------------------ 6. Launch Description Return ------------------
    return LaunchDescription(
        [
            # 基础节点 (必须立即启动)
            static_tf, 
            robot_state_publisher_node, 

            # ROS 2 Control 核心 (必须立即启动)
            ros2_control_node,
            
            # 启动顺序控制
            launch_step_1,
            launch_step_2,
            launch_step_3,
            launch_step_4,
        ]
    )

    # return LaunchDescription(
    #     [
    #         moveit,
    #         # rviz_node,
    #         # static_tf,
    #         # robot_state_publisher,
    #         # robot_state_publisher_node,
    #         run_move_group_node,
    #         # ros2_control_node,
    #         # joint_state_broadcaster,
    #         # arm_controller,
    #         # hand_controller,
    #         # arm_hand_controller,
    #     ]
    # )