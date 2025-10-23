// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from arm5dof_target_detect:msg/TargetDetect.idl
// generated code does not contain a copyright notice

#ifndef ARM5DOF_TARGET_DETECT__MSG__DETAIL__TARGET_DETECT__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define ARM5DOF_TARGET_DETECT__MSG__DETAIL__TARGET_DETECT__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "arm5dof_target_detect/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "arm5dof_target_detect/msg/detail/target_detect__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace arm5dof_target_detect
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_arm5dof_target_detect
cdr_serialize(
  const arm5dof_target_detect::msg::TargetDetect & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_arm5dof_target_detect
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  arm5dof_target_detect::msg::TargetDetect & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_arm5dof_target_detect
get_serialized_size(
  const arm5dof_target_detect::msg::TargetDetect & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_arm5dof_target_detect
max_serialized_size_TargetDetect(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace arm5dof_target_detect

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_arm5dof_target_detect
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, arm5dof_target_detect, msg, TargetDetect)();

#ifdef __cplusplus
}
#endif

#endif  // ARM5DOF_TARGET_DETECT__MSG__DETAIL__TARGET_DETECT__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
