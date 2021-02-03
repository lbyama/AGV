#include <ros/ros.h>
#include <iostream>

template<typename std_msg_type,typename msg_type>
class Publisher{
   private:

      ros::NodeHandle nh_;

      ros::Publisher pub_;

      std_msg_type msg_;

   public:

      Publisher(std::string topic) {
         pub_ = nh_.advertise<std_msg_type>(topic, 1);
      }

      void publish(msg_type msg) {
         msg_.data = msg;
         pub_.publish(msg_);
      }
};

class BrakePublisher : public Publisher<std_msgs::Float64,float>{
   public:
      BrakePublisher() : Publisher<std_msgs::Float64,float>("/brake_command"){}
};

class GearPublisher : public Publisher<std_msgs::String,std::string>{
   public:
      GearPublisher() : Publisher<std_msgs::String,std::string>("/brake_command"){}
};

class HandbrakePublisher : public Publisher<std_msgs::Bool,bool>{
   public:
      HandbrakePublisher() :  Publisher<std_msgs::Bool,bool>("/handbrake_command"){}
};

class SteeringPublisher : public Publisher<std_msgs::Float64,float>{
   public:
      SteeringPublisher() : Publisher<std_msgs::Float64,float>("/steering_command"){}
};

class ThrottlePublisher : public Publisher<std_msgs::Float64,float>{
   public:
      ThrottlePublisher() : Publisher<std_msgs::Float64,float>("/throttle_command"){}
};


/*
▪  /brake_command [std_msgs/Float64]
   Valid values range from 0.0 (no brake) to 1.0 (full brake)
▪  /gear_command [std_msgs/String]
   Valid values are "forward" or "reverse"
▪  /handbrake_command [std_msgs/Bool]
   If set to "true", throttle will be ignored
▪  /steering_command [std_msgs/Float64]
   Valid values range from -1.0 (full right) to 1.0 (full left)
▪  /throttle_command [std_msgs/Float64]
   Valid values range from 0.0 (no throttle) to 1.0 (full throttle)
*/