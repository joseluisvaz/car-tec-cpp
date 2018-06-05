//
// Created by jose on 3/06/18.
//

#ifndef PROJECT_BOARDCONNECTION_HPP
#define PROJECT_BOARDCONNECTION_HPP

#include <ros/ros.h>
#include <iostream>
#include <std_msgs/Float32MultiArray.h>

namespace board_connection {

class BoardConnection {
 public:

  BoardConnection(ros::NodeHandle& nodeHandle);
  ~BoardConnection();

 private:

  // Read parameters from configuration file
  bool readParameters();
  void topicCallback(const std_msgs::Float32MultiArray& message);

  // Attributes
  ros::NodeHandle& nodeHandle_;
  ros::Subscriber subscriber_;
  ros::Publisher publisher_;
  std::string subscriberTopic_;
  std::string publisherTopic_;

};

}

#endif //PROJECT_BOARDCONNECTION_HPP
