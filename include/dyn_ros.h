#ifndef dyn_control_h_
#define dyn_control_h_


#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <osrf_msgs/JointCommands.h>
#include <dynamixel.h>
#include <dxl_hal.h>

#include <map>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <string>

class dyn_controller{
  public:
    dyn_controller();
    bool init();
    bool shutdown();

    void dynCommandCb(const osrf_msgs::JointCommands::ConstPtr &cmd);

  private:
    // the queue of commands that are to be run on the dynamixels
    std::queue<osrf_msgs::JointCommands> cmd_queue_;
    std::mutex empty_queue_;

    // stores the map between joint name and motor id
    std::map<std::string, int> name2num_;
    std::map<int, std::string> num2name_;

    // stores the translation between units for each motor (each motor could be different)
    std::vector<float> dyn2rad_; 
    std::vector<float> rad2dyn_;
    std::thread control_loop_;
    void dynControl();
    int deviceIndex_;
    int baudnum_;

    ros::NodeHandle nh_;
    ros::Publisher motor_state_;
    ros::Subscriber motor_control_;
};

#endif
