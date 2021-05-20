#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
#include <math.h>

visualization_msgs::Marker setMarker(visualization_msgs::Marker marker, double position[3], double orientation[4], double scale[3], float color[3], double alpha);
void getPosition(const nav_msgs::Odometry::ConstPtr& msg);
double getDistance(double goal[2], double position[2]);
bool isReached(double distance, double threshold);

double robot_position[2] = {0, 0};

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  // Subscribe odom
  ros::Subscriber odom_sub = n.subscribe("/odom", 10, getPosition);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  int step = 0;
  // 0 : drive to pickup zone
  // 1 : picked object (hide and wait 5 seconds)
  // 2 : drive to drop off zone
  // 3 : drop off the object

  double pick_up_zone[2] = {3, 0};
  double drop_off_zone[2] = {-3, -0.5};  
  double threshold = 0.3;
  double distance = 99999;
  int wait = 0;

  double goal_position[3] = {1, 1, 0};
  double orientation[4] = {0.0, 0.0, 0.0, 1.0};
  double scale[3] = {0.3, 0.3, 0.3};
  float color[3] = {0.0f, 1.0f, 0.0f};
  double alpha = 1.0;

  while (ros::ok())
  {
    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "marker_cube";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;
    
    switch (step) {
      case 0:
        goal_position[0] = pick_up_zone[0];
        goal_position[1] = pick_up_zone[1];
        marker.action = visualization_msgs::Marker::ADD;
        distance = getDistance(pick_up_zone, robot_position);
        if (isReached(distance, threshold)) {
          step = 1;
        } else {
          ROS_INFO_STREAM("Drive to the pickup zone ; distance: " << distance);
        }
        break;
      case 1:
        marker.action = visualization_msgs::Marker::DELETE;
        if (wait >= 5) {
          wait = 0;
          step = 2;
          ROS_INFO("Picked up the object");
        } else {
          ROS_INFO_STREAM("Picking up the object " << wait+1 << "s/5s");
          sleep(1);
          wait++;
        }
        break;
      case 2:
        goal_position[0] = drop_off_zone[0];
        goal_position[1] = drop_off_zone[1];
        marker.action = visualization_msgs::Marker::DELETE;
        distance = getDistance(drop_off_zone, robot_position);
        if (isReached(distance, threshold)) {
          step = 3;
        } else {
          ROS_INFO_STREAM("Drive to the drop-off zone ; distance: " << distance);
        }
        break;
      case 3:
        marker.action = visualization_msgs::Marker::ADD;
        ROS_INFO("Drop off the object");
        ROS_INFO("Mission Complete");
        step = 4;
        break;
      case 4:
        if (wait >= 5) {
          wait = 0;
          step = 0;
          ROS_INFO("Go To the first step");
          marker.action = visualization_msgs::Marker::DELETE;
        } else {
          ROS_INFO_STREAM("Wait for next cycle " << wait+1 << "s/5s");
          sleep(1);
          wait++;
        }
    }

    marker = setMarker(marker, goal_position, orientation, scale, color, alpha);

    marker.lifetime = ros::Duration();

    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    marker_pub.publish(marker);
    ros::spinOnce();
    r.sleep();
  }
  
  ros::spin();
  return 0;
}

visualization_msgs::Marker setMarker(visualization_msgs::Marker marker, double position[3], double orientation[4], double scale[3], float color[3], double alpha) {
  marker.pose.position.x = position[0];
  marker.pose.position.y = position[1];
  marker.pose.position.z = position[2];

  marker.pose.orientation.x = orientation[0];
  marker.pose.orientation.y = orientation[1];
  marker.pose.orientation.z = orientation[2];
  marker.pose.orientation.w = orientation[3];

  marker.scale.x = scale[0];
  marker.scale.y = scale[1];
  marker.scale.z = scale[2];

  marker.color.r = color[0];
  marker.color.g = color[1];
  marker.color.b = color[2];
  marker.color.a = alpha;

  return marker;
}

void getPosition(const nav_msgs::Odometry::ConstPtr& msg)
{
  robot_position[0] = msg->pose.pose.position.x;
  robot_position[1] = msg->pose.pose.position.y;
}

double getDistance(double goal[2], double position[2])
{
  double distance;
  distance = sqrt(pow(goal[0] - position[0], 2) + pow(goal[1] - position[1], 2));
  return distance;
}

bool isReached(double distance , double threshold)
{
  return distance < threshold;
}
