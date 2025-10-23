// generated from rosidl_generator_cpp/resource/rosidl_generator_cpp__visibility_control.hpp.in
// generated code does not contain a copyright notice

#ifndef ARM5DOF_TARGET_DETECT__MSG__ROSIDL_GENERATOR_CPP__VISIBILITY_CONTROL_HPP_
#define ARM5DOF_TARGET_DETECT__MSG__ROSIDL_GENERATOR_CPP__VISIBILITY_CONTROL_HPP_

#ifdef __cplusplus
extern "C"
{
#endif

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define ROSIDL_GENERATOR_CPP_EXPORT_arm5dof_target_detect __attribute__ ((dllexport))
    #define ROSIDL_GENERATOR_CPP_IMPORT_arm5dof_target_detect __attribute__ ((dllimport))
  #else
    #define ROSIDL_GENERATOR_CPP_EXPORT_arm5dof_target_detect __declspec(dllexport)
    #define ROSIDL_GENERATOR_CPP_IMPORT_arm5dof_target_detect __declspec(dllimport)
  #endif
  #ifdef ROSIDL_GENERATOR_CPP_BUILDING_DLL_arm5dof_target_detect
    #define ROSIDL_GENERATOR_CPP_PUBLIC_arm5dof_target_detect ROSIDL_GENERATOR_CPP_EXPORT_arm5dof_target_detect
  #else
    #define ROSIDL_GENERATOR_CPP_PUBLIC_arm5dof_target_detect ROSIDL_GENERATOR_CPP_IMPORT_arm5dof_target_detect
  #endif
#else
  #define ROSIDL_GENERATOR_CPP_EXPORT_arm5dof_target_detect __attribute__ ((visibility("default")))
  #define ROSIDL_GENERATOR_CPP_IMPORT_arm5dof_target_detect
  #if __GNUC__ >= 4
    #define ROSIDL_GENERATOR_CPP_PUBLIC_arm5dof_target_detect __attribute__ ((visibility("default")))
  #else
    #define ROSIDL_GENERATOR_CPP_PUBLIC_arm5dof_target_detect
  #endif
#endif

#ifdef __cplusplus
}
#endif

#endif  // ARM5DOF_TARGET_DETECT__MSG__ROSIDL_GENERATOR_CPP__VISIBILITY_CONTROL_HPP_
