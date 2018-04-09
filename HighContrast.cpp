//
// Created by mkarier on 11/5/17.
//

#include "HighContrast.h"

void highContrast(double s_alpha, int s_beta, Mat& src)
{
    for(int x = 0; x < src.rows; x++)
    {
        for(int y = 0; y < src.cols; y++)
        {
            for(int c = 0; c < 3; c++)
            {
                src.at<Vec3b>(x,y)[c] = (s_alpha * (hc_src.at<Vec3b>(x,y)[c]) + s_beta);
            }
        }
    }//end of outer for loop
}

void highContrast(int, void *)
{
    cout << "in highContrast" << endl;

    double d_alpha = (double)alpha/10.0;
    if(d_alpha < 1.0)
    {
        d_alpha = 1.0;
    }
    if(!checkIfGrayScale(final_pic))
    {
        cout << "converting pic \n";
        cvtColor(final_pic, hc_src, CV_GRAY2BGR);
    }
    else
        hc_src = final_pic;
    for(int x = 0; x < hc_src.rows; x++)
    {
        for(int y = 0; y < hc_src.cols; y++)
        {
            for(int c = 0; c < 3; c++)
            {
                hc_src.at<Vec3b>(x,y)[c] = (d_alpha * (hc_src.at<Vec3b>(x,y)[c]) + beta);
            }
        }
    }//end of outer for loop
    //cvtColor(hc_src, src_gray, COLOR_RGB2GRAY);
    final_pic = hc_src;
    void (*next)(int, void *)  = *(++fun_it);
    next(0,0);
}//end of highContrast

