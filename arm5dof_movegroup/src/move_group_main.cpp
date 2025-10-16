#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

int main(int argc,char** argv)
{
    rclcpp::init(argc,argv);

    auto node = rclcpp::Node::make_shared("first_plan",
        rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(true));

    auto const logger = rclcpp::get_logger("first_plan");

    auto executor = rclcpp::executors::SingleThreadedExecutor();
    executor.add_node(node);

    using::moveit::planning_interface::MoveGroupInterface;
    auto move_group_interface = MoveGroupInterface(node,"arm5dof");

    auto const target_pose = [](){
        geometry_msgs::msg::Pose pose;
        pose.orientation.w = 1.0;
        pose.position.x = 0.28;
        pose.position.y = 0.4;
        pose.position.z = 0.5;
        return pose;
    }();

    move_group_interface.setPoseTarget(target_pose);

    auto const[success,plan] = [&move_group_interface](){
        MoveGroupInterface::Plan msg;
        auto const ok = static_cast<bool>(move_group_interface.plan(msg));
        return std::make_pair(ok,msg);
    }();

    if(success){
       move_group_interface.execute(plan);
    }
    else{
        RCLCPP_ERROR(logger,"planning failed!");
    }
    // if(!success){
    //     RCLCPP_ERROR(logger,"planning failed!");
    // }

    rclcpp::shutdown();
    return 0;
}