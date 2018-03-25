/*
 * OpenCVLibrary.h
 *
 *  Created on: Oct 19, 2017
 *      Author: marco
 */

#ifndef OPENCVLIBRARY_H_
#define OPENCVLIBRARY_H_

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

extern Mat final_pic, input;
extern string final_name;
extern vector<void  (*)(int, void*)>methods;
extern vector<void  (*)(int, void *)>::iterator fun_it;

void showFinal(int, void *);
bool checkIfGrayScale(Mat& src);

void gaussianBlur(int, void *);
void regularBlur(int, void *);

void houghTransform(int, void *);
void fill(int, void *);
#endif /* OPENCVLIBRARY_H_ */
