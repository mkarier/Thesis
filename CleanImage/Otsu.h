//
// Created by mkarier on 11/17/17.
//

#ifndef EDGEDETECTION_OTSU_H
#define EDGEDETECTION_OTSU_H

#include "OpenCVLibrary.h"
#include "Ratio.h"
#include "thread"

extern Mat src_gray;
extern int otsu_total;
extern const int max_value;
extern Ratio ratio_array[];
extern string final_name;

extern int threshold_value;// = 60;
extern int threshold_type;// = 0;
extern int const max_type;// = 4;
extern int const max_BINARY_value;// = 255;

void otsuThreshold(int, void *);
void regularThreshold(int, void *);
void findRatioArray();
void createRatioArray();
void applyThreshold(int threshold);
void findClassVariance(int threshold, float * spot);
float findWeight(Ratio * array, int size);
float findMean(Ratio * array, int size);
float findVariance(Ratio * array, int size, float mean);



#endif //EDGEDETECTION_OTSU_H
