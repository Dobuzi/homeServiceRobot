#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <visualization_msgs/Marker.h>

void getGoal(const visualization_msgs::Marker::ConstPtr& msg);

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

double goal_position[2] = {0, 0};

int main(int argc, char** argv) {
  ros::init(argc, argv, "pick_objects");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Subscriber marker_sub = n.subscribe("/visualization_marker", 1, getGoal);

  while (ros::ok())
  {

    MoveBaseClient ac("move_base", true);

    while(!ac.waitForServer(ros::Duration(5.0))) {
      ROS_INFO("Waiting for the move_base action server to come up");
    }

    move_base_msgs::MoveBaseGoal goal;

    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();

    goal.target_pose.pose.position.x = goal_position[0];
    goal.target_pose.pose.position.y = goal_position[1];
    goal.target_pose.pose.orientation.w = 1.0;

    ROS_INFO("Sending the goal");
    ac.sendGoal(goal);

    ac.waitForResult();

    if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
      ROS_INFO("The robot reached the goal");
    } else {
      ROS_INFO("Failed");
    }
  
    ros::spinOnce();
  }
  return 0;
}

void getGoal(const visualization_msgs::Marker::ConstPtr& msg)
{
  goal_position[0] = msg->pose.position.x;
  goal_position[1] = msg->pose.position.y;  
}
