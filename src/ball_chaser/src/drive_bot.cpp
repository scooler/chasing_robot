#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ball_chaser/DriveToTarget.h"
#include <std_msgs/Float64.h>


class DriveBot{
public:
  DriveBot(){
    // Inform ROS master that we will be publishing a message of type geometry_msgs::Twist on the robot actuation topic with a publishing queue size of 10
    _motor_command_publisher = _n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);


    // Define a safe_move service with a handle_safe_move_request callback function
    _service = _n.advertiseService("/ball_chaser/command_robot", &DriveBot::handle_drive_request, this);
    ROS_INFO("Ready to send robot commands");
  }

// This callback function executes whenever a safe_move service is requested
bool handle_drive_request(ball_chaser::DriveToTarget::Request& req,
    ball_chaser::DriveToTarget::Response& res)
{

    ROS_INFO("DriveToTarget received - linear_x:%1.2f, angular_z:%1.2f", (float)req.linear_x, (float)req.angular_z);

    geometry_msgs::Twist motor_command;

    // // Check if requested joint angles are in the safe zone, otherwise clamp them
    // std::vector<float> joints_angles = clamp_at_boundaries(req.joint_1, req.joint_2);

    // // Publish clamped joint angles to the arm
    // std_msgs::Float64 joint1_angle, joint2_angle;

    // joint1_angle.data = joints_angles[0];
    // joint2_angle.data = joints_angles[1];

    // _joint1_pub.publish(joint1_angle);
    // _joint2_pub.publish(joint2_angle);

    // // Wait 3 seconds for arm to settle
    // ros::Duration(3).sleep();

    // // Return a response message
    res.msg_feedback = "Works!"; //"Joint angles set - j1: " + std::to_string(joints_angles[0]) + " , j2: " + std::to_string(joints_angles[1]);
    // ROS_INFO_STREAM(res.msg_feedback);

    return true;
}
private:
  ros::NodeHandle _n;
  ros::Publisher _motor_command_publisher;
  ros::ServiceServer _service;

  // This function checks and clamps the joint angles to a safe zone
  // std::vector<float> clamp_at_boundaries(float requested_j1, float requested_j2)
  // {
  //     // Define clamped joint angles and assign them to the requested ones
  //     float clamped_j1 = requested_j1;
  //     float clamped_j2 = requested_j2;

  //     // Get min and max joint parameters, and assigning them to their respective variables
  //     float min_j1, max_j1, min_j2, max_j2;
  //     // Get node name
  //     std::string node_name = ros::this_node::getName();
  //     // Get joints min and max parameters
  //     _n.getParam(node_name + "/min_joint_1_angle", min_j1);
  //     _n.getParam(node_name + "/max_joint_1_angle", max_j1);
  //     _n.getParam(node_name + "/min_joint_2_angle", min_j2);
  //     _n.getParam(node_name + "/max_joint_2_angle", max_j2);

  //     // Check if joint 1 falls in the safe zone, otherwise clamp it
  //     if (requested_j1 < min_j1 || requested_j1 > max_j1) {
  //         clamped_j1 = std::min(std::max(requested_j1, min_j1), max_j1);
  //         ROS_WARN("j1 is out of bounds, valid range (%1.2f,%1.2f), clamping to: %1.2f", min_j1, max_j1, clamped_j1);
  //     }
  //     // Check if joint 2 falls in the safe zone, otherwise clamp it
  //     if (requested_j2 < min_j2 || requested_j2 > max_j2) {
  //         clamped_j2 = std::min(std::max(requested_j2, min_j2), max_j2);
  //         ROS_WARN("j2 is out of bounds, valid range (%1.2f,%1.2f), clamping to: %1.2f", min_j2, max_j2, clamped_j2);
  //     }

  //     // Store clamped joint angles in a clamped_data vector
  //     std::vector<float> clamped_data = { clamped_j1, clamped_j2 };

  //     return clamped_data;
  // }
};


int main(int argc, char** argv)
{
    // Initialize the arm_mover node and create a handle to it
    ros::init(argc, argv, "drive_bot");

    DriveBot driver;

    // Handle ROS communication events
    ros::spin();

    return 0;
}