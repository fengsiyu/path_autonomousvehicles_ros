#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/PolygonStamped.h"
#include "teb_local_planner/ObstacleMsg.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "teb_obstacles");
  ros::NodeHandle nh;

  ros::Publisher obstacles_pub = nh.advertise<teb_local_planner::ObstacleMsg>("/test_optim_node/obstacles", 1000);

  // msg definition
  teb_local_planner::ObstacleMsg obstacle_msg;
  geometry_msgs::PolygonStamped polygon_msg;
  geometry_msgs::Point32 point_msg;

  //
  obstacle_msg.header.stamp = ros::Time::now();
  obstacle_msg.header.frame_id = "odom"; // CHANGE HERE: odom/map;

  // Add point obstacle - C++
  polygon_msg.header.stamp = ros::Time::now();
  polygon_msg.header.frame_id = "odom";
  // point - 1
  point_msg.x = 1.5;
  point_msg.y = 0;
  point_msg.z = 0;
  polygon_msg.polygon.points.push_back(point_msg);
  // Add polygon to obstacle list
  obstacle_msg.obstacles.push_back(polygon_msg);


  // Add point obstacle - python
  /*
  obstacle_msg.obstacles.append(PolygonStamped());
  obstacle_msg.obstacles[0].polygon.points = [Point32()];
  obstacle_msg.obstacles[0].polygon.points[0].x = 1.5;
  obstacle_msg.obstacles[0].polygon.points[0].y = 0;
  obstacle_msg.obstacles[0].polygon.points[0].z = 0;
  */

  // Add line obstacle - C++
  geometry_msgs::PolygonStamped polygon2_msg;
  polygon2_msg.header.stamp = ros::Time::now();
  polygon2_msg.header.frame_id = "odom";
  // point - 1
  point_msg.x = -2.5;
  point_msg.y = 0.5;
  polygon2_msg.polygon.points.push_back(point_msg);
  // point - 2
  point_msg.x = -2.5;
  point_msg.y = 2;
  polygon2_msg.polygon.points.push_back(point_msg);
  // Add polygon to obstacle list
  obstacle_msg.obstacles.push_back(polygon2_msg);
  // Add line obstacle - python
  /*
  obstacle_msg.obstacles.append(PolygonStamped());
  line_start = Point32();
  line_start.x = -2.5;
  line_start.y = 0.5;
  line_end = Point32();
  line_end.x = -2.5;
  line_end.y = 2;
  obstacle_msg.obstacles[1].polygon.points = [line_start, line_end];
  */

  // Add polygon obstacle - C++

  // Add polygon obstacle - python
  /*
  obstacle_msg.obstacles.append(PolygonStamped());
  v1 = Point32();
  v1.x = -1;
  v1.y = -1;
  v2 = Point32();
  v2.x = -0.5;
  v2.y = -1.5;
  v3 = Point32();
  v3.x = 0;
  v3.y = -1;
  obstacle_msg.obstacles[2].polygon.points = [v1, v2, v3];
  */

  ros::Rate loop_rate(2);
  while (ros::ok())
  {
    obstacles_pub.publish(obstacle_msg);

    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
