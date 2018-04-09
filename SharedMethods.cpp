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

void gaussianBlur(int, void *)
{

    Mat src;
    if(!checkIfGrayScale(final_pic))
        cvtColor(final_pic, src, CV_GRAY2BGR);
    else
        src = final_pic;
    GaussianBlur(src, final_pic, Size(5,5), 0,0, BORDER_DEFAULT);

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
    //out << "in Canny" << endl;
    Mat src;
    if(checkIfGrayScale(final_pic))
    {
        cout << "converting \n";
        cvtColor(final_pic, src, CV_BGR2GRAY);
    }
    else
        src = final_pic;
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
