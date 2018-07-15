//
// Created by mkarier on 4/24/18.
//

#include "ImageNode.h"
ImageNode::ImageNode(string path, string filename)
{
    this->path = path;
    this->filename = filename;
    this->image = imread(path + filename, CV_LOAD_IMAGE_GRAYSCALE);
}

void ImageNode::loadContours()
{
    findContours(this->image, this->contours, this->hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
}

void ImageNode::printImage()
{
    namedWindow(filename, CV_WINDOW_NORMAL);
    Mat dst = Mat::zeros(this->image.size(), CV_8UC3);;
    int thickness = 8;
    //for(int index = 0; index < hierarchy.size(); index++)
    for(int index = 0 ; index >= 0; index = hierarchy[index][0])
    {
        // cout << "index = " << index << endl;
        Scalar color(rand()&255, rand()&255, rand()&255);
        drawContours(dst, contours, index, color, thickness, LINE_8, hierarchy);
    }
    imshow(filename, dst);
}//

bool ImageNode::compareImage(vector<vector<Point>> search_Contours)
{
    for(vector<Point> current: this->contours)
    {
        for(vector<Point> search: search_Contours)
        {
            double outcome = matchShapes(current, search, CONTOURS_MATCH_I3, 0 );
            if(outcome == 0)
            {
                cout << "Outcome of comparing " << this->filename  + " " << outcome <<endl;
                printImage();
            }

        }
    }
}//end of compareImage
