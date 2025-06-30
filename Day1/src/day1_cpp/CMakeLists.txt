cmake_minimum_required(VERSION 3.8)
project(day1_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(turtlesim REQUIRED)

add_executable(simple_publisher src/simple_publisher.cpp)
ament_target_dependencies(simple_publisher rclcpp std_msgs)

add_executable(simple_subscriber src/simple_subscriber.cpp)
ament_target_dependencies(simple_subscriber rclcpp std_msgs)

add_executable(task1 src/task1.cpp)
ament_target_dependencies(task1 rclcpp std_msgs geometry_msgs)

add_executable(task2 src/task2.cpp)
ament_target_dependencies(task2 turtlesim rclcpp std_msgs geometry_msgs)

add_executable(task2_2 src/task2_2.cpp)
ament_target_dependencies(task2_2 turtlesim rclcpp std_msgs geometry_msgs)

install(TARGETS
  simple_publisher
  simple_subscriber
  task1
  task2
  task2_2
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()