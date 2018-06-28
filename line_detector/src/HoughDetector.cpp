//
// Created by jose on 6/06/18.
//

#include "line_detector/HoughDetector.hpp"

using namespace std;

namespace line_detector {

HoughDetector::HoughDetector()
    {
      if (!readParameters()) {
        ROS_ERROR("Could not read parameters.");
        ros::requestShutdown();
      }

      cutter_.setVertices();
    };

HoughDetector::~HoughDetector() {};


bool HoughDetector::detect(cv::Mat& image, DetectionColor color) {
    if (&image == nullptr) {
      return false;
    }
    cv::cvtColor(image, bw_image_, cv::COLOR_BGR2GRAY);
    cv::cvtColor(image, hls_image_, cv::COLOR_BGR2HLS);
    filterColor(color);
    findEdges();
    return true;
}

void HoughDetector::filterColor(DetectionColor color){
  switch(color) {
    case DetectionColor::white :
      cv::inRange(hls_image_, hls_white1, hls_white2, color_range_img_);
      break;
    case DetectionColor::yellow :
      cv::inRange(hls_image_, hls_yellow1, hls_yellow2, color_range_img_);
      break;
    default :
      ROS_ERROR("Wrong color type sent to HoughDetector::filterColor");
      ros::requestShutdown();
      break;
  }
  cv::imshow("color range", color_range_img_);
  cv::waitKey(1);
}

void HoughDetector::findEdges() {
  cv::Canny(bw_image_, 
            edges_,
            canny_threshold[0],
            canny_threshold[1],
            3);
  edges_ = *cutter_.cutImage(edges_);
}

cv::Mat* HoughDetector::getImagePtr() {
  return &bgr_image_;
}

cv::Mat* HoughDetector::getBwImagePtr() {
  return &bw_image_;
}

cv::Mat* HoughDetector::getHlsImagePtr() {
  return &hls_image_;
}

cv::Mat* HoughDetector::getEdgesPtr() {
  return &edges_;
}

bool HoughDetector::readParameters() {
  if(ros::param::get("~color_config/hls_white1", hls_white1)
     && ros::param::get("~color_config/hls_white2", hls_white2)
     && ros::param::get("~color_config/hls_yellow1", hls_yellow1)
     && ros::param::get("~color_config/hls_yellow2", hls_yellow2)
     && ros::param::get("~color_config/canny_threshold", canny_threshold)) 
    return true;
  return false;
}

}