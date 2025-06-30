#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <chrono>

using namespace std::chrono_literals;

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("turtle_draw_8");
    
    auto publisher = node->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
    
    geometry_msgs::msg::Twist msg;
    rclcpp::Rate rate(1);  // 1 Hz
    
    RCLCPP_INFO(node->get_logger(), "Drawing figure 8...");
    
    // Draw two circles to make a figure 8
    for (int circle = 0; circle < 2; circle++) {
        msg.linear.x = 2.0;   // Forward speed
        msg.angular.z = (circle == 0) ? -2.0 : 2.0;  // First circle clockwise, second counter-clockwise
        
        // Draw circle for ~3 seconds (one complete circle)
        for (int i = 0; i < 3; i++) {
            publisher->publish(msg);
            rclcpp::spin_some(node);
            rate.sleep();
        }
    }
    
    // Stop the turtle
    msg.linear.x = 0.0;
    msg.angular.z = 0.0;
    publisher->publish(msg);
    
    RCLCPP_INFO(node->get_logger(), "Figure 8 complete!");
    
    rclcpp::shutdown();
    return 0;
}