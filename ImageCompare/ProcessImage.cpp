//
// Created by mkarier on 4/3/18.
//
#include "ImageCompare.h"

/*
 * TODO: try to find the discrete set and return it
 */
string processImage(Mat pic)
{
    string before = "image used to fined contour";
    namedWindow(before, CV_WINDOW_NORMAL);
    imshow(before, pic);
    Mat gray_scale;
    cvtColor(pic, gray_scale, CV_BGR2GRAY);
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(pic, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
    Mat dst = Mat::zeros(pic.size(), CV_8UC1);
    int thickness = 8;
    int index = 0;
    for( ; index >= 0; index = hierarchy[index][0])
    {
        //cout << "index = " << index << endl;
        Scalar color(rand()&255, rand()&255, rand()&255);
        drawContours(dst, contours, index, color, thickness, LINE_8, hierarchy);
    }//end of for loop*/
    cout << "In Process Image method" << endl;
    return "Still need to fix this";
}