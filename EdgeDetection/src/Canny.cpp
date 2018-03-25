//
// Created by marco on 11/7/17.
//

#include "Canny.h"


void CannyThreshold(int, void*)
{
    cout << "in Canny" << endl;
    if(checkIfGrayScale(final_pic))
    {
        cout << "converting \n";
        cvtColor(final_pic, src_gray, CV_BGR2GRAY);
    }
    else
        src_gray = final_pic;

    Mat c_dst, c_input, detected_edges;
    /// Reduce noise with a kernel 3x3
    blur( src_gray, detected_edges, Size(3,3) );

    /// Canny detector
    Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*c_ratio, kernel_size );

    /// Using Canny's output as a mask, we display our result
    c_dst = Scalar::all(0);

    src_gray.copyTo( c_dst, detected_edges);
    //cvtColor(c_dst, final_pic, CV_GRAY2BGR);
    final_pic = c_dst;
    void (*next)(int, void *)  = *(++fun_it);
    next(0,0);

}