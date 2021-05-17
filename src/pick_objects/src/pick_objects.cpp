#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv) {
  ros::init(argc, argv, "pick_objects");

  MoveBaseClient ac("move_base", true);

  while(!ac.waitForServer(ros::Duration(5.0))) {
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  goal.target_pose.pose.position.x = 1.0;
  goal.target_pose.pose.orientation.w = 1.0;

  ROS_INFO("Sending goal: pick the ball");
  ac.sendGoal(goal);

  ac.waitForResult();

  if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
    ROS_INFO("The robot pick the ball");
  } else {
    ROS_INFO("Failed (pick the ball)");
  }

  ros::Duration(5.0).sleep();

  goal.target_pose.pose.position.x = 0.1;
  goal.target_pose.pose.orientation.w = 1.0;

  ROS_INFO("Sending goal: go to the drop-off zone");
  ac.sendGoal(goal);

  ac.waitForResult();

  if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
    ROS_INFO("The robot drop off the ball");
  } else {
    ROS_INFO("Failed (drop-off the ball)");
  }

  return 0;
}
