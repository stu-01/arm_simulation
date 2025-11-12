#include "arm5dof_mtc/mtc.hpp"
#include <memory>
#include <moveit/task_constructor/container.h>

//随机目标位置，hand_frame的关节是tool_center_frame，setMinMaxDistance0.00-2.0

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
  // 创建一条消息，表示一个碰撞物体，再由规划场景接口添加到规划场景中
  moveit_msgs::msg::CollisionObject object;
  object.id = "object";
  object.header.frame_id = "world";
  object.primitives.resize(1);
  object.primitives[0].type = shape_msgs::msg::SolidPrimitive::CYLINDER;
  object.primitives[0].dimensions = {0.1, 0.02};

  geometry_msgs::msg::Pose pose;
  pose.position.x = 0.3;
  pose.position.y = 0.0;
  pose.position.z = 0.15;
  pose.orientation.w = 1.0;
  object.pose = pose;

  // 将碰撞物体添加到规划场景中
  moveit::planning_interface::PlanningSceneInterface psi;
  psi.applyCollisionObject(object);

  moveit_msgs::msg::CollisionObject base;
  base.id = "base";
  base.header.frame_id = "world";
  base.primitives.resize(1);
  base.primitives[0].type = shape_msgs::msg::SolidPrimitive::BOX;
  base.primitives[0].dimensions = {0.2, 0.2, 0.1};

  geometry_msgs::msg::Pose base_pose;
  base_pose.position.x = 0.3;
  base_pose.position.y = 0.0;
  base_pose.position.z = 0.05;
  base_pose.orientation.w = 1.0;
  base.pose = base_pose;

  // 将碰撞物体添加到规划场景中
  psi.applyCollisionObject(base);

  // moveit_msgs::msg::CollisionObject left_base;
  // left_base.id = "left_base";
  // left_base.header.frame_id = "world";
  // left_base.primitives.resize(1);
  // left_base.primitives[0].type = shape_msgs::msg::SolidPrimitive::BOX;
  // left_base.primitives[0].dimensions = {0.1, 0.1, 0.1};

//   geometry_msgs::msg::Pose left_base_pose;
//   left_base_pose.position.x = 0.2;
//   left_base_pose.position.y = 0.2;
//   left_base_pose.position.z = 0.05;
//   left_base_pose.orientation.w = 1.0;
//   left_base.pose = left_base_pose;

//   // 将碰撞物体添加到规划场景中
//   psi.applyCollisionObject(left_base);
}

