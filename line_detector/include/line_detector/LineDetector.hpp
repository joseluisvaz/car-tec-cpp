//
// Created by jose on 4/06/18.
//

#ifndef PROJECT_LINEDETECTOR_HPP
#define PROJECT_LINEDETECTOR_HPP

#include <ros/ros.h>
#include <iostream>
#include <vector>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <image_transport/image_transport.h>
#include "line_detector/HoughDetector.hpp"


namespace line_detector {

class LineDetector {
 public:

  LineDetector(ros::NodeHandle& nodeHandle);
  ~LineDetector();

 private:

  bool readParameters();
  void imageCb(const sensor_msgs::ImageConstPtr &message);

  // Attributes
  ros::NodeHandle& nh_;
  image_transport::ImageTransport it_;
  HoughDetector detector_;
  image_transport::Subscriber subscriber_;
  image_transport::Publisher publisher1_;
  image_transport::Publisher publisher2_;
  image_transport::Publisher publisher3_;
  image_transport::Publisher publisher4_;


  // Config parameters
  std::string subscriberTopic_;
  std::string publisherTopic1_;
  std::string publisherTopic2_;
  std::string publisherTopic3_;
  std::string publisherTopic4_;
  int subs_queue_size_;
  int pubs_queue_size_;
  int buff_size_;
  std::vector<int> hls_white1;
  std::vector<int> hls_white2;
  std::vector<int> hls_yellow1;
  std::vector<int> hls_yellow2;


};

}


#endif //PROJECT_LINEDETECTOR_HPP
