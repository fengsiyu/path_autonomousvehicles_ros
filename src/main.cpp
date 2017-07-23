#include <ros/ros.h>
//#include <ros/param.h>
#include <nav_msgs/Path.h>


// DCC - Main Function

void mainfuntioncallback(const nav_msgs::Path::ConstPtr& msg){
//void mainfuntioncallback(){
  ROS_INFO("main_funtioncallback");
  ROS_INFO("first x is: %f", msg->poses[0].pose.position.x);
  ROS_INFO("first y is: %f", msg->poses[0].pose.position.y);
  ROS_INFO("first angle is: %f", msg->poses[0].pose.orientation);
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
