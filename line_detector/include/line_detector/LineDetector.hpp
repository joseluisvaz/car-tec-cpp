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
#include <car_tec_msgs/SegmentList.h>
#include <car_tec_msgs/Segment.h>

namespace line_detector {

class LineDetector {
 public:

  LineDetector(ros::NodeHandle& nodeHandle);
  ~LineDetector();

 private:

  bool readParameters();
  void imageCb(const sensor_msgs::ImageConstPtr &message);
  void toSegmentList(std::vector<cv::Vec4i>& inputLines, 
                     car_tec_msgs::SegmentList& outputSegments);

  // Attributes
  ros::NodeHandle& nh_;
  image_transport::ImageTransport it_;
  HoughDetector detector_;
  image_transport::Subscriber subscriber_;
  image_transport::Publisher publisher1_;
  image_transport::Publisher publisher2_;
  ros::Publisher publisher_segments_;


  // Config parameters
  std::string subscriberTopic_;
  std::string publisherTopic1_;
  std::string publisherTopic2_;
  std::string publisherTopicSegments_;
  int subs_queue_size_;
  int pubs_queue_size_;
  int buff_size_;



};

}


#endif //PROJECT_LINEDETECTOR_HPP
