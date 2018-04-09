//
// Created by mkarier on 11/27/17.
//

#include "Sobel.h"


void sobelEdgeDetection(int, void *)
{
    Mat grad_x, grad_y, grad;
    Mat abs_grad_x, abs_grad_y;
    Mat src;

    int ddepth = CV_16S;
    int scale = 1;
    int delta = 0;

    src = final_pic;
    //GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );

    /// Gradient X
    //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
    Sobel( src, grad_x, ddepth, 1, 0, CV_SCHARR, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_x, abs_grad_x );

    /// Gradient Y
    //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
    Sobel( src, grad_y, ddepth, 0, 1, CV_SCHARR, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_y, abs_grad_y );

    /// Total Gradient (approximate)
    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );

    final_pic = grad;
    void (*next)(int, void *)  = *(++fun_it);
    next(0,0);
}//end of sobelEdgeDetection