// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from arm5dof_target_detect:msg/TargetDetect.idl
// generated code does not contain a copyright notice
#include "arm5dof_target_detect/msg/detail/target_detect__rosidl_typesupport_fastrtps_cpp.hpp"
#include "arm5dof_target_detect/msg/detail/target_detect__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions
namespace geometry_msgs
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const geometry_msgs::msg::PointStamped &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  geometry_msgs::msg::PointStamped &);
size_t get_serialized_size(
  const geometry_msgs::msg::PointStamped &,
  size_t current_alignment);
size_t
max_serialized_size_PointStamped(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace geometry_msgs

// functions for geometry_msgs::msg::PointStamped already declared above

// functions for geometry_msgs::msg::PointStamped already declared above


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
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: final_position_red
  geometry_msgs::msg::typesupport_fastrtps_cpp::cdr_serialize(
    ros_message.final_position_red,
    cdr);
  // Member: final_position_blue
  geometry_msgs::msg::typesupport_fastrtps_cpp::cdr_serialize(
    ros_message.final_position_blue,
    cdr);
  // Member: final_position_green
  geometry_msgs::msg::typesupport_fastrtps_cpp::cdr_serialize(
    ros_message.final_position_green,
    cdr);
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_arm5dof_target_detect
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  arm5dof_target_detect::msg::TargetDetect & ros_message)
{
  // Member: final_position_red
  geometry_msgs::msg::typesupport_fastrtps_cpp::cdr_deserialize(
    cdr, ros_message.final_position_red);

  // Member: final_position_blue
  geometry_msgs::msg::typesupport_fastrtps_cpp::cdr_deserialize(
    cdr, ros_message.final_position_blue);

  // Member: final_position_green
  geometry_msgs::msg::typesupport_fastrtps_cpp::cdr_deserialize(
    cdr, ros_message.final_position_green);

  return true;
}  // NOLINT(readability/fn_size)

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_arm5dof_target_detect
get_serialized_size(
  const arm5dof_target_detect::msg::TargetDetect & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: final_position_red

  current_alignment +=
    geometry_msgs::msg::typesupport_fastrtps_cpp::get_serialized_size(
    ros_message.final_position_red, current_alignment);
  // Member: final_position_blue

  current_alignment +=
    geometry_msgs::msg::typesupport_fastrtps_cpp::get_serialized_size(
    ros_message.final_position_blue, current_alignment);
  // Member: final_position_green

  current_alignment +=
    geometry_msgs::msg::typesupport_fastrtps_cpp::get_serialized_size(
    ros_message.final_position_green, current_alignment);

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_arm5dof_target_detect
max_serialized_size_TargetDetect(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;


  // Member: final_position_red
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        geometry_msgs::msg::typesupport_fastrtps_cpp::max_serialized_size_PointStamped(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Member: final_position_blue
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        geometry_msgs::msg::typesupport_fastrtps_cpp::max_serialized_size_PointStamped(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Member: final_position_green
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        geometry_msgs::msg::typesupport_fastrtps_cpp::max_serialized_size_PointStamped(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = arm5dof_target_detect::msg::TargetDetect;
    is_plain =
      (
      offsetof(DataType, final_position_green) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _TargetDetect__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const arm5dof_target_detect::msg::TargetDetect *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _TargetDetect__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<arm5dof_target_detect::msg::TargetDetect *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _TargetDetect__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const arm5dof_target_detect::msg::TargetDetect *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _TargetDetect__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_TargetDetect(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _TargetDetect__callbacks = {
  "arm5dof_target_detect::msg",
  "TargetDetect",
  _TargetDetect__cdr_serialize,
  _TargetDetect__cdr_deserialize,
  _TargetDetect__get_serialized_size,
  _TargetDetect__max_serialized_size
};

static rosidl_message_type_support_t _TargetDetect__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_TargetDetect__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace arm5dof_target_detect

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_arm5dof_target_detect
const rosidl_message_type_support_t *
get_message_type_support_handle<arm5dof_target_detect::msg::TargetDetect>()
{
  return &arm5dof_target_detect::msg::typesupport_fastrtps_cpp::_TargetDetect__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, arm5dof_target_detect, msg, TargetDetect)() {
  return &arm5dof_target_detect::msg::typesupport_fastrtps_cpp::_TargetDetect__handle;
}

#ifdef __cplusplus
}
#endif