// 创建任务
mtc::Task MTCTaskNode::createTask() {
  mtc::Task task;
  task.stages()->setName("demo task");
  task.loadRobotModel(node_);
  // 以下六行都是在设置任务的属性
  // 给规划组的名字设置成变量，方便调用
  const auto &arm_group_name = "arm";
  const auto &hand_group_name = "hand";
  const auto &hand_frame = "tool_center_frame";

  // 设置任务属性，包括规划组，末端执行器，逆运动学
  task.setProperty("group", arm_group_name);
  task.setProperty("eef", hand_group_name);
  task.setProperty("ik_frame", hand_frame);

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

  // 下面是三个规划器选项
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

  // 打开夹爪
  auto stage_open_hand =
      std::make_unique<mtc::stages::MoveTo>("open hand", interpolation_planner);
  stage_open_hand->setGroup(hand_group_name);
  stage_open_hand->setGoal("open");
  task.add(std::move(stage_open_hand));

  auto stage_move_to_pick = std::make_unique<mtc::stages::Connect>(
      "move to pick", mtc::stages::Connect::GroupPlannerVector{
                          {arm_group_name, sampling_planner}});
  stage_move_to_pick->setTimeout(5.0);
  stage_move_to_pick->properties().configureInitFrom(mtc::Stage::PARENT);
  task.add(std::move(stage_move_to_pick));

  // 为什么当把下面的内容封闭之后，这个语句就失效了
  mtc::Stage *attach_object_stage = nullptr;

  {
    // 这里用来封装子阶段，使用mtc::SerialContainer
    auto grasp = std::make_unique<mtc::SerialContainer>("pick object");
    task.properties().exposeTo(grasp->properties(),
                               {"eef", "group", "ik_frame"});
    grasp->properties().configureInitFrom(mtc::Stage::PARENT,
                                          {"eef", "group", "ik_frame"});
    {
      // MoveRelative用于定义移动阶段，是相对目标，比如在当前位置上向某个坐标轴方向偏移多少
      auto stage = std::make_unique<mtc::stages::MoveRelative>(
          "approach object", cartesian_planner);
      stage->properties().set("marker_ns", "approach_object");
      stage->properties().set("link", hand_frame);
      stage->properties().configureInitFrom(mtc::Stage::PARENT, {"group"});
      stage->setMinMaxDistance(0.00, 2.0);

      // 设置手部方向,用一个三维向量描述运动方向
      geometry_msgs::msg::Vector3Stamped vec;
      vec.header.frame_id = hand_frame;
      vec.vector.z = 1.0;
      stage->setDirection(vec);
      grasp->insert(std::move(stage));
    }

    {
      // GenerateGraspPose生成抓取姿势
      auto stage = std::make_unique<mtc::stages::GenerateGraspPose>(
          "generate grasp pose");
      stage->properties().configureInitFrom(mtc::Stage::PARENT);
      stage->properties().set("marker_ns", "grasp_pose");
      stage->setPreGraspPose("open");
      stage->setObject("object");
      stage->setAngleDelta(M_PI / 30);
      stage->setMonitoredStage(current_state_ptr); // Hook into current state
      // Eigen::Isometry3d定义一个 3D 欧式变换矩阵
      Eigen::Isometry3d grasp_frame_transform;
      Eigen::Quaterniond q =
          Eigen::AngleAxisd(M_PI / 2, Eigen::Vector3d::UnitX()) *
          Eigen::AngleAxisd(M_PI / 2, Eigen::Vector3d::UnitY()) *
          Eigen::AngleAxisd(M_PI / 2, Eigen::Vector3d::UnitZ());
      grasp_frame_transform.linear() = q.matrix();
      grasp_frame_transform.translation().z() = 0.1;

      // IK求解器
      auto wrapper = std::make_unique<mtc::stages::ComputeIK>("grasp pose IK",
                                                              std::move(stage));
      wrapper->setMaxIKSolutions(60);
      wrapper->setMinSolutionDistance(0.5);
      wrapper->setIKFrame(grasp_frame_transform, hand_frame);
      wrapper->properties().configureInitFrom(mtc::Stage::PARENT,
                                              {"eef", "group"});
      wrapper->properties().configureInitFrom(mtc::Stage::INTERFACE,
                                              {"target_pose"});
      grasp->insert(std::move(wrapper));
    }

    {
      // ModifyPlanningScene允许发生碰撞
      auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>(
          "allow collision (hand,object)");
      stage->allowCollisions("object",
                             task.getRobotModel()
                                 ->getJointModelGroup(hand_group_name)
                                 ->getLinkModelNamesWithCollisionGeometry(),
                             true);
      grasp->insert(std::move(stage));
    }

    {
      // MoveTo向固定点移动
      auto stage = std::make_unique<mtc::stages::MoveTo>("close hand",
                                                         interpolation_planner);
      stage->setGroup(hand_group_name);
      stage->setGoal("close");
      grasp->insert(std::move(stage));
    }

    {
      // 使物体附着在手上
      auto stage =
          std::make_unique<mtc::stages::ModifyPlanningScene>("attach object");
      stage->attachObject("object", hand_frame);
      attach_object_stage = stage.get();
      grasp->insert(std::move(stage));
    }

    {
      // 抬起物体
      auto stage = std::make_unique<mtc::stages::MoveRelative>(
          "lift object", cartesian_planner);
      stage->properties().configureInitFrom(mtc::Stage::PARENT, {"group"});
      stage->setMinMaxDistance(0.00, 2.0);
      stage->setIKFrame(hand_frame);
      stage->properties().set("marker_ns", "lift_object");

      // 设置向上平移方向
      geometry_msgs::msg::Vector3Stamped vec;
      vec.header.frame_id = "world";
      vec.vector.z = 1.0;
      stage->setDirection(vec);
      grasp->insert(std::move(stage));
    }

    task.add(std::move(grasp));
  }

  {
    auto stage_move_to_place = std::make_unique<mtc::stages::Connect>(
        "move to place", mtc::stages::Connect::GroupPlannerVector{
                             {arm_group_name, sampling_planner},
                             {hand_group_name, interpolation_planner}});
    stage_move_to_place->setTimeout(5.0);
    stage_move_to_place->properties().configureInitFrom(mtc::Stage::PARENT);
    task.add(std::move(stage_move_to_place));
  }

  {
    auto place = std::make_unique<mtc::SerialContainer>("place object");
    task.properties().exposeTo(place->properties(),
                               {"eef", "group", "ik_frame"});
    place->properties().configureInitFrom(mtc::Stage::PARENT,
                                          {"eef", "group", "ik_frame"});

    {
      // Sample place pose
      auto stage = std::make_unique<mtc::stages::GeneratePlacePose>(
          "generate place pose");
      stage->properties().configureInitFrom(mtc::Stage::PARENT);
      stage->properties().set("marker_ns", "place_pose");
      stage->setObject("object");

      geometry_msgs::msg::PoseStamped target_pose_msg;
      target_pose_msg.header.frame_id = "world";
      target_pose_msg.pose.position.x = 0.20;
      target_pose_msg.pose.position.y = 0.15;
      target_pose_msg.pose.position.z = 0.15;
      target_pose_msg.pose.orientation.w = 1.0;

      stage->setPose(target_pose_msg);
      stage->setMonitoredStage(
          attach_object_stage); // Hook into attach_object_stage
      // 尝试更多角度：在目标位置周围沿 z 轴旋转多个偏航角，分别做 IK 求解
      // 72 个角度采样 -> 每 5 度一个
      // for (int i = 0; i < samples; ++i) {
      //   double yaw = (2.0 * M_PI * i) / static_cast<double>(samples);

      //   geometry_msgs::msg::PoseStamped pose_i = target_pose_msg;

      //   // 使用 Eigen 构造绕 Z 轴的旋转四元数
      //   Eigen::Quaterniond q_yaw(
      //       Eigen::AngleAxisd(yaw, Eigen::Vector3d::UnitZ()));
      //   // 保留原始朝向的旋转再叠加偏航（若需要保留原始
      //   // orientation，可乘以原来的）
      //   Eigen::Quaterniond orig_q(
      //       pose_i.pose.orientation.w, pose_i.pose.orientation.x,
      //       pose_i.pose.orientation.y, pose_i.pose.orientation.z);
      //   Eigen::Quaterniond final_q = q_yaw * orig_q;

      //   pose_i.pose.orientation.x = final_q.x();
      //   pose_i.pose.orientation.y = final_q.y();
      //   pose_i.pose.orientation.z = final_q.z();
      //   pose_i.pose.orientation.w = final_q.w();

      //   // 为每个采样角创建一个 GeneratePlacePose stage（名字带索引以区分）
      //   auto gen_name = std::string("generate place pose ") +
      //   std::to_string(i); auto stage_i =
      //       std::make_unique<mtc::stages::GeneratePlacePose>(gen_name);
      //   stage_i->properties().configureInitFrom(mtc::Stage::PARENT);
      //   stage_i->properties().set("marker_ns", "place_pose");
      //   stage_i->setObject("object");
      //   stage_i->setPose(pose_i);
      //   stage_i->setMonitoredStage(attach_object_stage);

      //   // 用 ComputeIK 包装并插入到 place 容器
      //   auto ik_name = std::string("place pose IK ") + std::to_string(i);
      //   auto wrapper_i = std::make_unique<mtc::stages::ComputeIK>(
      //       ik_name, std::move(stage_i));
      //   wrapper_i->setMaxIKSolutions(60);
      //   wrapper_i->setMinSolutionDistance(0.1);
      //   wrapper_i->setIKFrame("object");
      //   wrapper_i->properties().configureInitFrom(mtc::Stage::PARENT,
      //                                             {"eef", "group"});
      //   wrapper_i->properties().configureInitFrom(mtc::Stage::INTERFACE,
      //                                             {"target_pose"});
      //   place->insert(std::move(wrapper_i));
      // }

      // ... (代码承接 place 容器定义) ...

      // 以下为并行容器内容
      // 以上为并行容器内容

      // Compute IK
      auto wrapper = std::make_unique<mtc::stages::ComputeIK>("place pose IK",
                                                              std::move(stage));
      wrapper->setMaxIKSolutions(60);
      wrapper->setMinSolutionDistance(0.1);
      wrapper->setIKFrame("object");
      wrapper->properties().configureInitFrom(mtc::Stage::PARENT,
                                              {"eef", "group"});
      wrapper->properties().configureInitFrom(mtc::Stage::INTERFACE,
                                              {"target_pose"});
      place->insert(std::move(wrapper));
    }

    {
      auto stage = std::make_unique<mtc::stages::MoveTo>("open hand",
                                                         interpolation_planner);
      stage->setGroup(hand_group_name);
      stage->setGoal("open");
      place->insert(std::move(stage));
    }

    {
      auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>(
          "forbid collision (hand,object)");
      stage->allowCollisions("object",
                             task.getRobotModel()
                                 ->getJointModelGroup(hand_group_name)
                                 ->getLinkModelNamesWithCollisionGeometry(),
                             false);
      place->insert(std::move(stage));
    }

    {
      // 接触碰撞
      auto stage =
          std::make_unique<mtc::stages::ModifyPlanningScene>("detach object");
      stage->detachObject("object", hand_frame);
      place->insert(std::move(stage));
    }

    {
      auto stage = std::make_unique<mtc::stages::MoveRelative>(
          "retreat", cartesian_planner);
      stage->properties().configureInitFrom(mtc::Stage::PARENT, {"group"});
      stage->setMinMaxDistance(0.00, 2.0);
      stage->setIKFrame(hand_frame);
      stage->properties().set("marker_ns", "retreat");

      // Set retreat direction
      geometry_msgs::msg::Vector3Stamped vec;
      vec.header.frame_id = "world";
      vec.vector.z = 1.0;
      stage->setDirection(vec);
      place->insert(std::move(stage));
    }

    task.add(std::move(place));
  }

  // {
  //   auto stage = std::make_unique<mtc::stages::MoveTo>("return home",
  //                                                      interpolation_planner);
  //   stage->properties().configureInitFrom(mtc::Stage::PARENT, {"group"});
  //   stage->setGoal("ready");
  //   task.add(std::move(stage));
  // }

  // task.setProperty("topic", std::string("solution"));

  return task;
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