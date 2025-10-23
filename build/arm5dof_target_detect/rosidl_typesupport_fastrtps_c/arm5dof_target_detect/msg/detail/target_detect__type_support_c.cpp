// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from arm5dof_target_detect:msg/TargetDetect.idl
// generated code does not contain a copyright notice
#include "arm5dof_target_detect/msg/detail/target_detect__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "arm5dof_target_detect/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "arm5dof_target_detect/msg/detail/target_detect__struct.h"
#include "arm5dof_target_detect/msg/detail/target_detect__functions.h"
#include "fastcdr/Cdr.h"

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

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "geometry_msgs/msg/detail/point_stamped__functions.h"  // final_position_blue, final_position_green, final_position_red

// forward declare type support functions
ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_arm5dof_target_detect
size_t get_serialized_size_geometry_msgs__msg__PointStamped(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_arm5dof_target_detect
size_t max_serialized_size_geometry_msgs__msg__PointStamped(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_arm5dof_target_detect
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, geometry_msgs, msg, PointStamped)();


using _TargetDetect__ros_msg_type = arm5dof_target_detect__msg__TargetDetect;

static bool _TargetDetect__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _TargetDetect__ros_msg_type * ros_message = static_cast<const _TargetDetect__ros_msg_type *>(untyped_ros_message);
  // Field name: final_position_red
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, geometry_msgs, msg, PointStamped
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->final_position_red, cdr))
    {
      return false;
    }
  }

  // Field name: final_position_blue
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, geometry_msgs, msg, PointStamped
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->final_position_blue, cdr))
    {
      return false;
    }
  }

  // Field name: final_position_green
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, geometry_msgs, msg, PointStamped
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->final_position_green, cdr))
    {
      return false;
    }
  }

  return true;
}

static bool _TargetDetect__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _TargetDetect__ros_msg_type * ros_message = static_cast<_TargetDetect__ros_msg_type *>(untyped_ros_message);
  // Field name: final_position_red
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, geometry_msgs, msg, PointStamped
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->final_position_red))
    {
      return false;
    }
  }

  // Field name: final_position_blue
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, geometry_msgs, msg, PointStamped
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->final_position_blue))
    {
      return false;
    }
  }

  // Field name: final_position_green
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, geometry_msgs, msg, PointStamped
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->final_position_green))
    {
      return false;
    }
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_arm5dof_target_detect
size_t get_serialized_size_arm5dof_target_detect__msg__TargetDetect(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _TargetDetect__ros_msg_type * ros_message = static_cast<const _TargetDetect__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name final_position_red

  current_alignment += get_serialized_size_geometry_msgs__msg__PointStamped(
    &(ros_message->final_position_red), current_alignment);
  // field.name final_position_blue

  current_alignment += get_serialized_size_geometry_msgs__msg__PointStamped(
    &(ros_message->final_position_blue), current_alignment);
  // field.name final_position_green

  current_alignment += get_serialized_size_geometry_msgs__msg__PointStamped(
    &(ros_message->final_position_green), current_alignment);

  return current_alignment - initial_alignment;
}

static uint32_t _TargetDetect__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_arm5dof_target_detect__msg__TargetDetect(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_arm5dof_target_detect
size_t max_serialized_size_arm5dof_target_detect__msg__TargetDetect(
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

  // member: final_position_red
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_geometry_msgs__msg__PointStamped(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }
  // member: final_position_blue
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_geometry_msgs__msg__PointStamped(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }
  // member: final_position_green
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_geometry_msgs__msg__PointStamped(
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
    using DataType = arm5dof_target_detect__msg__TargetDetect;
    is_plain =
      (
      offsetof(DataType, final_position_green) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _TargetDetect__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_arm5dof_target_detect__msg__TargetDetect(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_TargetDetect = {
  "arm5dof_target_detect::msg",
  "TargetDetect",
  _TargetDetect__cdr_serialize,
  _TargetDetect__cdr_deserialize,
  _TargetDetect__get_serialized_size,
  _TargetDetect__max_serialized_size
};

static rosidl_message_type_support_t _TargetDetect__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_TargetDetect,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, arm5dof_target_detect, msg, TargetDetect)() {
  return &_TargetDetect__type_support;
}

#if defined(__cplusplus)
}
#endif
