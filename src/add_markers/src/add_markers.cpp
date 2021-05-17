#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

visualization_msgs::Marker setMarker(visualization_msgs::Marker marker, int position[3], double orientation[4], double scale[3], float color[3], double alpha);

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  int step = 0;

  int position[3] = {1, 1, 0};
  double orientation[4] = {0.0, 0.0, 0.0, 1.0};
  double scale[3] = {0.1, 0.1, 0.1};
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
        position[0] = 1;
        position[1] = 1;
        marker.action = visualization_msgs::Marker::ADD;
        step = 1;
        ROS_INFO("Set the marker at the pickup zone");
        break;
      case 1:
        sleep(5);
        marker.action = visualization_msgs::Marker::DELETE;
        step = 2;
        ROS_INFO("Hide the marker after pickup");
        break;
      case 2:
        position[0] = 2;
        position[1] = 2;
        marker.action = visualization_msgs::Marker::ADD;
        step = 3;
        ROS_INFO("Set the marker at the drop off zone");
        break;
      case 3:
        sleep(5);
        marker.action = visualization_msgs::Marker::DELETE;
        step = 0;
        ROS_INFO("Hide the marker after drop off");
        break;
        
    }

    marker = setMarker(marker, position, orientation, scale, color, alpha);

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

    r.sleep();
  }
  return 0;
}

visualization_msgs::Marker setMarker(visualization_msgs::Marker marker, int position[3], double orientation[4], double scale[3], float color[3], double alpha) {
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
