#include "ImageCompare.h"



int main(int argc, char ** args)
{
    if(argc < 1)
    {
        cout << "no file was given" << endl;
        exit(0);
    }

    Mat input_pic = imread(args[1], CV_LOAD_IMAGE_GRAYSCALE);
    if(input_pic.empty())
    {
        cout << "couldn't load image" << endl;
        exit(-1);
    }
    string before = "image used to fined contour";
    namedWindow(before, CV_WINDOW_NORMAL);
    string after = "Final with contour";
    namedWindow(after, CV_WINDOW_NORMAL);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    RNG rng(1234);
    findContours(input_pic, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
    cout << "done findinging contour." << endl;
    Mat dst = Mat::zeros(input_pic.size(), CV_8UC3);
    imshow(before, input_pic);
    int thickness = 8;
    //for(int index = 0; index < hierarchy.size(); index++)
    for(int index = 0 ; index >= 0; index = hierarchy[index][0])
    {
       // cout << "index = " << index << endl;
        //Scalar color(rand()&255, rand()&255, rand()&255);
        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        drawContours(dst, contours, index, color, thickness, LINE_8, hierarchy);
    }
    imshow(after, dst);
   // cout << processImage(dst);
    waitKey(0);
    destroyAllWindows();
    return 0;
}