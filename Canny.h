//
// Created by marco on 11/7/17.
//

#ifndef EDGEDETECTION_CANNY_H
#define EDGEDETECTION_CANNY_H

#include "OpenCVLibrary.h"
#include "Otsu.h"


extern Mat src_gray, input;
extern int edgeThresh;// = 1;
extern int lowThreshold;
extern int const max_lowThreshold;// = 100;
extern int c_ratio;// = 3;
extern int kernel_size;// = 3;
extern string final_name;// = "Edge Map";

void CannyThreshold(int, void*);

#endif //EDGEDETECTION_CANNY_H
