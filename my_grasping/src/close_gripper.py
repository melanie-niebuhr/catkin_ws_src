#!/usr/bin/env python

import sys
import rospy
import moveit_commander
import geometry_msgs.msg

#Initialisiere MoveIt sowie Nodes und Publisher, instanziiere diverse Objekte
moveit_commander.roscpp_initialize(sys.argv)
rospy.init_node("ur_node_me", anonymous=True)
robot = moveit_commander.RobotCommander()

g_group = moveit_commander.MoveGroupCommander("gripper")
# close the gripper
g_group.set_named_target("closed")
plan2 = g_group.go()

rospy.sleep(5)
moveit_commander.roscpp_shutdown()