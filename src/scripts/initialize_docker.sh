#!/bin/sh
apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key 2930ADAE8CAF5059EE73BB4B58712A2291FA4AD5
apt-get update -y && apt-get upgrade -y
apt-get install xterm python-pip python3-pip -y
python -m pip install --upgrade pip
python3 -m pip3 install --upgrade pip
python -m pip install rospkg
python3 -m pip3 install rospkg
cd src/
git clone https://github.com/ros-perception/slam_gmapping.git  
git clone https://github.com/turtlebot/turtlebot.git  
git clone https://github.com/turtlebot/turtlebot_interactions.git  
git clone https://github.com/turtlebot/turtlebot_simulator.git
cd ../
. /opt/ros/kinetic/setup.bash
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
