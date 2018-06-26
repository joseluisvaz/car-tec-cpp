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

void HoughDetector::detect() {
  findEdges_();
}

bool HoughDetector::setImage(cv::Mat& image){
    if (&image == nullptr) {
      return false;
    }
    bgr_image_ = image;
    cv::cvtColor(bgr_image_, bw_image_, cv::COLOR_BGR2GRAY);
    cv::cvtColor(bgr_image_, hls_image_, cv::COLOR_BGR2HLS);
    findEdges_();
}

void HoughDetector::findEdges_() {
  cv::Canny(bw_image_, 
            edges_,
            canny_threshold[0],
            canny_threshold[1],
            3);
  cutter_.cutImage(edges_);
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