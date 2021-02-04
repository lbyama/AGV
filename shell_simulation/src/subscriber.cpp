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

   float xo = msg->twist.twist.linear.x; //pega a velocidade em x
   float yo = msg->twist.twist.linear.y; //e em y

   xo = xo*100000;
   yo = yo*100000;

   float ang = atan(xo/yo); //calcula o angulo do carro em radianos
   ang = (ang*360.0)/(2*M_PI); //transforma angulo em graus
   ang = abs(ang); //faz o modulo do angulo

   //arrumando o angulo com base nos quadrantes
   if(xo < 0 && yo < 0){
       angle_ = 270 + ang;
   }else if(xo < 0 && yo >= 0){
       angle_ = 90 - ang;
   }else if(xo >= 0 && yo < 0){
       angle_ = 270 - ang;
   }else if(xo >= 0 && yo >= 0){
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