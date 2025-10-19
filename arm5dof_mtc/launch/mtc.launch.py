import os

from ament_index_python.packages import get_package_share_directory

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
    moveit_config = MoveItConfigsBuilder(robot_name ,package_name="arm5dof_moveit_config").to_moveit_configs()

    # 加载gazebo
    gazebo = IncludeLaunchDescription(
                PythonLaunchDescriptionSource([os.path.join(
                    get_package_share_directory('gazebo_ros'), 'launch', 'gazebo.launch.py')]),
    )

    # 加载controller manager
    controller_manager_node = Node(
    package='controller_manager',
    executable='ros2_control_node',
    parameters=[
        {'use_sim_time': True},
        '/path/to/your/ros2_control_config.yaml',  # 控制器配置文件
    ],
    output='screen'
    )
    
    # 加载实体到gazebo
    spawn_entity = Node(package='gazebo_ros', executable='spawn_entity.py',
                        arguments=['-topic', 'robot_description',
                                   '-entity', 'bbot'],
                        output='screen')
    
    # 加载ros2_controllers.yaml路径
    ros2_controllers_path = os.path.join(
        get_package_share_directory("arm5dof_moveit_config"),
        "config",
        "ros2_controllers.yaml",
    )


    # 关节状态发发布器
    joint_broad_spawner = Node(package='controller_manager', executable='spawner',
                               arguments=["joint_state"],)
    
    # 机械臂控制器节点
    arm_controller_node = Node(package='controller_manager', executable='spawner',
                               arguments=["arm_controller"],)

    # 手部控制器节点
    hand_controller_node = Node(package='controller_manager', executable='spawner',
                               arguments=["hand_controller"],)
    # 整体控制器节点
    arm_hand_controller_node = Node(package='controller_manager', executable='spawner',
                               arguments=["arm_hand_controller"],)
    # 任务执行节点
    mtc_task_node = Node(
    package='arm5dof_mtc',
    executable='arm5dof_mtc',
    output='screen'
    )   
    
    return LaunchDescription([
        arm5dof,
        gazebo,
        controller_manager_node,
        spawn_entity,
        joint_broad_spawner,
        arm_controller_node,
        hand_controller_node,
        arm_hand_controller_node,
        mtc_task_node,
    ])