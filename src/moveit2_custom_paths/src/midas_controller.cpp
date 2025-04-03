#include "moveit2_custom_paths/midas_controller.h"
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include <moveit_msgs/msg/display_robot_state.hpp>


midas_controller::MidasControllerNode::MidasControllerNode(): Node("midas_controller_node"){

    this->joint_state_sub = this->create_subscription<sensor_msgs::msg::JointState>("joint_states", 10, std::bind(&midas_controller::MidasControllerNode::joint_state_callback, this, std::placeholders::_1));

    this->reset_joint_states_srv = this->create_service<moveit2_custom_paths::srv::ResetJointStates>("reset_joint_states", std::bind(&midas_controller::MidasControllerNode::reset_joint_states, this, std::placeholders::_1));
}

midas_controller::MidasControllerNode::~MidasControllerNode(){}


void midas_controller::MidasControllerNode::start(){

}


void midas_controller::MidasControllerNode::joint_state_callback(const sensor_msgs::msg::JointState::ConstSharedPtr& joint_states){
    RCLCPP_INFO(this->get_logger(), "Positions: %s", rcpputils::join(joint_states->position, ", ").c_str());

    //Hardware Interface Here

}

void midas_controller::MidasControllerNode::reset_joint_states(std::shared_ptr<moveit2_custom_paths::srv::ResetJointStates::Response> res){
    static const std::string PLANNING_GROUP_ARM = "ur_manipulator";

    moveit::planning_interface::MoveGroupInterface move_group_arm(
        move_group_node, PLANNING_GROUP_ARM);
  
    const moveit::core::JointModelGroup *joint_model_group_arm =
        move_group_arm.getCurrentState()->getJointModelGroup(PLANNING_GROUP_ARM);
  
    // Get Current State
    moveit::core::RobotStatePtr current_state_arm =
        move_group_arm.getCurrentState(10);
  
    std::vector<double> joint_group_positions_arm;
    current_state_arm->copyJointGroupPositions(joint_model_group_arm,
                                               joint_group_positions_arm);
  
    move_group_arm.setStartStateToCurrentState();

    // Go Home
    RCLCPP_INFO(LOGGER, "Going Home");

    joint_group_positions_arm[0] = 0.00;  // Shoulder Pan
    joint_group_positions_arm[1] = 0.00; // Shoulder Lift
    joint_group_positions_arm[2] = 0.00;  // Elbow
    joint_group_positions_arm[3] = 0.00; // Wrist 1
    joint_group_positions_arm[4] = 0.00; // Wrist 2
    // joint_group_positions_arm[5] = 0.00;  // Wrist 3

    move_group_arm.setJointValueTarget(joint_group_positions_arm);

    moveit::planning_interface::MoveGroupInterface::Plan my_plan_arm;
    bool success_arm = (move_group_arm.plan(my_plan_arm) ==
                        moveit::core::MoveItErrorCode::SUCCESS);

    move_group_arm.execute(my_plan_arm);

    res->success = success_arm;
}