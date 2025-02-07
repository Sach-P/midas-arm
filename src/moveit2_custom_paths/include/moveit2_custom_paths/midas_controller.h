
#include <atomic>

#ifdef HAS_CPUID
#include <cpuid.h>
#endif

#include <ctime>
#include <fstream>
#include <future>
#include <iomanip>
#include <ios>
#include <iostream>
#include <mutex>
#include <signal.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/times.h>
#include <thread>


#include "rclcpp/rclcpp.hpp"

#include <sensor_msgs/msg/joint_state.hpp>


namespace midas_controller{
    class MidasControllerNode;
}

class midas_controller::MidasControllerNode: public rclcpp::Node{

public:

    MidasControllerNode();
    ~MidasControllerNode();

    void start();

private:

    void joint_state_callback(const sensor_msgs::msg::JointState::ConstSharedPtr& joint_states);

    rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_state_sub;
    
    
};