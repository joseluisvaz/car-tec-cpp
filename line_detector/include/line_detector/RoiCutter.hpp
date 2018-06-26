
#ifndef PROJECT_CUTTER_HPP
#define PROJECT_CUTTER_HPP

#include <vector>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

static const int ROWS = 1;
static const int COLUMNS = 8;

namespace line_detector {

class RoiCutter {

public:
    RoiCutter();
    ~RoiCutter();

    void setImageSize(vector<int>& size);
    void setVertices();
    void cutImage(cv::Mat& image);
    bool loadParameters();
    
private:
    // Initialize matrix of points for
    int numberOfPoints_ = 8;
    cv::Point vertices_[8];

    // TODO: ERAAASEE
    cv::Mat output_;

    vector<int> img_size_;
    vector<int> keke_;

    vector<int> leftBottom_;
    vector<int> rightBottom_;
    vector<int> leftApex_;
    vector<int> rightApex_;
    vector<int> innerLeftBottom_;
    vector<int> innerRightBottom_;
    vector<int> innerLeftApex_;
    vector<int> innerRightApex_;

};

}

#endif //PROJECT_LINEDETECTOR_HPP