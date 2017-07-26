#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <nav_msgs/Odometry.h>
#include <ackermann_msgs/AckermannDrive.h>

// DCC - Main Function


void localpathcallback(const nav_msgs::Path::ConstPtr& msg){
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


int main(int argc, char** argv){
    // Register main_node
    ros::init(argc, argv, "main_node");
    ros::NodeHandle main_node_path;
    ROS_INFO("main node created and registered");


    ros::Duration seconds_sleep(1);


    // Publish Ackermann Drive msg
    ros::Publisher acker_drive = main_node_path.advertise<ackermann_msgs::AckermannDrive>("ackermann_cmd", 1);
    ackermann_msgs::AckermannDrive acker_drive_msg;

    while(ros::ok()){



        // Subscriber to Local Path
        ros::Subscriber local_path_subscriber = main_node_path.subscribe("local_path_publisher", 0, localpathcallback);
        ROS_INFO("main_subscriber completed");

        // Subscriber to Odometry
        ros::Subscriber odometry_subscriber = main_node_path.subscribe("gazebo_odometry", 0, odometrycallback);
        ROS_INFO("odometry_subscriber completed");

        // Get values from Local Path Subscriber
        //ROS_INF(local_path_subscriber.)


        // Modify Ackermann msg values
        acker_drive_msg.steering_angle_velocity = 0.5;
        acker_drive_msg.steering_angle = 0.2;
        acker_drive_msg.acceleration= 0.6;
        acker_drive_msg.speed= 0.1;


        // Publish Ackermann Drive
        acker_drive.publish(acker_drive_msg);

        // Loop
        ros::spinOnce();
        seconds_sleep.sleep();


    }

}
