#!/bin/sh
sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
sudo apt-get update -y && apt-get upgrade -y
sudo apt-get install xterm python-pip python3-pip -y
sudo python -m pip install --upgrade pip
sudo python3 -m pip3 install --upgrade pip
sudo python -m pip install rospkg
sudo python3 -m pip3 install rospkg
source /opt/ros/kinetic/setup.bash
catkin_make
source devel/setup.bash
cd src/
git clone https://github.com/ros-perception/slam_gmapping.git  
git clone https://github.com/turtlebot/turtlebot.git  
git clone https://github.com/turtlebot/turtlebot_interactions.git  
git clone https://github.com/turtlebot/turtlebot_simulator.git
cd ../
source devel/setup.bash
rosdep -i install gmapping -y
rosdep -i install turtlebot_teleop -y
rosdep -i install turtlebot_rviz_launchers -y
rosdep -i install turtlebot_gazebo -y
catkin_make
source devel/setup.bash
