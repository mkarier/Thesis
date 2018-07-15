//
// Created by mkarier on 4/24/18.
//

#ifndef IMAGECOMPARE_IMAGENODE_H
#define IMAGECOMPARE_IMAGENODE_H

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

class ImageNode
{
    public:
        string path;
        string filename;
        Mat image;
        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;

        ImageNode(string path, string filename);
        void loadContours();
        void printImage();
        bool compareImage(vector<vector<Point>> search_Contours);
        ~ImageNode(){}
};


#endif //IMAGECOMPARE_IMAGENODE_H
