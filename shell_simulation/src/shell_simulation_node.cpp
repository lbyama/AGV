#include <shell_simulation/publisher.h>
#include <shell_simulation/subscriber.h>

int main(int argc, char **argv) {
   ros::init(argc, argv, "shell_simulation");

   //Cria um Subscriber para o topico da odometria

   OdometrySubscriber odom_node;
   
   //Cria Publishers para todos os topicos

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
   float steering = 0.01;
   float throttle = 0.5;
   
   char orien = 'f'; //frente, tras, direita, esquerda?

   ROS_INFO("Inicializando shell_simulation_node");

   while (ros::ok()) {
      //Ajustar direcao que nem um seguidor de linha com base no angulo

      /*
      if(orien = 'f'){ //se estiver indo pra frente
         if(odom_node.getAngle() < 180.0){ //se estiver virado para direita
            steering = 0.1; //vire a esquerda
         }else if(odom_node.getAngle() > 180.0){
            steering = -0.1;
         }else{
            steering = 0.0
         }
      }
      */
      
      //Ajustar direcao que nem um seguidor de linha com base na localizacao
      
      if(orien = 'f'){
         if(odom_node.getY() > 0.0){ //se estiver a direita do eixo x
            steering = 0.05; //vire a esquerda
         }else if(odom_node.getY() < 0.0){ //se estiver a esquerda dele
            steering = -0.05; //vire a direita
         }else{
            steering = 0;
         }
      }
      


      if(orien == 'e'){ //indo para a esquerda
         if(odom_node.getAngle() > 270 || odom_node.getAngle() < 90){ //curvando para cima
            steering = 0.1; //vire a esquerda
         }else{
            steering = -0.1;
         }
      }

      if(odom_node.getX() < -210){ //comecar a curva superior direita
         throttle = 0.0;
         steering = 1.0; //virar a esquerda
         orien = 'c'; //fazendo curva
      }

      if(orien == 'c'){
         if(odom_node.getAngle() < 5.0 && odom_node.getAngle() > 355.0){ // parar de fazer a curva
            steering = 0.0;
            throttle = 0.5;
            orien = 'e';  //pa esquerda
         }
      }

      ROS_INFO("Odometry---------------------------------------");
      ROS_INFO("   x: [%f]",odom_node.getX());
      ROS_INFO("   y: [%f]",odom_node.getY());
      ROS_INFO("   z: [%f]",odom_node.getZ());
      ROS_INFO("   angle: [%f]",odom_node.getAngle());

      ROS_INFO("CarCmd-----------------------------------------");
      ROS_INFO("   brake: [%f]",brake);
      ROS_INFO("   gear: [%s]",gear.data());
      ROS_INFO("   handbrake: [%d]",handbrake);
      ROS_INFO("   steering: [%f]",steering);
      ROS_INFO("   throttle: [%f]",throttle);


      //Publica o valor das variaveis em todos os topicos de controle
       brake_node.publish(brake);
       gear_node.publish(gear);
       handbrake_node.publish(handbrake);
       steering_node.publish(steering);
       throttle_node.publish(throttle);
       //alterar para publicacao no callback

       ros::spinOnce();
       rate.sleep(); //Dorme tempo suficiente para manter a frequencia definida no rate();
   }

    return 0;
}
/*
int main(int argc, char **argv) {
   ros::init(argc, argv, "shell_simulation");

   //Cria um Subscriber para o topico da odometria

   OdometrySubscriber odom_node;
   
   //Cria Publishers para todos os topicos

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
   float steering = -0.01;
   float throttle = 0.5;
   
   char orien = 'f'; //frente, tras, direita, esquerda?

   ROS_INFO("Inicializando shell_simulation_node");

   while (ros::ok()) {
      //Ajustar direcao que nem um seguidor de linha

      if(orien = 'f'){ //se estiver indo pra frente
	 ROS_INFO(" ORIENTAÇÃO FRENTE   angle: [%f]",odom_node.getAngle());
         if(odom_node.getAngle() < 180.0){ //se estiver virado para direita
            steering = -0.15; //vire a esquerda
         }else{
            steering = 0.15;
         }
      }

      if(orien == 'e'){ //indo para a esquerda
	ROS_INFO(" ORIENTAÇÃO ESQUERDA   angle: [%f]",odom_node.getAngle());
         if(odom_node.getAngle() > 270 || odom_node.getAngle() < 90){ //curvando para cima
            steering = -0.15; //vire a esquerda
         }else{
            steering = 0.15;
         }
      }

	//-------------

      if(odom_node.getX() < -210){ //comecar a curva superior direita
         throttle = 0.0;
         steering = -1.0; //virar a esquerda
         orien = 'c'; //fazendo curva
      }

      if(orien == 'c'){
         if(odom_node.getAngle() < 5.0 && odom_node.getAngle() > 355.0){ // parar de fazer a curva
            steering = 0.0;
            throttle = 0.5;
            orien = 'e';  //pa esquerda
         }
      }

      ROS_INFO("Odometry---------------------------------------");
      ROS_INFO("   x: [%f]",odom_node.getX());
      ROS_INFO("   y: [%f]",odom_node.getY());
      ROS_INFO("   z: [%f]",odom_node.getZ());
      ROS_INFO("   angle: [%f]",odom_node.getAngle());



      ROS_INFO("CarCmd-----------------------------------------");
      ROS_INFO("   brake: [%f]",brake);
      ROS_INFO("   gear: [%s]",gear.data());
      ROS_INFO("   handbrake: [%d]",handbrake);
      ROS_INFO("   steering: [%f]",steering);
      ROS_INFO("   throttle: [%f]",throttle);

      //Publica o valor das variaveis em todos os topicos de controle
       brake_node.publish(brake);
       gear_node.publish(gear);
       handbrake_node.publish(handbrake);
       steering_node.publish(steering);
       throttle_node.publish(throttle);
       //alterar para publicacao no callback

       ros::spinOnce();
       rate.sleep(); //Dorme tempo suficiente para manter a frequencia definida no rate();
   }

    return 0;
}
*/

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