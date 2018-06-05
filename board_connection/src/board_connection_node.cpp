//
// Created by jose on 3/06/18.
//

#include <iostream>
#include <ros/ros.h>
#include "board_connection/BoardConnection.hpp"

int main(int argc, char** argv){

  ros::init(argc, argv, "board_connection");
  ros::NodeHandle nodeHandle("~");
  board_connection::BoardConnection BoardConnection(nodeHandle);

  ros::spin();
  return 0;
}

