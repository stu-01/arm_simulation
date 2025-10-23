// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from arm5dof_target_detect:msg/TargetDetect.idl
// generated code does not contain a copyright notice

#ifndef ARM5DOF_TARGET_DETECT__MSG__DETAIL__TARGET_DETECT__BUILDER_HPP_
#define ARM5DOF_TARGET_DETECT__MSG__DETAIL__TARGET_DETECT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "arm5dof_target_detect/msg/detail/target_detect__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace arm5dof_target_detect
{

namespace msg
{

namespace builder
{

class Init_TargetDetect_final_position_green
{
public:
  explicit Init_TargetDetect_final_position_green(::arm5dof_target_detect::msg::TargetDetect & msg)
  : msg_(msg)
  {}
  ::arm5dof_target_detect::msg::TargetDetect final_position_green(::arm5dof_target_detect::msg::TargetDetect::_final_position_green_type arg)
  {
    msg_.final_position_green = std::move(arg);
    return std::move(msg_);
  }

private:
  ::arm5dof_target_detect::msg::TargetDetect msg_;
};

class Init_TargetDetect_final_position_blue
{
public:
  explicit Init_TargetDetect_final_position_blue(::arm5dof_target_detect::msg::TargetDetect & msg)
  : msg_(msg)
  {}
  Init_TargetDetect_final_position_green final_position_blue(::arm5dof_target_detect::msg::TargetDetect::_final_position_blue_type arg)
  {
    msg_.final_position_blue = std::move(arg);
    return Init_TargetDetect_final_position_green(msg_);
  }

private:
  ::arm5dof_target_detect::msg::TargetDetect msg_;
};

class Init_TargetDetect_final_position_red
{
public:
  Init_TargetDetect_final_position_red()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TargetDetect_final_position_blue final_position_red(::arm5dof_target_detect::msg::TargetDetect::_final_position_red_type arg)
  {
    msg_.final_position_red = std::move(arg);
    return Init_TargetDetect_final_position_blue(msg_);
  }

private:
  ::arm5dof_target_detect::msg::TargetDetect msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::arm5dof_target_detect::msg::TargetDetect>()
{
  return arm5dof_target_detect::msg::builder::Init_TargetDetect_final_position_red();
}

}  // namespace arm5dof_target_detect

#endif  // ARM5DOF_TARGET_DETECT__MSG__DETAIL__TARGET_DETECT__BUILDER_HPP_
