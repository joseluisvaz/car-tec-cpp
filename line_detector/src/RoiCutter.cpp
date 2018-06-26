#include "line_detector/RoiCutter.hpp"
#include <ros/ros.h>

using namespace std;

namespace line_detector {

RoiCutter::RoiCutter() {
    if(!loadParameters()) {
       ROS_ERROR("Could not read parameters for RoiCutter.");
       ros::requestShutdown();
    }
}

RoiCutter::~RoiCutter() {};

void RoiCutter::cutImage(cv::Mat& image) {
    cv::Mat mask = cv::Mat::zeros(img_size_[0], img_size_[1], CV_8U);
    const cv::Point* ppt =  vertices_ ;
    cv::fillPoly(mask, &ppt, &numberOfPoints_, 1, cv::Scalar(255, 255, 255), 8);
    // Bitwise and to cut the region imposed by mask
    output_ = image & mask;
    cv::imshow("Image", output_);
    cv::waitKey(1);

}

void RoiCutter::setVertices() {
    vertices_[0] = cv::Point(leftBottom_[0], leftBottom_[1]);
    vertices_[1] = cv::Point(leftApex_[0], leftApex_[1]);
    vertices_[2] = cv::Point(rightApex_[0], rightApex_[1]);
    vertices_[3] = cv::Point(rightBottom_[0], rightBottom_[1]);
    vertices_[4] = cv::Point(innerRightBottom_[0], innerRightBottom_[1]);
    vertices_[5] = cv::Point(innerRightApex_[0], innerRightApex_[1]);
    vertices_[6] = cv::Point(innerLeftApex_[0], innerLeftApex_[1]);
    vertices_[7] = cv::Point(innerLeftBottom_[0], innerLeftBottom_[1]);
}

bool RoiCutter::loadParameters() {
    if (!ros::param::get("~img_size", img_size_)){
        ROS_ERROR("Could not read parameters for 1.");
        return false;
    }
    if (!ros::param::get("~left_bottom", leftBottom_)){
        ROS_ERROR("Could not read parameters for 1.");
        return false;
    }
    if (!ros::param::get("~right_bottom", rightBottom_)){
        ROS_ERROR("2Could not read parameters for RoiCutter.");
        return false;
    }
    if (!ros::param::get("~apex1", leftApex_)){
        ROS_ERROR("3Could not read parameters for RoiCutter.");
        return false;
    }
    if (!ros::param::get("~apex2", rightApex_)){
        ROS_ERROR("4Could not read parameters for RoiCutter.");
        return false;
    }
    if (!ros::param::get("~inner_left_bottom", innerLeftBottom_)){
        ROS_ERROR("5Could not read parameters for RoiCutter.");
        return false;
    }
    if (!ros::param::get("~inner_right_bottom", innerRightBottom_)){
        ROS_ERROR("6Could not read parameters for RoiCutter.");
        return false;
    }
    if (!ros::param::get("~inner_apex1", innerLeftApex_)){
        ROS_ERROR("7Could not read parameters for RoiCutter.");
        return false;
    }
    if (!ros::param::get("~inner_apex2", innerRightApex_)){
        ROS_ERROR("8Could not read parameters for RoiCutter.");
        return false;
    }
    return true;
}


}