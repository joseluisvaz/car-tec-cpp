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

  bool detect(cv::Mat& image, DetectionColor color);
  void filterColor(DetectionColor color);
  bool readParameters();
  cv::Mat* getImagePtr();
  cv::Mat* getBwImagePtr();
  cv::Mat* getHlsImagePtr();
  cv::Mat* getEdgesPtr();

  cv::Mat edges_;
  void findEdges(); 

 private:


  cv::Mat bgr_image_;
  cv::Mat bw_image_;
  cv::Mat hls_image_;
  cv::Mat color_range_img_;;

  std::vector<int> hls_white1;
  std::vector<int> hls_white2;
  std::vector<int> hls_yellow1;
  std::vector<int> hls_yellow2;
  std::vector<int> canny_threshold;

  RoiCutter cutter_;

};

}

#endif //PROJECT_DETECTOR_HPP
