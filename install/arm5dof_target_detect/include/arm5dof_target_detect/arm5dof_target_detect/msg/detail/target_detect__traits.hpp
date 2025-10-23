// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from arm5dof_target_detect:msg/TargetDetect.idl
// generated code does not contain a copyright notice

#ifndef ARM5DOF_TARGET_DETECT__MSG__DETAIL__TARGET_DETECT__TRAITS_HPP_
#define ARM5DOF_TARGET_DETECT__MSG__DETAIL__TARGET_DETECT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "arm5dof_target_detect/msg/detail/target_detect__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'final_position_red'
// Member 'final_position_blue'
// Member 'final_position_green'
#include "geometry_msgs/msg/detail/point_stamped__traits.hpp"

namespace arm5dof_target_detect
{

namespace msg
{

inline void to_flow_style_yaml(
  const TargetDetect & msg,
  std::ostream & out)
{
  out << "{";
  // member: final_position_red
  {
    out << "final_position_red: ";
    to_flow_style_yaml(msg.final_position_red, out);
    out << ", ";
  }

  // member: final_position_blue
  {
    out << "final_position_blue: ";
    to_flow_style_yaml(msg.final_position_blue, out);
    out << ", ";
  }

  // member: final_position_green
  {
    out << "final_position_green: ";
    to_flow_style_yaml(msg.final_position_green, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const TargetDetect & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: final_position_red
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "final_position_red:\n";
    to_block_style_yaml(msg.final_position_red, out, indentation + 2);
  }

  // member: final_position_blue
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "final_position_blue:\n";
    to_block_style_yaml(msg.final_position_blue, out, indentation + 2);
  }

  // member: final_position_green
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "final_position_green:\n";
    to_block_style_yaml(msg.final_position_green, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const TargetDetect & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace arm5dof_target_detect

namespace rosidl_generator_traits
{

[[deprecated("use arm5dof_target_detect::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const arm5dof_target_detect::msg::TargetDetect & msg,
  std::ostream & out, size_t indentation = 0)
{
  arm5dof_target_detect::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use arm5dof_target_detect::msg::to_yaml() instead")]]
inline std::string to_yaml(const arm5dof_target_detect::msg::TargetDetect & msg)
{
  return arm5dof_target_detect::msg::to_yaml(msg);
}

template<>
inline const char * data_type<arm5dof_target_detect::msg::TargetDetect>()
{
  return "arm5dof_target_detect::msg::TargetDetect";
}

template<>
inline const char * name<arm5dof_target_detect::msg::TargetDetect>()
{
  return "arm5dof_target_detect/msg/TargetDetect";
}

template<>
struct has_fixed_size<arm5dof_target_detect::msg::TargetDetect>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::PointStamped>::value> {};

template<>
struct has_bounded_size<arm5dof_target_detect::msg::TargetDetect>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::PointStamped>::value> {};

template<>
struct is_message<arm5dof_target_detect::msg::TargetDetect>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ARM5DOF_TARGET_DETECT__MSG__DETAIL__TARGET_DETECT__TRAITS_HPP_
