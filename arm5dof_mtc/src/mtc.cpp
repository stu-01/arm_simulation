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
  object.primitives[0].dimensions = {0.2, 0.02};

  geometry_msgs::msg::Pose pose;
  pose.position.x = 0.3;
  pose.position.y = 0.0;
  pose.position.z = 0.1;
  pose.orientation.w = 1.0;
  object.pose = pose;

  // 将碰撞物体添加到规划场景中
  moveit::planning_interface::PlanningSceneInterface psi;
  psi.applyCollisionObject(object);
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

  // 添加移动到预抓取位置
  auto stage_open_hand =
      // 使用MoveTo移动，是绝对目标，比如描述文件内置的动作，或某个固定座标的点
      std::make_unique<mtc::stages::MoveTo>("open hand", interpolation_planner);
  stage_open_hand->setGroup(hand_group_name);
  stage_open_hand->setGoal("open");
  // add将顶级阶段添加到任务中
  task.add(std::move(stage_open_hand));

  // 为什么当把下面的内容封闭之后，这个语句就失效了
  mtc::Stage *attach_object_stage = nullptr;

  // 一个串行容器，并没有被添加到任务中
  {
    // 这里用来封装子阶段，使用mtc::SerialContainer
    auto grasp = std::make_unique<mtc::SerialContainer>("pick object");
    // exposeTo是将父任务task的关键属性都暴露给子任务
    task.properties().exposeTo(grasp->properties(),
                               {"eef", "group", "ik_frame"});
    // configureInitFrom初始化父任务属性，允许串行容器内访问这些属性
    grasp->properties().configureInitFrom(mtc::Stage::PARENT,
                                          {"eef", "group", "ik_frame"});
    {
      // MoveRelative用于定义移动阶段，是相对目标，比如在当前位置上向某个坐标轴方向偏移多少
      auto stage = std::make_unique<mtc::stages::MoveRelative>(
          "approach object", cartesian_planner);
      // .set用于设置具体的值
      stage->properties().set("marker_ns", "approach_object");
      stage->properties().set("link", hand_frame);
      // .configureInitFrom用于设置值的来源
      // “PARENT”指值的来源是紧邻该阶段的上一个阶段的结束状态（串行容器外）
      stage->properties().configureInitFrom(mtc::Stage::PARENT, {"group"});
      stage->setMinMaxDistance(0.1, 0.15);

      // 设置手部方向
      geometry_msgs::msg::Vector3Stamped vec;
      vec.header.frame_id = hand_frame;
      vec.vector.z = 1.0;
      stage->setDirection(vec);
      // insert将子阶段添加到容器中
      grasp->insert(std::move(stage));
    }

    {
      // GenerateGraspPose生成抓取姿势
      // 创建实例并命名
      auto stage = std::make_unique<mtc::stages::GenerateGraspPose>(
          "generate grasp pose");
      // 初始化属性，从上一阶段继承机器人状态
      stage->properties().configureInitFrom(mtc::Stage::PARENT);
      // rviz可视化命名空间，可以在motion planning插件中调试
      stage->properties().set("marker_ns", "grasp_pose");
      // 设置预抓取姿态，必须是srdf文件中配置过的
      stage->setPreGraspPose("open");
      // 设置目标物体，必须已经加入规划场景
      stage->setObject("object");
      // 设置角度增量，求解时每pi/12一次
      stage->setAngleDelta(M_PI / 12);
      // 声明当前状态指的是current所对应的状态
      stage->setMonitoredStage(current_state_ptr); // Hook into current state
      // Eigen::Isometry3d定义一个 3D 欧式变换矩阵
      Eigen::Isometry3d grasp_frame_transform;
      // Eigen::Quaterniond双精度浮点数表示的四元数
      Eigen::Quaterniond q =
          // 乘法表示旋转的串联
          Eigen::AngleAxisd(M_PI / 2, Eigen::Vector3d::UnitX()) *
          Eigen::AngleAxisd(M_PI / 2, Eigen::Vector3d::UnitY()) *
          Eigen::AngleAxisd(M_PI / 2, Eigen::Vector3d::UnitZ());
      // linear访问变换矩阵左上角3*3的线性变换矩阵（旋转部分）
      // matrix将四元数转换为一个3*3的旋转矩阵
      grasp_frame_transform.linear() = q.matrix();
      // translation访问平移部分，在z轴方向平移0.1
      grasp_frame_transform.translation().z() = 0.1;

      // Compute IK
      auto wrapper = std::make_unique<mtc::stages::ComputeIK>("grasp pose IK",
                                                              std::move(stage));
      // 解的最多数量
      wrapper->setMaxIKSolutions(10);
      // 最小解距离，差距小于该距离的两个解视为相似，其一无效
      wrapper->setMinSolutionDistance(1.0);
      // 设置IK求解的目标姿态和参考连杆
      wrapper->setIKFrame(grasp_frame_transform, hand_frame);
      wrapper->properties().configureInitFrom(mtc::Stage::PARENT,
                                              {"eef", "group"});
      // INTERFACE指定属性的值来源是前一个已成功执行的MTC阶段的输出
      wrapper->properties().configureInitFrom(
          mtc::Stage::INTERFACE,
          // target_pose是MTC 框架内部使用的标准接口名称
          {"target_pose"});
      // 将生成抓取姿势与解算过程放入子序列中
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
      stage->setMinMaxDistance(0.1, 0.3);
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
      target_pose_msg.header.frame_id = "object";
      target_pose_msg.pose.position.y = 0.5;
      target_pose_msg.pose.orientation.w = 1.0;
      stage->setPose(target_pose_msg);
      stage->setMonitoredStage(
          attach_object_stage); // Hook into attach_object_stage

      // Compute IK
      auto wrapper = std::make_unique<mtc::stages::ComputeIK>("place pose IK",
                                                              std::move(stage));
      wrapper->setMaxIKSolutions(10);
      wrapper->setMinSolutionDistance(2.0);
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
      auto stage =
          std::make_unique<mtc::stages::ModifyPlanningScene>("detach object");
      stage->detachObject("object", hand_frame);
      place->insert(std::move(stage));
    }

    {
      auto stage = std::make_unique<mtc::stages::MoveRelative>(
          "retreat", cartesian_planner);
      stage->properties().configureInitFrom(mtc::Stage::PARENT, {"group"});
      stage->setMinMaxDistance(0.1, 0.3);
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

  {
    auto stage = std::make_unique<mtc::stages::MoveTo>("return home",
                                                       interpolation_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, {"group"});
    stage->setGoal("ready");
    task.add(std::move(stage));
  }
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