//
// Created by jose on 4/06/18.
//

#include "line_detector/LineDetector.hpp"

using namespace std;

static const string WINDOW_NAME = "Edges";
static const int SIZE = 5;


namespace line_detector {

LineDetector::LineDetector(ros::NodeHandle& nh)
    : nh_{nh},
      it_{nh_}
  {

  // Test hough_detect
  if (!readParameters()) {
    ROS_ERROR("Could not read parameters.");
    ros::requestShutdown();
  }

  subscriber_ = it_.subscribe(subscriberTopic_, 1,
                              &LineDetector::imageCb, this);
  publisher1_ = it_.advertise(publisherTopic1_, 1000);
  publisher2_ = it_.advertise(publisherTopic2_, 1000);
  publisher3_ = it_.advertise(publisherTopic3_, 1000);
  publisher4_ = it_.advertise(publisherTopic4_, 1000);

  cv::namedWindow(WINDOW_NAME);
  ROS_INFO("Succesfully launched node. ");
}

LineDetector::~LineDetector() {
  cv::destroyWindow(WINDOW_NAME);
};

bool LineDetector::readParameters() {
  // If all parameters are loaded
  if (nh_.getParam("subscriber_topic", subscriberTopic_)
      && nh_.getParam("publisher_topic_1", publisherTopic1_)
      && nh_.getParam("publisher_topic_2", publisherTopic2_)
      && nh_.getParam("publisher_topic_3", publisherTopic3_)
      && nh_.getParam("publisher_topic_4", publisherTopic4_)
      && nh_.getParam("subs_queue_size", subs_queue_size_)
      && nh_.getParam("pubs_queue_size", pubs_queue_size_)
      && nh_.getParam("buff_size", buff_size_))
    return true;
  return false;
}

void LineDetector::imageCb(const sensor_msgs::ImageConstPtr &message) {
  cv_bridge::CvImagePtr cv_ptr;

  try {
    cv_ptr = cv_bridge::toCvCopy(message, sensor_msgs::image_encodings::BGR8);
  }
  catch (cv_bridge::Exception& e) {
    ROS_ERROR("cv_bridge exception: %s", e.what());
    return;
  }

  detector_.detect(cv_ptr->image)
           .filterColor(DetectionColor::white)
           .detectLines();

  cv::imshow(WINDOW_NAME, *detector_.getEdgesPtr());
  cv::waitKey(1);

  publisher1_.publish(cv_ptr->toImageMsg());
}

}
