#!/bin/sh
sudo apt-get update && apt-get upgrade
sudo apt-get install xterm
sudo pip install --upgrade pip
sudo pip3 install --upgrade pip
sudo pip install rospkg
sudo pip3 install rospkg
catkin_make
source devel/setup.bash
rosdep -i install gmapping
rosdep -i install turtlebot_teleop
rosdep -i install turtlebot_rviz_launchers
rosdep -i install turtlebot_gazebo
catkin_make
source devel/setup.bash