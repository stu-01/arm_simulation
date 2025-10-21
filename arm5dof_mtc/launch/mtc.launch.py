import os

from ament_index_python.packages import get_package_share_directory
from launch.actions import ExecuteProcess
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource

from moveit_configs_utils import MoveItConfigsBuilder

from launch_ros.actions import Node

def generate_launch_description():
    robot_name = "arm5dof"
    package_name='arm5dof_description'
    
    arm5dof = IncludeLaunchDescription(
                PythonLaunchDescriptionSource([os.path.join(
                    get_package_share_directory(package_name),'launch','arm5dof.launch.py'
                )]), launch_arguments={'use_sim_time': 'true'}.items()
    )
    
    # 加载moveit配置
    moveit_config = (MoveItConfigsBuilder("arm5dof")
                    #  _moveit_config为什么这里不能写package_name="arm5dof_moveit_config"？
    .robot_description(file_path="config/arm5dof.urdf.xacro")
    .trajectory_execution(file_path="config/moveit_controllers.yaml")
    .planning_pipelines(
        pipelines=["ompl", "chomp", "pilz_industrial_motion_planner"]
    )).to_moveit_configs()
    # .package_name="arm5dof_moveit_config".to_moveit_configs()

    # # 加载gazebo
    # gazebo = IncludeLaunchDescription(
    #             PythonLaunchDescriptionSource([os.path.join(
    #                 get_package_share_directory('gazebo_ros'), 'launch', 'gazebo.launch.py')]),
    # )

    # # 加载controller manager
    # controller_manager_node = Node(
    # package='controller_manager',
    # executable='ros2_control_node',
    # parameters=[
    #     {'use_sim_time': True},
    #     '/path/to/your/ros2_control_config.yaml',  # 控制器配置文件
    # ],
    # output='screen'
    # )
    
    # # 加载实体到gazebo
    # spawn_entity = Node(package='gazebo_ros', executable='spawn_entity.py',
    #                     arguments=['-topic', 'robot_description',
    #                                '-entity', 'bbot'],
    #                     output='screen')
    
    # # 加载ros2_controllers.yaml路径
    # ros2_controllers_path = os.path.join(
    #     get_package_share_directory("arm5dof_moveit_config"),
    #     "config",
    #     "ros2_controllers.yaml",
    # )


    # # 关节状态发发布器
    # joint_broad_spawner = Node(package='controller_manager', executable='spawner',
    #                            arguments=["joint_state"],)
    
    # # 机械臂控制器节点
    # arm_controller_node = Node(package='controller_manager', executable='spawner',
    #                            arguments=["arm_controller"],)

    # # 手部控制器节点
    # hand_controller_node = Node(package='controller_manager', executable='spawner',
    #                            arguments=["hand_controller"],)
    # # 整体控制器节点
    # arm_hand_controller_node = Node(package='controller_manager', executable='spawner',
    #                            arguments=["arm_hand_controller"],)
    # # 任务执行节点
    # mtc_task_node = Node(
    # package='arm5dof_mtc',
    # executable='arm5dof_mtc',
    # output='screen'
    # )   
    
    # return LaunchDescription([
    #     arm5dof,
    #     gazebo,
    #     controller_manager_node,
    #     spawn_entity,
    #     joint_broad_spawner,
    #     arm_controller_node,
    #     hand_controller_node,
    #     arm_hand_controller_node,
    #     mtc_task_node,
    # ])

    move_group_capabilities = {
        "capabilities": "move_group/ExecuteTaskSolutionCapability"
    }

    # Start the actual move_group node/action server
    run_move_group_node = Node(
        package="arm5dof_mtc",
        executable="arm5dof_mtc",
        output="screen",
        parameters=[
            moveit_config.to_dict(),
            move_group_capabilities,
        ],
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

    # # Static TF
    # static_tf = Node(
    #     package="tf2_ros",
    #     executable="static_transform_publisher",
    #     name="static_transform_publisher",
    #     output="log",
    #     arguments=["--frame-id", "world", "--child-frame-id", "base_link"],
    # )

    # # Publish TF
    # robot_state_publisher = Node(
    #     package="robot_state_publisher",
    #     executable="robot_state_publisher",
    #     name="robot_state_publisher",
    #     output="both",
    #     parameters=[
    #         moveit_config.robot_description,
    #     ],
    # )

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

    # Load controllers
    load_controllers = []
    for controller in [
        "arm_controller",
        "hand_controller",
        "arm_hand_controller",
        "joint_state_broadcaster",
    ]:
        load_controllers += [
            ExecuteProcess(
                cmd=["ros2 run controller_manager spawner {}".format(controller)],
                shell=True,
                output="screen",
            )
        ]

    return LaunchDescription(
        [
            rviz_node,
            # static_tf,
            # robot_state_publisher,
            run_move_group_node,
            ros2_control_node,
        ]
        + load_controllers
    )