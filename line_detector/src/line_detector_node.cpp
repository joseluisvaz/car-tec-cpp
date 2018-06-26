//
// Created by jose on 4/06/18.
//

#include <iostream>
#include <ros/ros.h>
#include "line_detector/LineDetector.hpp"
#include "line_detector/HoughDetector.hpp"
#include "line_detector/RoiCutter.hpp"

using namespace line_detector;
using namespace std;

int main(int argc, char** argv) {

  ros::init(argc, argv, "line_detector");
  ros::NodeHandle nodeHandle("~");
  LineDetector lineDetector(nodeHandle);

  ros::spin();
  return 0;
}
