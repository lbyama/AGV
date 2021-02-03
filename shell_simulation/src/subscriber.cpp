#include <shell_simulation/subscriber.h>

float OdometrySubscriber::x_;
float OdometrySubscriber::y_;
float OdometrySubscriber::z_;
float OdometrySubscriber::angle_;

OdometrySubscriber::OdometrySubscriber(){
    ros::Subscriber sub = nh_.subscribe("/airsim_node/PhysXCar/odom_local_ned", 1, odomCallback);
    sub_ = sub;
}

void OdometrySubscriber::odomCallback(const nav_msgs::Odometry::ConstPtr& msg){
   x_ = msg->pose.pose.position.x; //seta a posicao x do carro
   y_ = msg->pose.pose.position.y; //y
   z_ = msg->pose.pose.position.z;//z

   float xo = msg->pose.pose.orientation.x;
   float yo = msg->pose.pose.orientation.y;

   float ang = atan(abs(yo)/abs(xo)); //calcula o angulo do carro em radianos
   ang = (ang*360.0)/(2*M_PI); //transforma angulo em graus

   //arrumando o angulo com base nos quadrantes
   if(xo < 0 && yo < 0){
       angle_ = 270 + ang;
   }else if(xo < 0 && yo > 0){
       angle_ = 90 - ang;
   }else if(xo > 0 && yo < 0){
       angle_ = 270 - ang;
   }else if(xo > 0 && yo > 0){
       angle_ = 90 + ang;
   }
}

float OdometrySubscriber::getX(){
    return x_;
}
float OdometrySubscriber::getY(){
    return y_;
}
float OdometrySubscriber::getZ(){
    return z_;
}
float OdometrySubscriber::getAngle(){
    return angle_;
}