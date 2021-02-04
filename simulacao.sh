#!/bin/bash
echo super mega script incrivel uaaauuuuuu

#dar make em nossos codigos
cd ~/catkin_ws
catkin_make

#iniciar nodes do airsim
. $HOME/src/AirSim/ros/install/setup.bash
roslaunch airsim_car_ros_pkgs airsim_node.launch > /dev/null 2>&1

#iniciar tradutor
rosrun airsim_translator airsim_translator_node > /dev/null 2>&1

#iniciar shell_simulation
roslaunch shell_simulation shell_simulation_node
