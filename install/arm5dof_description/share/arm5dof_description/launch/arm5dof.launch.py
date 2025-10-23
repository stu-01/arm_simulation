from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, RegisterEventHandler
from launch.conditions import IfCondition
from launch.event_handlers import OnProcessExit
from launch.substitutions import Command, FindExecutable, PathJoinSubstitution, LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():
    # 定义函数
    declared_arguments = []

# 设置参数，声明描述文件所在的包
    declared_arguments.append(
        DeclareLaunchArgument(
            "description_package",
            default_value="arm5dof_description",
            description="Description package with robot URDF/xacro files. Usually the argument \
        is not set, it enables use of a custom description.",
        )
    )
#设置参数，证明描述文件的名称 
    declared_arguments.append(
        DeclareLaunchArgument(
            "description_file",
            default_value="arm5dof.urdf.xacro",
            description="URDF/XACRO description file with the robot.",
        )
    )

# 把参数赋值给变量
    description_package = LaunchConfiguration("description_package")
    description_file = LaunchConfiguration("description_file")
    # gui = LaunchConfiguration("gui")
# xacro描述
    robot_description_content = Command(
        [
            PathJoinSubstitution([FindExecutable(name="xacro")]),
            " ",
            PathJoinSubstitution(
                [FindPackageShare(description_package), "urdf", description_file]
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

    nodes = [
        static_tf,
        robot_state_publisher_node,
    ]

    # Launch!
    return LaunchDescription(declared_arguments + nodes)
