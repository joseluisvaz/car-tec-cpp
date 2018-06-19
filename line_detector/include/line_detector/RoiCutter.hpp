
#ifndef PROJECT_DETECTOR_HPP
#define PROJECT_DETECTOR_HPP

#include <vector>
#include <tuple>

using namespace std;

namespace roi_cutter {

class RoiCutter {

public:
    RoiCutter();
    ~RoiCutter();

    typedef tuple<int, int> intTuple;
    
    void setImageSize(intTuple size);
    void setVertices(vector<intTuple>& vertices);

private:
    vector<intTuple> vertices;

};

}

#endif //PROJECT_LINEDETECTOR_HPP