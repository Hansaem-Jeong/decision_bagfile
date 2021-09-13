cmake_minimum_required(VERSION 3.0.2)
project(data_bagfile)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)

add_message_files(
  FILES
  aes_data.msg
  Chassis.msg
  Sensor.msg
  Traffic.msg
  Line.msg
  AEB.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  INCLUDE_DIRS 
    include
  LIBRARIES 
    ${PROJECT_NAME}_node
  CATKIN_DEPENDS 
    roscpp 
    rospy 
    std_msgs 
    message_runtime
  DEPENDS 
    system_lib
)

include_directories(
  include
  src
  ${catkin_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}_node 
  node/data_pub_node.cpp
)

target_link_libraries(${PROJECT_NAME}_node
  ${catkin_LIBRARIES}
)

add_dependencies(${PROJECT_NAME}_node 
  ${${PROJECT_NAME}_EXPORTED_TARGETS} 
  ${catkin_EXPORTED_TARGETS}
)
