//
// Created by jose on 4/06/18.
//

#include <iostream>
#include <ros/ros.h>
#include "line_detector/LineDetector.hpp"

int main(int argc, char** argv){

  ros::init(argc, argv, "line_detector");
  ros::NodeHandle nodeHandle("~");
  line_detector::LineDetector lineDetector(nodeHandle);

  ros::spin();
  return 0;
}
