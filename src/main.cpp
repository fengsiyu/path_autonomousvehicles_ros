#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <nav_msgs/Odometry.h>

// DCC - Main Function

void mainfuntioncallback(const nav_msgs::Path::ConstPtr& msg){
  ROS_INFO("mainfuntioncallback");
  //ROS_INFO("first x is: %f", msg->poses[0].pose.position.x);
  //ROS_INFO("first y is: %f", msg->poses[0].pose.position.y);
  //ROS_INFO("first angle is: %f", msg->poses[0].pose.orientation);
  //for(int i=0; i < 18 ; i++){
      //ROS_INFO("Position %i, Pose x = %f", i, msg->poses[i].pose.position.x);
  //}
}



void odometrycallback(const nav_msgs::Odometry::ConstPtr& msg_odom){
  ROS_INFO("odometrycallback");
  ROS_INFO("odom || x = %f, y = %f, angle = %f",
           msg_odom->pose.pose.position.x,
           msg_odom->pose.pose.position.y,
           msg_odom->pose.pose.orientation.z);
}


int main(int argc, char** argv)
{

  ros::init(argc, argv, "main_node");
  ros::NodeHandle main_node_path;
  ROS_INFO("main node created and registered");

  // Subscriber to Local Path
  ros::Subscriber main_subscriber = main_node_path.subscribe("local_path_publisher", 0, mainfuntioncallback);
  ROS_INFO("main_subscriber completed");

  // Subscriber to Odometry
  ros::Subscriber odometry_subscriber = main_node_path.subscribe("gazebo_odometry", 0, odometrycallback);
  ROS_INFO("odometry_subscriber completed");


  // Loop
  ros::spin();

  return 0;

}
