#!/bin/sh
sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
sudo apt-get update && apt-get upgrade
sudo apt-get install xterm
sudo pip install --upgrade pip
sudo pip3 install --upgrade pip
sudo pip install rospkg
sudo pip3 install rospkg
source /opt/ros/kinetic/setup.bash
catkin_make
source devel/setup.bash
cd src/
git clone https://github.com/ros-perception/slam_gmapping.git  
git clone https://github.com/turtlebot/turtlebot.git  
git clone https://github.com/turtlebot/turtlebot_interactions.git  
git clone https://github.com/turtlebot/turtlebot_simulator.git
rosdep -i install gmapping -y
rosdep -i install turtlebot_teleop -y
rosdep -i install turtlebot_rviz_launchers -y
rosdep -i install turtlebot_gazebo -y
cd ../
catkin_make
source devel/setup.bash
