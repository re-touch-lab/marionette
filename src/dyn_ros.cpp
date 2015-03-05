#include <dyn_ros.h>
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <osrf_msgs/JointCommands.h>
#include <dynamixel.h>
#include <dxl_hal.h>

dyn_controller::dyn_controller(){
  motor_state_ = nh_.advertise<sensor_msgs::JointState>("/cur_state",100);
  motor_control_ = nh_.subscribe("/cur_command", 100, &dyn_controller::dynCommandCb, this);
}

bool dyn_controller::init(){
  ROS_INFO("[DYN CONTROLLER]::Initializing");
  // generate motor name to id mapping
  while(!nh_.hasParam("/namesToIds")){
    ROS_INFO("[DYN CONTROLLER]::Waiting for params");
    sleep(1);};
  nh_.getParam("/namesToIds",name2num_);

  ROS_INFO("[DYN CONTROLLER]::%d motors loaded",(int)name2num_.size());

  for(auto it = name2num_.cbegin(); it != name2num_.cend(); ++it)
  {
        ROS_INFO( "%s %d \n", it->first.c_str(), it->second);
        num2name_.insert( std::pair<int, std::string>(it->second,it->first) );
  }


}

bool dyn_controller::shutdown(){
}

void dyn_controller::dynCommandCb(const osrf_msgs::JointCommands::ConstPtr &cmd){

}

void dyn_controller::dynControl(){
  dxl_initialize(deviceIndex_,baudnum_)
  while(ros::ok()){

  }
}

int main(int argc, char** argv){
  ROS_INFO("[DYN CONTROLLER]::Started");
  ros::init(argc,argv,"dyn_controller");
  
  dyn_controller my_controller;

  my_controller.init();

  ros::spin();

  return 0;
}
