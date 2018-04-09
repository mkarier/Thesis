//
// Created by mkarier on 11/5/17.
//

#ifndef EDGEDETECTION_HIGHCONTRAST_H
#define EDGEDETECTION_HIGHCONTRAST_H
#include"OpenCVLibrary.h"
#include"Canny.h"

extern int alpha;// = 1;//can be values [10 - 30]
extern int beta;// = 100;//can be values [0-100]
extern Mat hc_src, input;
extern string hc_name;

void highContrast(int, void *);
void highContrast(double s_alpha, int s_beta, Mat& src);
void showFinal(int, void *);

#endif //EDGEDETECTION_HIGHCONTRAST_H
