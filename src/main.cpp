#include <ros/ros.h>
//#include <ros/param.h>
#include <nav_msgs/Path.h>


// DCC - Main Function

void mainfuntioncallback(const nav_msgs::Path::ConstPtr& msg){
  ROS_INFO("main_funtioncallback");
  //ROS_INFO("first is: %f", msg->poses);

}


int main(int argc, char** argv)
{

  ros::init(argc, argv, "main_node");
  ros::NodeHandle main_node_path;
  ROS_INFO("main node created and registered");

  ros::Subscriber main_subscriber = main_node_path.subscribe("local_path_publisher", 0, mainfuntioncallback);

  ROS_INFO("main_subscriber completed");

  ros::spin();

  return 0;

}
