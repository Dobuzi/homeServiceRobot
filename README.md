# homeServiceRobot

SLAM and Path Planning for home service robot with ros

# Play Video

![Home Service Robot](homeService.gif)

# How to use

1. On ubuntu (VM or Raw)

```
git clone https://github.com/Dobuzi/homeServiceRobot.git
cd homeServiceRobot
chmod +x src/scripts/initialize.sh
./src/scripts/initialize.sh
chmod +x src/scripts/home_service.sh
./src/scripts/home_service.sh
```

2. On docker container (ros:kinetic)

```
git clone https://github.com/Dobuzi/homeServiceRobot.git
cd homeServiceRobot
chmod +x src/scripts/initialize_docker.sh
./src/scripts/initialize_docker.sh
chmod +x src/scripts/home_service.sh
./src/scripts/home_service.sh
```

# Dependency

-   OS : Linux (Ubuntu xenial 16.04 LTS)
-   ROS : kinetic
-   gmapping : For performing SLAM and build a map of the environment (with laser range finder and RGB-D cameras).
-   turtlebot_teleop : To manually control thr robot using keyboard commands.
-   turtlebot_rviz_launchers : To load the robot model, trajectories and map for navigating with rviz.
-   turtlebot_gazebo : To Deploy a turtlebot for simulating the gazebo world.

# Scripts (in src/scripts folder)

0. initialize.sh : Set up for the workspace
1. test_slam.sh : SLAM Testing
2. test_navigation.sh : Localization and Navigation Testing
3. pick_object.sh : Navigation and Goal Node (Path Finding)
4. add_marker.sh : Virtual Objects (Make goal with marker)
5. home_service.sh : Make goal and make the path finding. (pick up and drop off the object)

## Reference

-   [Udacity](https://www.udacity.com)
