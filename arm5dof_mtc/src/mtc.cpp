#include "../include/arm5dof_mtc/mtc.hpp"

// 构造函数，用初始化列表创建节点
MTCTaskNode::MTCTaskNode(const rclcpp::NodeOptions &options)
    : node_{std::make_shared<rclcpp::Node>("mtc_node", options)} {}

// 返回节点的基础接口指针
rclcpp::node_interfaces::NodeBaseInterface::SharedPtr
MTCTaskNode::getNodeBaseInterface() {
  return node_->get_node_base_interface();
}

// 创建规划场景，添加碰撞物体
void MTCTaskNode::setupPlanningScene() {
  // 创建一条消息，表示一条碰撞物体，再由规划场景接口添加到规划场景中
  moveit_msgs::msg::CollisionObject object;
  object.id = "object";
  object.header.frame_id = "world";
  object.primitives.resize(1);
  object.primitives[0].type = shape_msgs::msg::SolidPrimitive::CYLINDER;
  object.primitives[0].dimensions = {0.1, 0.02};

  geometry_msgs::msg::Pose pose;
  pose.position.x = 0.5;
  pose.position.y = -0.25;
  pose.orientation.w = 1.0;
  object.pose = pose;

  // 将碰撞物体添加到规划场景中
  moveit::planning_interface::PlanningSceneInterface psi;
  psi.applyCollisionObject(object);
}

// 执行任务
void MTCTaskNode::doTask() {
  task_ = createTask();

  try {
    task_.init();
  } catch (mtc::InitStageException &e) {
    RCLCPP_ERROR_STREAM(LOGGER, e);
    return;
  }

  if (!task_.plan(5)) {
    RCLCPP_ERROR_STREAM(LOGGER, "Task planning failed");
    return;
  }
  task_.introspection().publishSolution(*task_.solutions().front());

  // 执行任务
  auto result = task_.execute(*task_.solutions().front());
  if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
    RCLCPP_ERROR_STREAM(LOGGER, "Task execution failed");
    return;
  }

  return;
}

// 创建任务
mtc::Task MTCTaskNode::createTask() {
  mtc::Task task;
  task.stages()->setName("demo task");
  task.loadRobotModel(node_);

  // 给规划组的名字设置成变量，方便调用
  const auto &arm_group_name = "arm";
  const auto &hand_group_name = "hand";
  // const auto &hand_frame = "arm_hand";

  // 设置任务属性，规划组，末端执行器，逆运动学
  task.setProperty("group", arm_group_name);
  task.setProperty("eef", hand_group_name);
  // task.setProperty("ik_frame", hand_frame);

// 暂时禁用特别的编译器警告，允许错误的写法存在
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

  mtc::Stage *current_state_ptr =
      nullptr; // Forward current_state on to grasp pose generator

#pragma GCC diagnostic pop

// 添加当前阶段状态
  auto stage_state_current =
      std::make_unique<mtc::stages::CurrentState>("current");
  current_state_ptr = stage_state_current.get();
  task.add(std::move(stage_state_current));

  // 规划器设置
  auto sampling_planner =
      std::make_shared<mtc::solvers::PipelinePlanner>(node_);
  
  // 关节插值规划器设置
  auto interpolation_planner =
      std::make_shared<mtc::solvers::JointInterpolationPlanner>();

  // 笛卡尔路径规划器设置
  auto cartesian_planner = std::make_shared<mtc::solvers::CartesianPath>();
  cartesian_planner->setMaxVelocityScalingFactor(1.0);
  cartesian_planner->setMaxAccelerationScalingFactor(1.0);
  cartesian_planner->setStepSize(.01);

  // 添加移动到预抓取位置
  auto stage_open_hand =
      std::make_unique<mtc::stages::MoveTo>("open hand", interpolation_planner);
  stage_open_hand->setGroup(hand_group_name);
  stage_open_hand->setGoal("open");
  task.add(std::move(stage_open_hand));

  return task;
}