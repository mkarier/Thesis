/*
 * ColorReduce.cpp
 *
 *  Created on: Oct 19, 2017
 *      Author: marco
 */


#include"ColorReduce.h"
void colorReduce(int, void *)
{
    cout << "in color reduce" << endl;
	Mat image;
    if(!checkIfGrayScale(final_pic))
	    cvtColor(final_pic, image, CV_GRAY2BGR);
    else
        image = final_pic;
	int div = 64;
    int nl = image.rows;                    // number of lines
    int nc = image.cols * image.channels(); // number of elements per line

    for (int j = 0; j < nl; j++)
    {
        // get the address of row j
        uchar* data = image.ptr<uchar>(j);

        for (int i = 0; i < nc; i++)
        {
            // process each pixel
            data[i] = data[i] / div * div + div / 2;
        }//inner for loop
    }//end of outer for loop
	final_pic = image;
	void (*next)(int, void *)  = *(++fun_it);
	next(0,0);
}//end of colorReduce method


/*
 * note the order is blue green red
 */
void removeColor(int, void *)
{
	Mat image = final_pic;
	int nl = image.rows;
	int nc = image.cols * image.channels();

	for(int y = 1; y < nl-1; y++)
	{
		for(int x = 1; x < nc-1; x++)
		{
			Vec3b pixel = image.at<Vec3b>(Point(x, y));
			if(pixel.val[0] == 160 && pixel.val[1] == 96 && pixel.val[2] == 96)
			{
				image.at<Vec3b>(Point(x, y)).val[0] = 0;
				image.at<Vec3b>(Point(x, y)).val[1] = 0;
				image.at<Vec3b>(Point(x, y)).val[2] = 0;
			}//end of if
			else if(pixel.val[0] == 160 && pixel.val[1] == 160 && pixel.val[2] == 96)
			{
				image.at<Vec3b>(Point(x, y)).val[0] = 0;
				image.at<Vec3b>(Point(x, y)).val[1] = 0;
				image.at<Vec3b>(Point(x, y)).val[2] = 0;
			}//end of else if
			else if(pixel.val[0] == 160 && pixel.val[1] == 96 && pixel.val[2] == 160)
			{
				image.at<Vec3b>(Point(x, y)).val[0] = 0;
				image.at<Vec3b>(Point(x, y)).val[1] = 0;
				image.at<Vec3b>(Point(x, y)).val[2] = 0;
			}//end of else if
			else if(pixel.val[0] == 160 && pixel.val[1] == 160 && pixel.val[2] == 160)//This if statement is to try and get rid of the extra gray pixels
			{
				//std::cout<<"found a 160"<<std::endl;

				//Vec3b right = image.at<Vec3b>(Point(x, y));;
				//Vec3b down = image.at<Vec3b>(Point(x, y-1));
				/*
				 if((down.val[0] == 160 && down.val[1] == 160 && down.val[2] == 160) &&
					 (right.val[0] == 160 && right.val[1] == 160 && right.val[2] == 160))
				{
					//std::cout<<"it found one"<<std::endl;
					image.at<Vec3b>(Point(x, y)).val[0] = 244;
					image.at<Vec3b>(Point(x, y)).val[1] = 244;
					image.at<Vec3b>(Point(x, y)).val[2] = 244;
				}//end of inner i*/
			}
			else
				continue;
		}//end of inner for loop
	}//end of outer for loop
	final_pic = image;
	void (*next)(int, void *)  = *(++fun_it);
	next(0,0);
}//end of removeColor method
