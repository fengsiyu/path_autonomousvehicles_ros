#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <nav_msgs/Odometry.h>
#include <ackermann_msgs/AckermannDrive.h>

#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

#include <iostream>

using namespace std;

// ----------------
// Global variables
ackermann_msgs::AckermannDrive acker_drive_msg;
nav_msgs::Path gl_msg_path;
nav_msgs::Odometry gl_msg_odom;

// -----------------------
// Purepursuit + actionLib
//
//http://wiki.ros.org/navigation/Tutorials/SendingSimpleGoals
//https://github.com/RobotnikAutomation/robotnik_purepursuit_planner.git
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
//typedef actionlib::SimpleActionClient<robotnik_pp_msgs::goal> MoveBaseClient;

void localpathcallback(const nav_msgs::Path::ConstPtr& msg_path){
  //ROS_INFO("mainfuntioncallback");
  gl_msg_path = *msg_path;
  //ROS_INFO("first x is: %f", msg->poses[0].pose.position.x);
  //ROS_INFO("first y is: %f", msg->poses[0].pose.position.y);
  //ROS_INFO("first angle is: %f", msg->poses[0].pose.orientation);
  //for(int i=0; i < 18 ; i++){
  //ROS_INFO("Position %i, Pose x = %f", i, msg->poses[i].pose.position.x);
  //}

  //cout << acker_drive_msg.speed << endl;
}


void odometrycallback(const nav_msgs::Odometry::ConstPtr& msg_odom){
  //ROS_INFO("odometrycallback");
  gl_msg_odom = *msg_odom;

  //ROS_INFO("odom || x = %f, y = %f, angle = %f",
  //         msg_odom->pose.pose.position.x,
  //         msg_odom->pose.pose.position.y,
  //         msg_odom->pose.pose.orientation.z);
}


int main(int argc, char** argv){

  // Register main_node
  ros::init(argc, argv, "main_node");
  ros::NodeHandle main_node_path;
  ros::Duration seconds_sleep(0.001);
  ROS_INFO("main node created and registered");

  // Publish Ackermann Drive msg
  ros::Publisher acker_drive = main_node_path.advertise<ackermann_msgs::AckermannDrive>("ackermann_cmd", 1);

  // ------------------------
  // Subscriber to Local Path
  ros::Subscriber local_path_subscriber = main_node_path.subscribe("local_path_publisher", 0, localpathcallback);
  ROS_INFO("main_subscriber completed");

  // ----------------------
  // Subscriber to Odometry
  ros::Subscriber odometry_subscriber = main_node_path.subscribe("gazebo_odometry", 0, odometrycallback);
  ROS_INFO("odometry_subscriber completed");

  // -----------
  // Purepursuit
  MoveBaseClient ac("move_base", true);
  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  //we'll send a goal to the robot to move 1 meter forward
  goal.target_pose.header.frame_id = "base_link";
  goal.target_pose.header.stamp = ros::Time::now();

  goal.target_pose.pose.position.x = 1.0;
  goal.target_pose.pose.orientation.w = 1.0;

  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  ac.waitForResult();

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, the base moved 1 meter forward");
  else
    ROS_INFO("The base failed to move forward 1 meter for some reason");


  // Modify Ackermann msg values
  acker_drive_msg.steering_angle_velocity = 0.5;
  acker_drive_msg.steering_angle = 0.2;
  acker_drive_msg.acceleration= 0.6;
  acker_drive_msg.speed= 0.1;

  while(ros::ok()){

    ROS_INFO("main in while --");

    // Publish Ackermann Drive
    acker_drive.publish(acker_drive_msg);

    int sizeofPath = (sizeof(gl_msg_path)/sizeof(float));

    //cout << sizeofPath << endl;
    //cout << gl_msg_path << endl;

    //for(int i = 0; i < sizeofPath; i++ ){

    //    cout << i << endl;
    //cout << gl_msg_path << endl;
    //ROS_INFO("first x is: %f", gl_msg_path.poses[i].pose.position.x);
    //ROS_INFO("first y is: %f", gl_msg_path.poses[i].pose.position.y);
    //ROS_INFO("first angle is: %f", gl_msg_path.poses[i].pose.orientation);
    //}

    // TBD
    //cout << gl_msg_odom.pose.pose.position.x << endl;
    //cout << gl_msg_odom.pose.pose.position.y << endl;
    //gl_msg_odom->pose.pose.position.x;


    // Loop
    ros::spinOnce();
    seconds_sleep.sleep();

  }
}
