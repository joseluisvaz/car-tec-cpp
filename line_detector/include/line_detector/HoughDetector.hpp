//
// Created by jose on 6/06/18.
//

#ifndef PROJECT_DETECTOR_HPP
#define PROJECT_DETECTOR_HPP


#include <iostream>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace line_detector {

class HoughDetector {
 public:

  HoughDetector(int size);
  ~HoughDetector();

  void detect();

  bool setImage(cv::Mat& image);
  cv::Mat* getImagePtr();
  cv::Mat* getBwImagePtr();
  int getSize();

 private:
  cv::Mat bgr_image_;
  cv::Mat bw_image_;
  cv::Mat hls_image_;
  int size_;

};

}

#endif //PROJECT_DETECTOR_HPP
