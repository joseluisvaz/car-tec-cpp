//
// Created by jose on 3/06/18.
//

#include "board_connection/BoardConnection.hpp"

using namespace std;

namespace board_connection {

BoardConnection::BoardConnection(ros::NodeHandle& nodeHandle)
    : nodeHandle_(nodeHandle) {

  if(!readParameters()) {
    ROS_ERROR("Could not read parameters.");
    ros::requestShutdown();
  }

  subscriber_ = nodeHandle_.subscribe(subscriberTopic_, 1,
                                      &BoardConnection::topicCallback, this);
  publisher_ = nodeHandle_.advertise<std_msgs::Float32MultiArray>(publisherTopic_, 1000);

  ROS_INFO("Succesfully launched node. ");
}

BoardConnection::~BoardConnection() = default;

bool BoardConnection::readParameters() {
  // If all parameters are loaded
  if(nodeHandle_.getParam("subscriber_topic", subscriberTopic_)
      && nodeHandle_.getParam("publisher_topic", publisherTopic_)
      && nodeHandle_.getParam("subs_queue_size", subs_queue_size_)
      && nodeHandle_.getParam("pubs_queue_size", pubs_queue_size_))
    return true;
  return false;
}

void BoardConnection::topicCallback(const std_msgs::Float32MultiArray &message) {
  publisher_.publish(message);
}

}

