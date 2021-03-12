cmake_minimum_required(VERSION 3.1.3)
project(ur10e_robotiq85_moveit2)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  gazebo_ros
  rospy
  control_toolbox
  std_msgs
  xmlrpcpp
)

FIND_PACKAGE(gazebo REQUIRED)
FIND_PACKAGE(Boost REQUIRED COMPONENTS thread)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")

CATKIN_PACKAGE(
  DEPENDS
    roscpp
    gazebo_ros
    control_toolbox
    xmlrpcpp
)

LINK_DIRECTORIES(
  ${GAZEBO_LIBRARY_DIRS}
)
INCLUDE_DIRECTORIES(
  ${Boost_INCLUDE_DIR}
  ${catkin_INCLUDE_DIRS}
  ${GAZEBO_INCLUDE_DIRS}
  include
)

ADD_LIBRARY(gazebo_mimic_joint_plugin src/mimic_joint_plugin.cpp)
TARGET_LINK_LIBRARIES(gazebo_mimic_joint_plugin
  ${catkin_LIBRARIES}
  ${GAZEBO_LIBRARIES})

ADD_LIBRARY(gazebo_disable_link_plugin src/disable_link_plugin.cpp)
TARGET_LINK_LIBRARIES(gazebo_disable_link_plugin
  ${catkin_LIBRARIES}
  ${GAZEBO_LIBRARIES})


install(DIRECTORY launch DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
  PATTERN "setup_assistant.launch" EXCLUDE)
install(DIRECTORY config DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
