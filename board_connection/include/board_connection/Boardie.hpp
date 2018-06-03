//
// Created by jose on 1/06/18.
//

#ifndef PROJECT_BOARDCONNECTIONNODE_H
#define PROJECT_BOARDCONNECTIONNODE_H

#include "board_connection/BoardConnection.hpp"

//ROS
#include <ros/ros.h>
#include <std_msgs/Float32MultiArray.h>

namespace board_connection {

  class BoardConnection {
   public:
    BoardConnection(ros::NodeHandle& nodeHandle);
    virtual ~BoardConnection();

   private:
    topicCallback(const std_msgs::Float32MultiArray& array);

    ros::NodeHandle& nodeHandle_;
    ros::Subscriber subscriber_;
  };

}

#endif //PROJECT_BOARDCONNECTIONNODE_H
