#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <chrono>

using namespace std::chrono_literals;

class CirclePublisher : public rclcpp::Node
{
public:
  CirclePublisher() : Node("circle_publisher")
  {
    pub_ = create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
    timer_ = create_wall_timer(100ms, std::bind(&CirclePublisher::timerCallback, this));
    RCLCPP_INFO(get_logger(), "Publishing velocity commands to make the turtle move in a circle");
  }

  void timerCallback()
  {
    auto message = geometry_msgs::msg::Twist();
    message.linear.x = 1.0;  // Linear velocity in the x direction
    message.angular.z = 1.0; // Angular velocity around the z axis
    pub_->publish(message);
  }

private:
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<CirclePublisher>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
