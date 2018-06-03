//
// Created by jose on 1/06/18.
//

#include "board_connection/BoardConnection.hpp"
#include <stdlib.h>

BoardConnection::BoardConnection(ros::NodeHandle& nodeHandle)
    : nodeHandle_(nodeHandle) {
  subscriber_ = nodeHandle_.subscribe("/lane_control/control_signal");
  ROS_INFO("succesful");
}

BoardConnection::~BoardConnection() {

}

void BoardConnection::topicCallback(const std_msgs::Float32MultiArray array){
  std::cout << array.data[0] << std::endl;
}