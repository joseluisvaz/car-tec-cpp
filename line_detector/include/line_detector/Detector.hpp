//
// Created by jose on 6/06/18.
//

#ifndef PROJECT_DETECTOR_HPP
#define PROJECT_DETECTOR_HPP


#include <iostream>
#include <opencv2/imgcodecs.hpp>

namespace detector {

class Detector {
 public:

  Detector(int size);
  ~Detector();
  int getSize();

 private:
  int size_;

};

}

#endif //PROJECT_DETECTOR_HPP
