search_mode=OPTIMIZE_MAX_JOINT
srdf_filename=arm5dof.srdf
robot_name_in_srdf=arm5dof
moveit_config_pkg=arm5dof_moveit_config
robot_name=arm5dof
planning_group_name=arm
ikfast_plugin_pkg=arm5dof_moveit_ikfast_plugins
base_link_name=base_link
eef_link_name=link5
ikfast_output_path=/home/zc/code/ws_arm5dof/src/arm5dof_moveit_ikfast_plugins/src/arm5dof_arm_ikfast_solver.cpp

rosrun moveit_kinematics create_ikfast_moveit_plugin.py\
  --search_mode=$search_mode\
  --srdf_filename=$srdf_filename\
  --robot_name_in_srdf=$robot_name_in_srdf\
  --moveit_config_pkg=$moveit_config_pkg\
  $robot_name\
  $planning_group_name\
  $ikfast_plugin_pkg\
  $base_link_name\
  $eef_link_name\
  $ikfast_output_path
