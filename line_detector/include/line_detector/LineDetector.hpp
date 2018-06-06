//
// Created by jose on 4/06/18.
//

#ifndef PROJECT_LINEDETECTOR_HPP
#define PROJECT_LINEDETECTOR_HPP

#include <ros/ros.h>
#include <iostream>
#include <sensor_msgs/Image.h>

namespace line_detector {

class LineDetector {
 public:

  explicit LineDetector(ros::NodeHandle& nodeHandle_);
  ~LineDetector();

 private:

  bool readParameters();
  void topicCallback(const sensor_msgs::Image& message);

  // Attributes
  ros::NodeHandle& nodeHandle_;
  ros::Subscriber subscriber_;
  ros::Publisher publisher_;

  // Config parameters
  std::string subscriberTopic_;
  std::string publisherTopic_;
  int subs_queue_size_;
  int pubs_queue_size_;


};

}


#endif //PROJECT_LINEDETECTOR_HPP
