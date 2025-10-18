#include "../include/arm5dof_movegroup/move_group.hpp"


    MoveNode::MoveNode():Node("move_node",rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(true)){
        
        subscriber_ = this->create_subscription<arm5dof_target_detect::msg::TargetDetect>(
            "target_detect",10,
            std::bind(&MoveNode::move_callback,this,std::placeholders::_1)
        );
        
    }

    geometry_msgs::msg::PointStamped MoveNode::getRedTarget() const {
        return red_target;
    }
    geometry_msgs::msg::PointStamped MoveNode::getBlueTarget() const {
        return blue_target;
    }
    geometry_msgs::msg::PointStamped MoveNode::getGreenTarget() const {
        return green_target;
    }