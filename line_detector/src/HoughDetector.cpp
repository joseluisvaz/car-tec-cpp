//
// Created by jose on 6/06/18.
//

#include "line_detector/HoughDetector.hpp"

using namespace std;

namespace line_detector {

HoughDetector::HoughDetector() {
  if (!readParameters()) {
    ROS_ERROR("Could not read parameters.");
    ros::requestShutdown();
  }
  cutter_.setVertices();
};

HoughDetector::~HoughDetector() {};

HoughDetector& HoughDetector::detect(cv::Mat& image) {
  if (&image == nullptr) {
    ROS_ERROR("Could not set image");
    ros::requestShutdown();
  }
  bgr_image_ptr = &image;
  cv::cvtColor(image, bw_image_, cv::COLOR_BGR2GRAY);
  cv::cvtColor(image, hls_image_, cv::COLOR_BGR2HLS);
  findEdges();
  return *this;
}

HoughDetector& HoughDetector::filterColor(DetectionColor color){
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

  auto kernel_size = cv::Size(dilatation_kernel_size, dilatation_kernel_size);
  auto kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, kernel_size);
  cv::dilate(color_range_img_, color_range_img_, kernel);
  cv::bitwise_and(color_range_img_, edges_, color_range_img_);
  return *this;
}

HoughDetector& HoughDetector::detectLines() {
  HoughLinesP(color_range_img_, 
              detected_lines_, 
              1, 
              CV_PI/180, 
              hough_threshold_, 
              hough_min_line_length_, 
              hough_max_line_gap_);

  // Print the lines in video
  for (size_t i = 0; i < detected_lines_.size(); i++) {
    cv::Vec4i line = detected_lines_[i];
    cv::line(*bgr_image_ptr, 
         cv::Point(line[0], line[1]), 
         cv::Point(line[2], line[3]), 
         cv::Scalar(0,0,255), 
         3, 
         CV_AA);
  }
  cv::imshow("lines show", *getImagePtr());
  cv::waitKey(1);
  return *this;
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
  return bgr_image_ptr;
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
     && ros::param::get("~color_config/canny_threshold", canny_threshold) 
     && ros::param::get("~color_config/hough_threshold", hough_threshold_) 
     && ros::param::get("~color_config/hough_min_line_length", hough_min_line_length_) 
     && ros::param::get("~color_config/hough_max_line_gap", hough_max_line_gap_) 
     && ros::param::get("~color_config/dilatation_kernel_size", dilatation_kernel_size)) 
    return true;
  return false;
}

}