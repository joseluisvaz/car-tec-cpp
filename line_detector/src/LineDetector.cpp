//
// Created by jose on 4/06/18.
//

#include "line_detector/LineDetector.hpp"

static const std::string WINDOW_NAME = "OpenCv Window";

using namespace std;
using namespace cv;

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

  namedWindow(WINDOW_NAME);

  ROS_INFO("Succesfully launched node. ");
}

LineDetector::~LineDetector() {
  destroyWindow(WINDOW_NAME);
};

bool LineDetector::readParameters() {
  // If all parameters are loaded
  if(nodeHandle_.getParam("subscriber_topic", subscriberTopic_)
      && nodeHandle_.getParam("publisher_topic", publisherTopic_)
      && nodeHandle_.getParam("subs_queue_size", subs_queue_size_)
      && nodeHandle_.getParam("pubs_queue_size", pubs_queue_size_))
    return true;
  return false;
}

void LineDetector::topicCallback(const sensor_msgs::ImageConstPtr &message) {

  cv_bridge::CvImagePtr cv_ptr;

  try {
    cv_ptr = cv_bridge::toCvCopy(message, sensor_msgs::image_encodings::BGR8);
  }
  catch (cv_bridge::Exception & e) {
    ROS_ERROR("cv_bridge exception: %s", e.what());
    return;
  }

  // If window is big enough
  if (cv_ptr->image.rows > 60 && cv_ptr->image.cols > 60)
    circle(cv_ptr->image, Point(50, 50), 10, CV_RGB(255,0,0));

  imshow(WINDOW_NAME, cv_ptr->image);
  waitKey(3);

  publisher_.publish(cv_ptr->toImageMsg());
}

}
