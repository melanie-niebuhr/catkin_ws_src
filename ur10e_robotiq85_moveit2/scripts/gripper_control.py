#!/usr/bin/env python

# Python 2/3 compatibility imports
from __future__ import print_function
from six.moves import input

import sys
import copy
import rospy
import moveit_commander
import moveit_msgs.msg
import geometry_msgs.msg
from math import pi
from std_msgs.msg import String
from moveit_commander.conversions import pose_to_list

# set_gripper
import actionlib
import control_msgs.msg

# Initialisiere MoveIt sowie Nodes und Publisher, instanziiere diverse Objekte
moveit_commander.roscpp_initialize(sys.argv)
robot = moveit_commander.RobotCommander()
scene = moveit_commander.PlanningSceneInterface()
m_group = moveit_commander.MoveGroupCommander("manipulator")
g_group = moveit_commander.MoveGroupCommander("gripper")

# Action client for controlling 2f85 gripper
# value is from 0.0 to 0.8
def set_gripper(value):
    rospy.init_node('gripper_command')

    client = actionlib.SimpleActionClient('/gripper_controller/gripper_cmd', control_msgs.msg.GripperCommandAction)
    client.wait_for_server()

    goal = control_msgs.msg.GripperCommandGoal()
    goal.command.position = value
    goal.command.max_effort = -1.0  # Do not limit the effort
    client.send_goal(goal)

    client.wait_for_result()
    return client.get_result()
## path & grasp planning with exact position values
# close gripper (value=0.8)
set_gripper(0.0)

rospy.sleep(2)

# semi-open gripper (value=0.4)
set_gripper(0.4)

## Manipulator pose
joint_goal = m_group.get_current_joint_values()
joint_goal[0] = pi
joint_goal[1] = -pi/2
joint_goal[2] = pi/3
joint_goal[3] = -pi/2
joint_goal[4] = pi/3
joint_goal[5] = pi

m_group.go(joint_goal, wait=True)
m_group.stop()

## path planning with predefined poses
# put the manipulator in the elbow/home position
m_group.set_named_target("home")
plan1 = m_group.go()

# open/close the gripper
g_group.set_named_target("closed")
plan2 = g_group.go()

rospy.sleep(2)
moveit_commander.roscpp_shutdown()













