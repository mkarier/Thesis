/*
 * OpenCVLibrary.h
 *
 *  Created on: Oct 19, 2017
 *      Author: marco
 */

#ifndef OPENCVLIBRARY_H_
#define OPENCVLIBRARY_H_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

extern Mat final_pic, input, current_final;
extern string final_name;
extern vector<void  (*)(int, void*)>methods;
extern vector<void  (*)(int, void *)>::iterator fun_it;
extern int frame_left, frame_right, frame_top, frame_bottom;
extern int thickness;

void showFinal(int, void *);
bool checkIfGrayScale(Mat& src);
Mat getGrayscale(Mat& src);

void gaussianBlur(int, void *);
void regularBlur(int, void *);

void houghTransform(int, void *);
void fill(int, void *);

void addFrame(int, void *);

string processImage(Mat pic);
void printIndividualContours(Mat pic);
void printGroups(vector<int> windows, Mat pic);
#endif /* OPENCVLIBRARY_H_ */
