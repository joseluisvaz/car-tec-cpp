//
// Created by jose on 4/06/18.
//

#include "line_detector/LineDetector.hpp"

using namespace std;

namespace line_detector {

LineDetector::LineDetector(ros::NodeHandle& nodeHandle)
    : nodeHandle_(nodeHandle) {

  if(!readParameters()) {
    ROS_ERROR("Could not read parameters.");
    ros::requestShutdown();
  }

  subscriber_ = nodeHandle_.subscribe(subscriberTopic_, 1,
                                      &LineDetector::topicCallback, this);
  publisher_ = nodeHandle_.advertise<sensor_msgs::Image>(publisherTopic_, 1000);

  ROS_INFO("Succesfully launched node. ");
}

LineDetector::~LineDetector() = default;

bool LineDetector::readParameters() {
  // If all parameters are loaded
  if(nodeHandle_.getParam("subscriber_topic", subscriberTopic_)
      && nodeHandle_.getParam("publisher_topic", publisherTopic_)
      && nodeHandle_.getParam("subs_queue_size", subs_queue_size_)
      && nodeHandle_.getParam("pubs_queue_size", pubs_queue_size_))
    return true;
  return false;
}

void LineDetector::topicCallback(const sensor_msgs::Image &message) {
  publisher_.publish(message);
}

}
