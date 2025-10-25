import os
from ament_index_python.packages import get_package_share_directory
from launch.actions import ExecuteProcess
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, RegisterEventHandler
from launch.launch_description_sources import PythonLaunchDescriptionSource
from moveit_configs_utils import MoveItConfigsBuilder
from launch_ros.actions import Node
from launch.event_handlers import OnProcessExit
from launch.substitutions import Command, FindExecutable, PathJoinSubstitution, LaunchConfiguration
from launch_ros.substitutions import FindPackageShare

# 在3的基础上更改了rviz文件的路径，但应该是没有效果
# 有“/”不能在描述路径中使用，程序运行失败，还没有改

def generate_launch_description():
    robot_name = "arm5dof"
    description_package='arm5dof_moveit_config'
    description_file='arm5dof.urdf.xacro'
    
    # ------------------ 1. Robot Description Loading ------------------
    # Generate the robot description (URDF/XACRO) content
    robot_description_content = Command(
        [
            PathJoinSubstitution([FindExecutable(name="xacro")]),
            " ",
            PathJoinSubstitution(
                [FindPackageShare(description_package), "config", description_file]
            ),
        ]
    )
    robot_description = {"robot_description": robot_description_content}

    # ------------------ 2. MoveIt Configuration Loading ------------------
    # Use consistent path finding for MoveIt configs
    moveit_config = (MoveItConfigsBuilder(robot_name, package_name=description_package)
    .robot_description(file_path=PathJoinSubstitution([FindPackageShare(description_package), "config", "arm5dof.urdf.xacro"]))
    .trajectory_execution(file_path=PathJoinSubstitution([FindPackageShare(description_package), "config", "moveit_controllers.yaml"]))
    .planning_pipelines(
        pipelines=["ompl", "chomp", "pilz_industrial_motion_planner"]
    )
    # Add other necessary config files (SRDF, kinematics, planning) using package paths
    .to_moveit_configs()
    )

    # ------------------ 3. Essential Robot Nodes ------------------
    static_tf = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        name='static_transform_publisher',
        output='both',
        # world -> base_link transform
        arguments=['0', '0', '0', '0', '0', '0', 'world', 'base_link'], 
    )

    robot_state_publisher_node = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        output="both",
        parameters=[robot_description],
    )

    # ------------------ 4. ROS 2 Control Setup ------------------
    ros2_controllers_path = PathJoinSubstitution([FindPackageShare(description_package), "config", "ros2_controllers.yaml"])

    ros2_control_node = Node(
        package="controller_manager",
        executable="ros2_control_node",
        parameters=[ros2_controllers_path],
        remappings=[
            ("/controller_manager/robot_description", "/robot_description"),
        ],
        output="both",
    )

    # Spawners MUST be launched AFTER ros2_control_node is ready.
    # We use RegisterEventHandler to ensure correct startup order.
    
    # Spawner for joint_state_broadcaster
    joint_state_broadcaster_spawner = Node(package='controller_manager', executable='spawner',
                              arguments=["joint_state_broadcaster", "-c", "/controller_manager"],)
    
    # Spawner for arm_controller
    arm_controller_spawner = Node(package='controller_manager', executable='spawner',
                              arguments=["arm_controller", "-c", "/controller_manager"],)
    
    # Spawner for hand_controller
    hand_controller_spawner = Node(package='controller_manager', executable='spawner',
                              arguments=["hand_controller", "-c", "/controller_manager"],)


    # ------------------ 5. MoveGroup Node ------------------
    # Explicitly launch the MoveGroup node (from MoveIt)
    move_group_node = Node(
        package="moveit_ros_move_group",
        executable="move_group",
        output="screen",
        parameters=[moveit_config.to_dict()],
        arguments=["--ros-args", "--log-level", "info"],
    )

    # ------------------ 6. Rviz Node ------------------
    rviz_config_file = PathJoinSubstitution([FindPackageShare(description_package), "config", "moveit.rviz"])
    rviz_node = Node(
        package="rviz2",
        executable="rviz2",
        output="log",
        arguments=["-d", rviz_config_file],
        parameters=[
            moveit_config.robot_description,
            moveit_config.robot_description_semantic,
            moveit_config.robot_description_kinematics,
            moveit_config.planning_pipelines,
            moveit_config.joint_limits,
        ],
    )


    # ------------------ 7. MTC Task Node ------------------
    # The actual Multi-Task/MTC node
    run_move_group_node = Node(
        package="arm5dof_mtc",
        executable="arm5dof_mtc",
        output="screen",
        parameters=[
            moveit_config.to_dict(),
            # Required capability for MTC execution
            {"move_group/capabilities": "move_group/ExecuteTaskSolutionCapability"},
        ],
    )
    
    return LaunchDescription(
        [
            # 1. Base Robot Components
            static_tf,
            robot_state_publisher_node,

            # 2. ROS 2 Control (Execution)
            ros2_control_node,
            
            # 3. Controller Spawners (Need to wait for ros2_control_node)
            RegisterEventHandler(
                OnProcessExit(
                    target_action=ros2_control_node,
                    on_exit=[joint_state_broadcaster_spawner],
                )
            ),
            RegisterEventHandler(
                OnProcessExit(
                    target_action=joint_state_broadcaster_spawner,
                    on_exit=[arm_controller_spawner],
                )
            ),
            RegisterEventHandler(
                OnProcessExit(
                    target_action=arm_controller_spawner,
                    on_exit=[hand_controller_spawner],
                )
            ),
            # Optional: Add any remaining controllers here if needed

            # 4. MoveIt and MTC Task (Can start after robot description is published)
            move_group_node,
            run_move_group_node,
            
            # 5. Visualization (Rviz)
            rviz_node,
        ]
    )