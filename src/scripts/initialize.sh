#!/bin/sh
sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
sudo apt-get update -y && apt-get upgrade -y
sudo apt-get install xterm python3-pip -y
cd src/
git clone https://github.com/ros-perception/slam_gmapping.git  
git clone https://github.com/turtlebot/turtlebot.git  
git clone https://github.com/turtlebot/turtlebot_interactions.git  
git clone https://github.com/turtlebot/turtlebot_simulator.git
cd ../
catkin_make
chmod +x devel/setup.bash
. devel/setup.bash
catkin_make
. devel/setup.bash
rosdep -i install gmapping -y
rosdep -i install turtlebot_teleop -y
rosdep -i install turtlebot_rviz_launchers -y
rosdep -i install turtlebot_gazebo -y
. devel/setup.bash
catkin_make
. devel/setup.bash
