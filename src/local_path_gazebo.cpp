#include <math.h>

#include <ros/ros.h>
#include <ros/param.h>
#include <nav_msgs/Path.h>
#include <tf/tf.h>

// DCC - Local Path from Time Elastic Band

int main(int argc, char** argv)
{

    ros::init(argc, argv, "local_path_publisher");
    ros::NodeHandle nh;
    std::string global_plan;

    nh.param<std::string>("publish_topic", global_plan, "goal_path");

    ros::Publisher pub_plan = nh.advertise<nav_msgs::Path>("/local_path_publisher", 1);

    geometry_msgs::PoseStamped point;
    nav_msgs::Path path;

    float radius = 10;
    path.header.stamp = ros::Time::now();
    path.header.frame_id = "base_footprint";

    ROS_INFO("Local Path formed by 18 points");

    ros::Duration seconds_sleep(1);

    while (ros::ok()){
        for(int i=0; i < 18 ; i++)
        {
            point.pose.position.x = radius * sin(20*M_PI/180 * i);
            point.pose.position.y = -radius * cos(20*M_PI/180 * i) + radius;
            point.pose.orientation = tf::createQuaternionMsgFromYaw(20*M_PI/180 * i);
            path.poses.push_back(point);
        }

        pub_plan.publish(path);

        ros::spinOnce();
        seconds_sleep.sleep();
    }
}
