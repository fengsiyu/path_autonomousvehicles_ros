#include <ros/ros.h>

#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

//#include <robotnik_pp_msgs/GoToAction.h>

//#include <robotnik_pp_msgs/GoToActionGoal.h>
//#include <robotnik_pp_msgs/GoToActionFeedback.h>
//#include <robotnik_pp_msgs/GoToActionResult.h>

//#include <robotnik_pp_msgs/GoToGoal.h>
//#include <robotnik_pp_msgs/GoToFeedback.h>
//#include <robotnik_pp_msgs/GoToResult.h>

using namespace std;


//http://wiki.ros.org/navigation/Tutorials/SendingSimpleGoals
//https://github.com/RobotnikAutomation/robotnik_purepursuit_planner.git
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

//typedef robotnik_pp_msgs::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;


// Subscriber to A
ros::Subscriber local_path_subscriber = main_node_path.subscribe("local_path_publisher", 0, localpathcallback);
ROS_INFO("main_subscriber completed");
