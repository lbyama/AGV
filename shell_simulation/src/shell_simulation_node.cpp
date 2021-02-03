#include <shell_simulation/publisher.h>
#include <std_msgs/Float64.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Quaternion.h>

geometry_msgs::Point position;
geometry_msgs::Quaternion orientation;

void odomCallback(const nav_msgs::Odometry::ConstPtr& msg){
   position = msg->pose.pose.position;
   orientation = msg->pose.pose.orientation;
}


int main(int argc, char **argv) {
   ros::init(argc, argv, "shell_simulation");

   ros::NodeHandle nh;
   
   ros::Subscriber sub = nh.subscribe("/airsim_node/PhysXCar/odom_local_ned", 1, odomCallback);

   /* 
   Cria Publishers para todos os topicos de comando passando:
      - o tipo de mensagem publicada no topico [std_msgs];
      - o tipo do atributo data de cada msg [std_msgs.data];
      - uma string com o nome do topico a ser publicado [/x_command];
   */

   BrakePublisher brake_node;
   GearPublisher gear_node;
   HandbrakePublisher handbrake_node;
   SteeringPublisher steering_node;
   ThrottlePublisher throttle_node;

   ros::Rate rate(10); //Define a frequencia de publicacao de mensagens [Hz]

   //Define o valor das variaveis a serem publicadas
   float brake = 0.0;
   std::string gear = "forward";
   bool handbrake = false;
   float steering = 0.0;
   float throttle = 1.0;
   
   char orien = 'v';

   while (ros::ok()) {
      //Ajustar direcao que nem um seguidor de linha
      if(orientation.x > 0 && orien == 'v'){ //se estiver virado para direita enquanto indo na vertical
         steering = 0.01; //vire a esquerda
      }
      if(orientation.x < 0 && orien == 'v'){
         steering = -0.01;
      }
      
      if(position.y < -210){ //comecar a curva superior direita
         throttle = 0.0;
         steering = 1.0;
         orien = 'n'; //nenhuma direcao nem outra
      }
      
      if(orientation.y > -1 && orientation.y < 1){ // parar de fazer a curva
         steering = 0.0;
         throttle = 1.0;
         orien = 'h';  //na horizontal
      }

      if(orientation.y < 0 && orien == 'h'){ //se estiver virado para cima enquanto indo na horizontal
         steering = 0.01; //vire a esquerda
      }
      if(orientation.y > 0 && orien == 'h'){
         steering = -0.01;
      }

      //Publica o valor das variaveis em todos os topicos de controle
       brake_node.publish(brake);
       gear_node.publish(gear);
       handbrake_node.publish(handbrake);
       steering_node.publish(steering);
       throttle_node.publish(throttle);

       ros::spinOnce();
       rate.sleep(); //Dorme tempo suficiente para manter a frequencia definida no rate();
   }

    return 0;
}

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