#include "../include/arm5dof_movegroup/color_detect.hpp"

int main(int argc, char **argv) {
  // 检查输入参数
  rclcpp::init(argc, argv);

  if (argc < 2) {
    std::cout << "请提供视频文件路径，如：./color_detect video.mp4"
              << std::endl;
    return -1;
  }

  // 打开视频
  cv::VideoCapture cap(argv[1]);
  if (!cap.isOpened()) {
    std::cout << "无法打开视频文件：" << argv[1] << std::endl;
    return -1;
  }

  // 定义颜色范围（HSV）
  std::vector<ColorRange> colorRanges = {
      // 红色有两个范围（环形），这里只示例一个范围
      {cv::Scalar(0, 120, 70), cv::Scalar(10, 255, 255), "Red",
       cv::Scalar(0, 0, 255)},
      // 蓝色
      {cv::Scalar(100, 150, 70), cv::Scalar(130, 255, 255), "Blue",
       cv::Scalar(255, 0, 0)},
      // 绿色
      {cv::Scalar(40, 70, 70), cv::Scalar(80, 255, 255), "Green",
       cv::Scalar(0, 255, 0)}};

  cv::Mat frame;
  while (true) {
    cap >> frame;
    if (frame.empty())
      break;

    cv::Mat hsv;
    cvtColor(frame, hsv, cv::COLOR_BGR2HSV);

    cv::Mat result = frame.clone();

    for (const auto &colorRange : colorRanges) {
      detectColor(hsv, result, colorRange);
    }

    imshow("Color Detection", result);
    if (cv::waitKey(30) == 27)
      break; // 按 ESC 退出
  }
  // rclcpp::spin(std::make_shared<ColorNode>());

  cap.release();
  cv::destroyAllWindows();
  rclcpp::shutdown();
  return 0;
}
