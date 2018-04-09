/*
 * Wavelet.cpp
 *
 *  Created on: Oct 19, 2017
 *      Author: marco
 */
#include"Wavelet.h"
//TODO: Make sure to do the same thing but with columns instead of just rows
void dhwt1dRow(Mat& src, Mat& dst, int row)
{
	int nc = src.cols;/// * src.channels();
	for(int length = nc/2;  ;length = length/2)
	{
		for(int i = 0; i < length; ++i)
		{
			uchar sum = src.at<uchar>(Point(i*2, row)) + src.at<uchar>(Point(i*2 + 1, row));
			uchar difference = src.at<uchar>(Point(i*2, row)) - src.at<uchar>(Point(i*2 + 1, row));
			dst.at<uchar>(Point(i,row)) = sum/(2.0);
			dst.at<uchar>(Point(length + i, row)) = difference/(2.0);
		}//end of inner for loop
		if(length == 1)
		{
			//copyArray(output, 0, src, 0, length);
			//src = dst;
			return;
		}//end of if
		src = dst;
		//copyArray(output, src, length);
	}//end of outer for loop
}//end of dhwt1

void dhwt1dColumn(Mat& src, Mat& dst, int column)
{
	int nc = src.rows;// * src.channels();
	for(int length = nc/2;  ;length = length/2)
	{
		for(int i = 0; i < length; ++i)
		{
			uchar sum = src.at<uchar>(Point(column, i*2)) + src.at<uchar>(Point(column, i*2 + 1));
			uchar difference = src.at<uchar>(Point(column, i*2)) - src.at<uchar>(Point(column, i*2 + 1));
			dst.at<uchar>(Point(column, i)) = sum/(2.0);
			dst.at<uchar>(Point(column, length + i)) = difference/(2.0);
		}//end of inner for loop
		if(length == 1)
		{
			//copyArray(output, 0, src, 0, length);
			src = dst;
			return;
		}//end of if
		src = dst;
		//copyArray(output, src, length);
	}//end of outer for loop
}//end of dhwt1

void dhwt2d(int, void *)
{
	Mat src = final_pic;
   /* if(!checkIfGrayScale(final_pic))
    {
        cout << "converting pic \n";
        cvtColor(final_pic, src, CV_BGR2GRAY);
    }//end of if statement
    else
        src = final_pic;//*/
	int nl = src.rows;
	int nc = src.cols;/// * src.channels();
	Mat output_row = src.clone();
	Mat output_column = src.clone();
    Mat abs_output_row, abs_output_column;
	for(int y = 0; y< nl; y++)
	{
		dhwt1dRow(src, output_row, y);

	}//end of for loop
    convertScaleAbs(output_row, abs_output_row);
	for(int y = 0; y< nc; y++)
	{
		dhwt1dColumn(src, output_column, y);

	}//end of for loop
    convertScaleAbs(output_column, abs_output_column);
	addWeighted(abs_output_column, 0.5, abs_output_row, 0.5, 0, final_pic);
	void (*next)(int, void *)  = *(++fun_it);
	next(0,0);
}//end of waveletTransform

void copyArray(uchar* src, uchar* dst, int length)
{
	int count = 0;
	for( ; count < length; ++count)
		dst[count] = src[count];
}//end of swapArray

