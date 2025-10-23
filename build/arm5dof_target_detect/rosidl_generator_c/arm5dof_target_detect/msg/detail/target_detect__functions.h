// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from arm5dof_target_detect:msg/TargetDetect.idl
// generated code does not contain a copyright notice

#ifndef ARM5DOF_TARGET_DETECT__MSG__DETAIL__TARGET_DETECT__FUNCTIONS_H_
#define ARM5DOF_TARGET_DETECT__MSG__DETAIL__TARGET_DETECT__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "arm5dof_target_detect/msg/rosidl_generator_c__visibility_control.h"

#include "arm5dof_target_detect/msg/detail/target_detect__struct.h"

/// Initialize msg/TargetDetect message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * arm5dof_target_detect__msg__TargetDetect
 * )) before or use
 * arm5dof_target_detect__msg__TargetDetect__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_arm5dof_target_detect
bool
arm5dof_target_detect__msg__TargetDetect__init(arm5dof_target_detect__msg__TargetDetect * msg);

/// Finalize msg/TargetDetect message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm5dof_target_detect
void
arm5dof_target_detect__msg__TargetDetect__fini(arm5dof_target_detect__msg__TargetDetect * msg);

/// Create msg/TargetDetect message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * arm5dof_target_detect__msg__TargetDetect__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_arm5dof_target_detect
arm5dof_target_detect__msg__TargetDetect *
arm5dof_target_detect__msg__TargetDetect__create();

/// Destroy msg/TargetDetect message.
/**
 * It calls
 * arm5dof_target_detect__msg__TargetDetect__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm5dof_target_detect
void
arm5dof_target_detect__msg__TargetDetect__destroy(arm5dof_target_detect__msg__TargetDetect * msg);

/// Check for msg/TargetDetect message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm5dof_target_detect
bool
arm5dof_target_detect__msg__TargetDetect__are_equal(const arm5dof_target_detect__msg__TargetDetect * lhs, const arm5dof_target_detect__msg__TargetDetect * rhs);

/// Copy a msg/TargetDetect message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm5dof_target_detect
bool
arm5dof_target_detect__msg__TargetDetect__copy(
  const arm5dof_target_detect__msg__TargetDetect * input,
  arm5dof_target_detect__msg__TargetDetect * output);

/// Initialize array of msg/TargetDetect messages.
/**
 * It allocates the memory for the number of elements and calls
 * arm5dof_target_detect__msg__TargetDetect__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm5dof_target_detect
bool
arm5dof_target_detect__msg__TargetDetect__Sequence__init(arm5dof_target_detect__msg__TargetDetect__Sequence * array, size_t size);

/// Finalize array of msg/TargetDetect messages.
/**
 * It calls
 * arm5dof_target_detect__msg__TargetDetect__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm5dof_target_detect
void
arm5dof_target_detect__msg__TargetDetect__Sequence__fini(arm5dof_target_detect__msg__TargetDetect__Sequence * array);

/// Create array of msg/TargetDetect messages.
/**
 * It allocates the memory for the array and calls
 * arm5dof_target_detect__msg__TargetDetect__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_arm5dof_target_detect
arm5dof_target_detect__msg__TargetDetect__Sequence *
arm5dof_target_detect__msg__TargetDetect__Sequence__create(size_t size);

/// Destroy array of msg/TargetDetect messages.
/**
 * It calls
 * arm5dof_target_detect__msg__TargetDetect__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm5dof_target_detect
void
arm5dof_target_detect__msg__TargetDetect__Sequence__destroy(arm5dof_target_detect__msg__TargetDetect__Sequence * array);

/// Check for msg/TargetDetect message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm5dof_target_detect
bool
arm5dof_target_detect__msg__TargetDetect__Sequence__are_equal(const arm5dof_target_detect__msg__TargetDetect__Sequence * lhs, const arm5dof_target_detect__msg__TargetDetect__Sequence * rhs);

/// Copy an array of msg/TargetDetect messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_arm5dof_target_detect
bool
arm5dof_target_detect__msg__TargetDetect__Sequence__copy(
  const arm5dof_target_detect__msg__TargetDetect__Sequence * input,
  arm5dof_target_detect__msg__TargetDetect__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // ARM5DOF_TARGET_DETECT__MSG__DETAIL__TARGET_DETECT__FUNCTIONS_H_
