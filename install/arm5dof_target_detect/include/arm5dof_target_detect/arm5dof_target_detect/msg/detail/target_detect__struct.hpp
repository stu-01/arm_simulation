// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from arm5dof_target_detect:msg/TargetDetect.idl
// generated code does not contain a copyright notice

#ifndef ARM5DOF_TARGET_DETECT__MSG__DETAIL__TARGET_DETECT__STRUCT_HPP_
#define ARM5DOF_TARGET_DETECT__MSG__DETAIL__TARGET_DETECT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'final_position_red'
// Member 'final_position_blue'
// Member 'final_position_green'
#include "geometry_msgs/msg/detail/point_stamped__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__arm5dof_target_detect__msg__TargetDetect __attribute__((deprecated))
#else
# define DEPRECATED__arm5dof_target_detect__msg__TargetDetect __declspec(deprecated)
#endif

namespace arm5dof_target_detect
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct TargetDetect_
{
  using Type = TargetDetect_<ContainerAllocator>;

  explicit TargetDetect_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : final_position_red(_init),
    final_position_blue(_init),
    final_position_green(_init)
  {
    (void)_init;
  }

  explicit TargetDetect_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : final_position_red(_alloc, _init),
    final_position_blue(_alloc, _init),
    final_position_green(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _final_position_red_type =
    geometry_msgs::msg::PointStamped_<ContainerAllocator>;
  _final_position_red_type final_position_red;
  using _final_position_blue_type =
    geometry_msgs::msg::PointStamped_<ContainerAllocator>;
  _final_position_blue_type final_position_blue;
  using _final_position_green_type =
    geometry_msgs::msg::PointStamped_<ContainerAllocator>;
  _final_position_green_type final_position_green;

  // setters for named parameter idiom
  Type & set__final_position_red(
    const geometry_msgs::msg::PointStamped_<ContainerAllocator> & _arg)
  {
    this->final_position_red = _arg;
    return *this;
  }
  Type & set__final_position_blue(
    const geometry_msgs::msg::PointStamped_<ContainerAllocator> & _arg)
  {
    this->final_position_blue = _arg;
    return *this;
  }
  Type & set__final_position_green(
    const geometry_msgs::msg::PointStamped_<ContainerAllocator> & _arg)
  {
    this->final_position_green = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    arm5dof_target_detect::msg::TargetDetect_<ContainerAllocator> *;
  using ConstRawPtr =
    const arm5dof_target_detect::msg::TargetDetect_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<arm5dof_target_detect::msg::TargetDetect_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<arm5dof_target_detect::msg::TargetDetect_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      arm5dof_target_detect::msg::TargetDetect_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<arm5dof_target_detect::msg::TargetDetect_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      arm5dof_target_detect::msg::TargetDetect_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<arm5dof_target_detect::msg::TargetDetect_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<arm5dof_target_detect::msg::TargetDetect_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<arm5dof_target_detect::msg::TargetDetect_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__arm5dof_target_detect__msg__TargetDetect
    std::shared_ptr<arm5dof_target_detect::msg::TargetDetect_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__arm5dof_target_detect__msg__TargetDetect
    std::shared_ptr<arm5dof_target_detect::msg::TargetDetect_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TargetDetect_ & other) const
  {
    if (this->final_position_red != other.final_position_red) {
      return false;
    }
    if (this->final_position_blue != other.final_position_blue) {
      return false;
    }
    if (this->final_position_green != other.final_position_green) {
      return false;
    }
    return true;
  }
  bool operator!=(const TargetDetect_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TargetDetect_

// alias to use template instance with default allocator
using TargetDetect =
  arm5dof_target_detect::msg::TargetDetect_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace arm5dof_target_detect

#endif  // ARM5DOF_TARGET_DETECT__MSG__DETAIL__TARGET_DETECT__STRUCT_HPP_
