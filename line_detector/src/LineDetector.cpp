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
  publisher_segments_ = nh_.advertise<car_tec_msgs::SegmentList>(publisherTopicSegments_, 1000);

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
      && nh_.getParam("publisher_topic_segments", publisherTopicSegments_)
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

  car_tec_msgs::SegmentList segmentList;
  toSegmentList(*detector_.getDetectedLinesPtr(), segmentList);

  cv_ptr->image = *detector_.getImagePtr();
  publisher1_.publish(cv_ptr->toImageMsg());
  
  cv_ptr->image = *detector_.getEdgesPtr();
  publisher2_.publish(cv_ptr->toImageMsg());


  // TODO: ERASE THIS DEBUGGING STAGE


  publisher_segments_.publish(segmentList);

}

void LineDetector::toSegmentList(std::vector<cv::Vec4i>& inputLines, 
                                 car_tec_msgs::SegmentList& outputSegments) {
  for (auto& line: inputLines) {
    car_tec_msgs::Segment segment;
    segment.pixels_normalized[0].x = line[0];
    segment.pixels_normalized[0].y = line[1];
    segment.pixels_normalized[1].x = line[2];
    segment.pixels_normalized[1].y = line[3];
    outputSegments.segments.push_back(segment);
  }
}

}
