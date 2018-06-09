//
// Created by jose on 6/06/18.
//

#include "line_detector/Detector.hpp"

using namespace std;

namespace detector {

Detector::Detector(int size) : size_(size) {
};

Detector::~Detector() {};

int Detector::getSize() {
  return size_;
}


}

