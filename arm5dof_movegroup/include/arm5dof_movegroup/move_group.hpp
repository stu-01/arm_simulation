#include <arm5dof_target_detect/msg/detail/target_detect__struct.hpp>
#include <arm5dof_target_detect/msg/target_detect.hpp>
#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

class MoveNode : public rclcpp::Node{
    public:
    MoveNode();
    geometry_msgs::msg::PointStamped getRedTarget() const ;
    geometry_msgs::msg::PointStamped getBlueTarget() const ;
    geometry_msgs::msg::PointStamped getGreenTarget() const ;

    private:
        rclcpp::Subscription<arm5dof_target_detect::msg::TargetDetect>::SharedPtr subscriber_;
        geometry_msgs::msg::PointStamped red_target;
        geometry_msgs::msg::PointStamped blue_target;
        geometry_msgs::msg::PointStamped green_target;

        void move_callback(const arm5dof_target_detect::msg::TargetDetect::SharedPtr msg){
            this->red_target = msg->final_position_red;
            this->blue_target = msg->final_position_blue;
            this->green_target = msg->final_position_green;
        }

};