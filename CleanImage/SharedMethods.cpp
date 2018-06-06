//
// Created by mkarier on 11/18/17.
//

#include "OpenCVLibrary.h"

void showFinal(int, void *)
{
    fun_it = methods.begin();
    Mat output;
    final_pic.copyTo(output);
    final_pic.copyTo(current_final);
    input.copyTo(final_pic);
    imshow(final_name, output);
}//end of showFinal

bool checkIfGrayScale(Mat& src)
{
    return ~(src.channels() == 3);
}

Mat getGrayscale(Mat& src)
{
	Mat gray_scale;
	if(!checkIfGrayScale(src))
        cvtColor(src, gray_scale, CV_BGR2GRAY);
    else
        gray_scale = src;
	return gray_scale;
}
void gaussianBlur(int, void *)
{

    Mat src;
    if(!checkIfGrayScale(final_pic))
        cvtColor(final_pic, src, CV_GRAY2BGR);
    else
        src = final_pic;
    GaussianBlur(src, final_pic, Size(3,3), 0,0, BORDER_DEFAULT);

    void (*next)(int, void *)  = *(++fun_it);
    next(0,0);
}

void regularBlur(int, void *)
{
    Mat src = final_pic;
    blur(src, final_pic, Size(3,3), Point(-1,-1), BORDER_DEFAULT );

    void (*next)(int, void *)  = *(++fun_it);
    next(0,0);

}

void fill(int, void *)
{

    Mat src = getGrayscale(final_pic);
	vector<vector<Point> > contours;
  	vector<Vec4i> hierarchy;
	findContours( src, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

	/// Draw contours
	Mat drawing = Mat::zeros(src.size(), CV_8UC3 );
	for( int i = 0; i< contours.size(); i++ )
	{
		Scalar color = Scalar( 255 ,255,255 );
		drawContours( drawing, contours, i ,color, 1, 8, hierarchy, INT_MAX, Point(-1 ,-1) );
	}

	fillPoly(drawing, contours, cv::Scalar::all(255),8);
	final_pic = drawing;

	void (*next)(int, void *)  = *(++fun_it);
   	next(0,0);
}

void houghTransform(int, void *)
{
    Mat src;
    if(!checkIfGrayScale(final_pic))
        cvtColor(final_pic, src, CV_GRAY2BGR);
    else
        src = final_pic;

    vector<Vec4i> lines;
    HoughLinesP(src, lines, 1, CV_PI/180, 50, 50, 10 );
    for( size_t i = 0; i < lines.size(); i++ )
    {
        Vec4i l = lines[i];
        line(src, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
    }

    final_pic = src;
    void (*next)(int, void *)  = *(++fun_it);
    next(0,0);
}//end of houghTransform

void addFrame(int, void *)
{
    Mat src = getGrayscale(final_pic);
    int maxCols = src.cols * src.channels();
    int maxRows = src.rows;
    int distanceRight = maxCols - frame_right;
    int distanceBottom = maxRows - frame_bottom;
    for (int x = 0; x < maxRows; x++)
    {
        for (int y = 0; y < maxCols; y++)
        {
            if(y <= frame_left || y >= distanceRight)
                src.at<uchar>(x,y) = 0;
            else if(x <= frame_top || x >= distanceBottom)
                src.at<uchar>(x, y) = 0;
        }//end of for for loop to change the columns.
    }//end of a for loop to change the columns
    final_pic = src;
    void (*next)(int, void *)  = *(++fun_it);
    next(0,0);
}

string processImage(Mat pic)
{
    //string before = "image used to fined contour";
    //namedWindow(before, CV_WINDOW_NORMAL);
    //imshow(before, pic);
    Mat gray_scale = getGrayscale(pic);
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(gray_scale, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    Mat dst = Mat::zeros(gray_scale.size(), CV_8UC3);
    int index = 0;
    for( ; index >= 0; index = hierarchy[index][0])
    {
        Scalar color(rand()&255, rand()&255, rand()&255);
        drawContours(dst, contours, index, color, thickness, LINE_4, hierarchy);
    }//end of for loop*/

    string after = "Found Contour";
    namedWindow(after, CV_WINDOW_NORMAL);
    imshow(after, dst);
    //TODO: get the letters to make up the character
    return "Still need to fix this";
}//end of processImage

void printIndividualContours(Mat pic)
{
    Mat gray_scale = getGrayscale(pic);
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(gray_scale, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	
    string name_prefix = "window";
    for(int index = 0 ; index >= 0; index = hierarchy[index][0])
    {
        string window = name_prefix + to_string(index);
        namedWindow(window, CV_WINDOW_NORMAL);
        Mat dst = Mat::zeros(gray_scale.size(), CV_8UC3);
        //cout << "index = " << index << endl;
        string number = to_string(index);
        Scalar color(rand()&255, rand()&255, rand()&255);
        drawContours(dst, contours, index, color, thickness, LINE_8, hierarchy);
        imshow(window, dst);
    }//end of for loop*/ = find(methods.begin(), methods.end(), addFrame);
}///end of printIndividual Contours


void printGroups(vector<int> windows, Mat pic)
{
    Mat gray_scale = getGrayscale(pic);
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(gray_scale, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    Mat dst = Mat::zeros(gray_scale.size(), CV_8UC3);

    for(int count = 0; count < windows.size(); count++)
    {

        //cout << "index = " << index << endl;
        int index = windows[count];
        Scalar color(rand()&255, rand()&255, rand()&255);
        drawContours(dst, contours, index, color, thickness, LINE_8, hierarchy);
    }//end of for loop*/

    string after = "user grouped image";
    namedWindow(after, CV_WINDOW_NORMAL);
    imshow(after, dst);
}///endo of printGroups
