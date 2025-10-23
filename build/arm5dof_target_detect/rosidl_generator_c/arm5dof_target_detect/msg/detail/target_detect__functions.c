// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from arm5dof_target_detect:msg/TargetDetect.idl
// generated code does not contain a copyright notice
#include "arm5dof_target_detect/msg/detail/target_detect__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `final_position_red`
// Member `final_position_blue`
// Member `final_position_green`
#include "geometry_msgs/msg/detail/point_stamped__functions.h"

bool
arm5dof_target_detect__msg__TargetDetect__init(arm5dof_target_detect__msg__TargetDetect * msg)
{
  if (!msg) {
    return false;
  }
  // final_position_red
  if (!geometry_msgs__msg__PointStamped__init(&msg->final_position_red)) {
    arm5dof_target_detect__msg__TargetDetect__fini(msg);
    return false;
  }
  // final_position_blue
  if (!geometry_msgs__msg__PointStamped__init(&msg->final_position_blue)) {
    arm5dof_target_detect__msg__TargetDetect__fini(msg);
    return false;
  }
  // final_position_green
  if (!geometry_msgs__msg__PointStamped__init(&msg->final_position_green)) {
    arm5dof_target_detect__msg__TargetDetect__fini(msg);
    return false;
  }
  return true;
}

void
arm5dof_target_detect__msg__TargetDetect__fini(arm5dof_target_detect__msg__TargetDetect * msg)
{
  if (!msg) {
    return;
  }
  // final_position_red
  geometry_msgs__msg__PointStamped__fini(&msg->final_position_red);
  // final_position_blue
  geometry_msgs__msg__PointStamped__fini(&msg->final_position_blue);
  // final_position_green
  geometry_msgs__msg__PointStamped__fini(&msg->final_position_green);
}

bool
arm5dof_target_detect__msg__TargetDetect__are_equal(const arm5dof_target_detect__msg__TargetDetect * lhs, const arm5dof_target_detect__msg__TargetDetect * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // final_position_red
  if (!geometry_msgs__msg__PointStamped__are_equal(
      &(lhs->final_position_red), &(rhs->final_position_red)))
  {
    return false;
  }
  // final_position_blue
  if (!geometry_msgs__msg__PointStamped__are_equal(
      &(lhs->final_position_blue), &(rhs->final_position_blue)))
  {
    return false;
  }
  // final_position_green
  if (!geometry_msgs__msg__PointStamped__are_equal(
      &(lhs->final_position_green), &(rhs->final_position_green)))
  {
    return false;
  }
  return true;
}

bool
arm5dof_target_detect__msg__TargetDetect__copy(
  const arm5dof_target_detect__msg__TargetDetect * input,
  arm5dof_target_detect__msg__TargetDetect * output)
{
  if (!input || !output) {
    return false;
  }
  // final_position_red
  if (!geometry_msgs__msg__PointStamped__copy(
      &(input->final_position_red), &(output->final_position_red)))
  {
    return false;
  }
  // final_position_blue
  if (!geometry_msgs__msg__PointStamped__copy(
      &(input->final_position_blue), &(output->final_position_blue)))
  {
    return false;
  }
  // final_position_green
  if (!geometry_msgs__msg__PointStamped__copy(
      &(input->final_position_green), &(output->final_position_green)))
  {
    return false;
  }
  return true;
}

arm5dof_target_detect__msg__TargetDetect *
arm5dof_target_detect__msg__TargetDetect__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  arm5dof_target_detect__msg__TargetDetect * msg = (arm5dof_target_detect__msg__TargetDetect *)allocator.allocate(sizeof(arm5dof_target_detect__msg__TargetDetect), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(arm5dof_target_detect__msg__TargetDetect));
  bool success = arm5dof_target_detect__msg__TargetDetect__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
arm5dof_target_detect__msg__TargetDetect__destroy(arm5dof_target_detect__msg__TargetDetect * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    arm5dof_target_detect__msg__TargetDetect__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
arm5dof_target_detect__msg__TargetDetect__Sequence__init(arm5dof_target_detect__msg__TargetDetect__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  arm5dof_target_detect__msg__TargetDetect * data = NULL;

  if (size) {
    data = (arm5dof_target_detect__msg__TargetDetect *)allocator.zero_allocate(size, sizeof(arm5dof_target_detect__msg__TargetDetect), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = arm5dof_target_detect__msg__TargetDetect__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        arm5dof_target_detect__msg__TargetDetect__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
arm5dof_target_detect__msg__TargetDetect__Sequence__fini(arm5dof_target_detect__msg__TargetDetect__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      arm5dof_target_detect__msg__TargetDetect__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

arm5dof_target_detect__msg__TargetDetect__Sequence *
arm5dof_target_detect__msg__TargetDetect__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  arm5dof_target_detect__msg__TargetDetect__Sequence * array = (arm5dof_target_detect__msg__TargetDetect__Sequence *)allocator.allocate(sizeof(arm5dof_target_detect__msg__TargetDetect__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = arm5dof_target_detect__msg__TargetDetect__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
arm5dof_target_detect__msg__TargetDetect__Sequence__destroy(arm5dof_target_detect__msg__TargetDetect__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    arm5dof_target_detect__msg__TargetDetect__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
arm5dof_target_detect__msg__TargetDetect__Sequence__are_equal(const arm5dof_target_detect__msg__TargetDetect__Sequence * lhs, const arm5dof_target_detect__msg__TargetDetect__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!arm5dof_target_detect__msg__TargetDetect__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
arm5dof_target_detect__msg__TargetDetect__Sequence__copy(
  const arm5dof_target_detect__msg__TargetDetect__Sequence * input,
  arm5dof_target_detect__msg__TargetDetect__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(arm5dof_target_detect__msg__TargetDetect);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    arm5dof_target_detect__msg__TargetDetect * data =
      (arm5dof_target_detect__msg__TargetDetect *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!arm5dof_target_detect__msg__TargetDetect__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          arm5dof_target_detect__msg__TargetDetect__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!arm5dof_target_detect__msg__TargetDetect__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
