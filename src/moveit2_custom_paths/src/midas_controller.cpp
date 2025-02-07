#include "moveit2_custom_paths/midas_controller.h"
#include <fmt/core.h>



midas_controller::MidasControllerNode::MidasControllerNode(): Node("midas_controller_node"){

    this->joint_state_sub = this->create_subscription<sensor_msgs::msg::JointState>("joint_states", 10, std::bind(&midas_controller::MidasControllerNode::joint_state_callback, this, std::placeholders::_1));
}

midas_controller::MidasControllerNode::~MidasControllerNode(){}


void midas_controller::MidasControllerNode::start(){

}


void midas_controller::MidasControllerNode::joint_state_callback(const sensor_msgs::msg::JointState::ConstSharedPtr& joint_states){
    RCLCPP_INFO(this->get_logger(), "Positions: %s", rcpputils::join(joint_states->position, ", ").c_str());

    //Hardware Interface Here
}