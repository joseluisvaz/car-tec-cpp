//
// Created by jose on 6/06/18.
//

#include "line_detector/HoughDetector.hpp"

using namespace std;

namespace line_detector {

HoughDetector::HoughDetector(int size) : size_(size) {};

HoughDetector::~HoughDetector() {};

void HoughDetector::detect() {
  cv::cvtColor(bgr_image_, bw_image_, cv::COLOR_BGR2GRAY);
  cv::cvtColor(bgr_image_, hls_image_, cv::COLOR_BGR2HLS);
}

bool HoughDetector::setImage(cv::Mat& image){
    if (&image == nullptr) {
      return false;
    }
    bgr_image_ = image;
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

int HoughDetector::getSize() {
  return size_;
}

}

