#include <ros/ros.h>
#include <iostream>
#include <std_msgs/Float64.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Quaternion.h>
#include <cmath> 

class OdometrySubscriber{
    private:
        ros::NodeHandle nh_;
        ros::Subscriber sub_;

        static float x_;
        static float y_;
        static float z_;
        static float angle_;

    public:
        OdometrySubscriber();
        static void odomCallback(const nav_msgs::Odometry::ConstPtr& msg);
        float getX();
        float getY();
        float getZ();
        float getAngle();
};