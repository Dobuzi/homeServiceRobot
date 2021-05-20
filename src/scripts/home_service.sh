#!/bin/sh
xterm -e "cd /home/workspace/catkin_ws && source devel/setup.bash && export TURTLEBOT_GAZEBO_WORLD_FILE=/home/workspace/catkin_ws/src/map/JongWonKim.world && roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 10
xterm -e "cd /home/workspace/catkin_ws && source devel/setup.bash && export TURTLEBOT_GAZEBO_MAP_FILE=/home/workspace/catkin_ws/src/map/map.yaml && roslaunch turtlebot_gazebo amcl_demo.launch" &
sleep 5
xterm -e "cd /home/workspace/catkin_ws && source devel/setup.bash && roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm -e "cd /home/workspace/catkin_ws && source devel/setup.bash && rosrun add_markers add_markers" &
sleep 5
xterm -e "cd /home/workspace/catkin_ws && source devel/setup.bash && roslaunch pick_objects pick_objects.launch"


