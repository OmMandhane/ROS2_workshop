#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <turtlesim/msg/pose.hpp>
#include <cmath>

using namespace std::chrono_literals;

class EightPublisher : public rclcpp::Node
{
public:
  EightPublisher() : Node("eight_publisher"), first_circle_(true), initial_position_recorded_(false)
  {
    pub_ = create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
    sub_ = create_subscription<turtlesim::msg::Pose>(
      "/turtle1/pose", 10, std::bind(&EightPublisher::poseCallback, this, std::placeholders::_1));

    RCLCPP_INFO(get_logger(), "Subscribing to pose and publishing velocity commands to draw a figure-8");
  }

private:
  void poseCallback(const turtlesim::msg::Pose::SharedPtr msg)
  {
    current_pose_ = *msg;

    if (!initial_position_recorded_) {
      initial_position_ = current_pose_;
      initial_position_recorded_ = true;
      RCLCPP_INFO(get_logger(), "Initial position recorded: x=%.2f, y=%.2f", initial_position_.x, initial_position_.y);
    }

    publishCommand();
  }

  void publishCommand()
  {
    auto message = geometry_msgs::msg::Twist();
    message.linear.x = 1.0;

    if (first_circle_) {
      // Draw the first circle with positive angular velocity
      message.angular.z = 1.0;
      if (isBackToStart()) {
        first_circle_ = false;
        RCLCPP_INFO(get_logger(), "Completed first circle. Starting second circle.");
      }
    } else {
      // Draw the second circle with negative angular velocity
      message.angular.z = -1.0;
      if (isBackToStart()) {
        RCLCPP_INFO(get_logger(), "Completed second circle. Figure-8 complete. Shutting down.");
        stopMoving();
        rclcpp::shutdown();
        return;
      }
    }

    pub_->publish(message);
  }

  bool isBackToStart()
  {
    if (current_pose_.x == initial_position_.x && current_pose_.y == initial_position_.y){
        return true;
    } else{
        return false;
    }

  }

  void stopMoving()
  {
    auto message = geometry_msgs::msg::Twist();
    pub_->publish(message); // Publish zero velocity to stop
  }

  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub_;
  rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr sub_;

  turtlesim::msg::Pose current_pose_;
  turtlesim::msg::Pose initial_position_;

  bool first_circle_;
  bool initial_position_recorded_;
};

int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<EightPublisher>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
