//============================================================================
// Name        : EdgeDetection.cpp
// Author      : Marco Karier
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "OpenCVLibrary.h"
#include "HighContrast.h"
#include "ColorReduce.h"
#include "Wavelet.h"
#include "ArrayBuffer.h"
#include "Otsu.h"
#include "Sobel.h"
#include "Ratio.h"

vector<void (*)(int, void *)>methods =  {
        gaussianBlur,
                                             gaussianBlur,
                                            // highContrast,
                                             //colorReduce,
                                             //dhwt2d,
                                             sobelEdgeDetection,
                                             //CannyThreshold,
                                             
                                             gaussianBlur,
					    // houghTransform,
                                             //regularBlur,
					     //fill,

                                             //fill,
                                             CannyThreshold,
                                             regularBlur,
                                             sobelEdgeDetection,
                                             //otsuThreshold,
                                             regularThreshold,
                                             //sobelEdgeDetection,
                                             showFinal
                                         };

vector<void  (*)(int, void *)>::iterator fun_it;
int read_in_style = CV_64FC1;
int threshold_value = 0;
int threshold_type = 0;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;
int alpha = 10;
int beta = 0;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int c_ratio = 3;
int kernel_size = 3;


//for otsu
int otsu_total = 0;
Ratio ratio_array[max_value + 1];
string final_name = "final picture";
Mat input, src_gray, hc_src, final_pic;
string ctrl = "controlWindow";


int main(int argc, char * argv[])
{
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!
	namedWindow(ctrl, CV_WINDOW_NORMAL);
    namedWindow( final_name, CV_WINDOW_NORMAL);
    input = imread(argv[1], read_in_style);
    Mat original = imread(argv[1], read_in_style);
    if (input.empty()) {
        std::cout << "!!! Failed imread()" << std::endl;
        input = imread("~/Dropbox/ImageProcessing/EdgeDetection/kana.jpg", read_in_style);
        original = imread("~/Dropbox/ImageProcessing/EdgeDetection/kana.jpg", read_in_style);
        if (input.empty()) {
            cout << "Still couldn't find the file" << endl;
            return -1;
        }
    }
    ///create a Trackbar for high contrast
    createTrackbar("alpha", ctrl, &alpha, 30, methods[0]);
    createTrackbar("beta", ctrl, &beta, 100, methods[0]);

    ///Create a Trackbar for user to enter threshold
    createTrackbar( "Canny Min Threshold:", ctrl, &lowThreshold, max_lowThreshold, methods[0]);

    ///create a track bar for Threshold
    createTrackbar("regular Threshold value", ctrl, &threshold_value, max_value, methods[0]);
    createTrackbar("threshold style", ctrl, &threshold_type, max_type, methods[0]);

    buffArray(input);
    input.copyTo(final_pic);
    fun_it = methods.begin();
    methods[0](0,0);

    imshow(ctrl, original);
    //imwrite("output.jpg", input);
    waitKey(0);
    destroyAllWindows();

	return 0;
}//end of main


