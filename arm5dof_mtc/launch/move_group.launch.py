from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from moveit_configs_utils import MoveItConfigsBuilder
from launch_ros.actions import Node
from launch.substitutions import Command, FindExecutable, PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():
    robot_name = "arm5dof"

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

    run_move_group_node = Node(
        package="arm5dof_mtc",
        executable="arm5dof_mtc",
        output="screen",
        parameters=[
            moveit_config.to_dict(),
            move_group_capabilities,
        ],
    )


    return LaunchDescription(
        [
            rviz_node,
            move_group_node,
            run_move_group_node,
        ]
    )