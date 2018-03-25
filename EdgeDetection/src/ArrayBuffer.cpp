/*
 * ArrayBuffer.cpp
 *
 *  Created on: Oct 24, 2017
 *      Author: marco
 */

#include "ArrayBuffer.h"



void buffArray(Mat& src)
{
	int rows = src.rows;
	int cols = src.cols;
	int type = src.type();
	Mat out(rows+1, cols+1, type);
	for(int y = 0; y < rows; y++)
	{
		for(int x = 0; x < cols; x++)
		{
			out.at<Vec3b>(Point(x,y)) = src.at<Vec3b>(Point(x,y));
		}
		out.at<Vec3b>(Point(cols,y)).val[0] = '$';
		out.at<Vec3b>(Point(cols,y)).val[1] = '$';
		out.at<Vec3b>(Point(cols,y)).val[2] = '$';
	}//end of for loop
	for(int x =0; x < cols + 1; x++)
	{
		out.at<Vec3b>(Point(x,rows)).val[0] = '$';
		out.at<Vec3b>(Point(x,rows)).val[1] = '$';
		out.at<Vec3b>(Point(x,rows)).val[2] = '$';
	}

	src = out;
}//end of buffArray

void buffRows(Mat& src)
{

}//end of buffRows

void buffCols(Mat& src)
{

}//end of buffCols


