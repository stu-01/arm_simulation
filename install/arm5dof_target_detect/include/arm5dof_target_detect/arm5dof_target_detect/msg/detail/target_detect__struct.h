// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from arm5dof_target_detect:msg/TargetDetect.idl
// generated code does not contain a copyright notice

#ifndef ARM5DOF_TARGET_DETECT__MSG__DETAIL__TARGET_DETECT__STRUCT_H_
#define ARM5DOF_TARGET_DETECT__MSG__DETAIL__TARGET_DETECT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'final_position_red'
// Member 'final_position_blue'
// Member 'final_position_green'
#include "geometry_msgs/msg/detail/point_stamped__struct.h"

/// Struct defined in msg/TargetDetect in the package arm5dof_target_detect.
typedef struct arm5dof_target_detect__msg__TargetDetect
{
  geometry_msgs__msg__PointStamped final_position_red;
  geometry_msgs__msg__PointStamped final_position_blue;
  geometry_msgs__msg__PointStamped final_position_green;
} arm5dof_target_detect__msg__TargetDetect;

// Struct for a sequence of arm5dof_target_detect__msg__TargetDetect.
typedef struct arm5dof_target_detect__msg__TargetDetect__Sequence
{
  arm5dof_target_detect__msg__TargetDetect * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} arm5dof_target_detect__msg__TargetDetect__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ARM5DOF_TARGET_DETECT__MSG__DETAIL__TARGET_DETECT__STRUCT_H_
