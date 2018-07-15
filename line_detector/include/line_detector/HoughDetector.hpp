//
// Created by jose on 6/06/18.
//

#ifndef PROJECT_DETECTOR_HPP
#define PROJECT_DETECTOR_HPP


#include <iostream>
#include <ros/ros.h>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "line_detector/RoiCutter.hpp"


namespace line_detector {

enum DetectionColor {
  white = 0,
  yellow = 1
};

class HoughDetector {
 public:

  HoughDetector();
  ~HoughDetector();

  HoughDetector& detect(cv::Mat& image);
  HoughDetector& filterColor(DetectionColor color);
  HoughDetector& detectLines();
  bool readParameters();
  cv::Mat* getImagePtr();
  cv::Mat* getBwImagePtr();
  cv::Mat* getHlsImagePtr();
  cv::Mat* getEdgesPtr();

  cv::Mat edges_;
  DetectionColor color_;
  void findEdges(); 

 private:

  cv::Mat* bgr_image_ptr;
  cv::Mat bw_image_;
  cv::Mat hls_image_;
  cv::Mat color_range_img_;
  std::vector<cv::Vec4i> detected_lines_;

  // Parameters
  std::vector<int> hls_white1;
  std::vector<int> hls_white2;
  std::vector<int> hls_yellow1;
  std::vector<int> hls_yellow2;
  std::vector<int> canny_threshold;
  int dilatation_kernel_size;
  int hough_threshold_;
  int hough_min_line_length_;
  int hough_max_line_gap_;

  RoiCutter cutter_;

};

}

#endif //PROJECT_DETECTOR_HPP
