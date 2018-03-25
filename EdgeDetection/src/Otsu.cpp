//
// Created by mkarier on 11/17/17.
//

#include <iomanip>
#include "Otsu.h"


void regularThreshold(int, void *)
{
    if (!checkIfGrayScale(final_pic))
    {
        cout << "converting pic\n";
        cvtColor(final_pic, src_gray, CV_BGR2GRAY);
    }
    else
        src_gray = final_pic;
    threshold( src_gray, final_pic, threshold_value, max_BINARY_value,threshold_type );

    void (*next)(int, void *)  = *(++fun_it);
    next(0,0);

}

void otsuThreshold(int, void *)
{
    if (!checkIfGrayScale(final_pic))
    {
        cout << "converting pic\n";
        cvtColor(final_pic, src_gray, CV_BGR2GRAY);
    }
    else
        src_gray = final_pic;
    cout << "in otsu"<< endl;
    createRatioArray();
    findRatioArray();
    thread workers[max_value+1];
    float values[max_value+1];
    ///threading
    for(int i = 0; i <= max_value; i++)
        workers[i] = thread(findClassVariance, i, &values[i]);
    for(int i = 0; i <= max_value; i++)
        workers[i].join();

    int bestThreshold = 0;
    float lowestVariance = FLT_MAX;
    for(int i = 0; i <= max_value; i++)
    {
        if(lowestVariance > values[i])
        {
            bestThreshold = i;
            lowestVariance = values[i];
        }
    }
    cout << "best threshold = " << bestThreshold << endl;
    cout << "lowestVariance " << lowestVariance << endl << endl;
    applyThreshold(bestThreshold);
    final_pic = src_gray;
    void (*next)(int, void *)  = *(++fun_it);
    next(0,0);
}

void applyThreshold(int threshold)
{
    for (int x = 0; x < src_gray.rows; x++)
    {
        for (int y = 0; y < src_gray.cols; y++)
        {

            if(src_gray.at<uchar>(x,y) < threshold)
                src_gray.at<uchar>(x,y) = 0;
            else
                src_gray.at<uchar>(x,y) = 255;
        }//inner
    }//outer for loop
}

void findClassVariance(int threshold, float * spot)
{
    float wB, meanB, varianceB;
    float wF, meanF, varianceF;
    int numForeground = (max_value - threshold) + 1;
    int numBackground = threshold +1;
    Ratio background[numBackground];
    Ratio foreground[numForeground];
    int b_counter = 0, f_counter = 0;
    for(int i = 0; i <= max_value; i++)
    {
        if(ratio_array[i].pixel_value <= threshold)
        {
            background[b_counter++] = ratio_array[i];
        } //end of if
        else
        {
         foreground[f_counter++] = ratio_array[i];
        }//end of else
    }//end of for loop
    wB = findWeight(background, numBackground);
    wF = findWeight(foreground, numForeground);
    meanB = findMean(background, numBackground);
    meanF = findMean(foreground, numForeground);
    varianceB = findVariance(background, numBackground, meanB);
    varianceF = findVariance(foreground, numForeground, meanF);

    *spot = (wB * varianceB) + (wF * varianceF);
}//end of findClassVariance

float findVariance(Ratio * array, int size, float mean)
{
    float numerator = 0.0, denominator = 0.0;
    for(int i = 0; i < size; i++)
        denominator += (float)array[i].count;
    for(int i = 0; i < size; i++)
    {
        numerator += pow((array[i].pixel_value - mean), (float)2) * (float)array[i].count;
    }

    return (float)numerator/(float)denominator;

}

float findMean(Ratio * array, int size)
{
    int denominator  = 0;
    int numerator = 0;
    for(int i = 0; i < size; i++)
        denominator += array[i].count;
    for(int i = 0; i < size; i++)
        numerator += (array[i].pixel_value * array[i].count);
    if(numerator == 0 or denominator == 0)
        return 0.0;
    else
        return (float)numerator/(float)denominator;
}

float findWeight(Ratio * array, int size)
{
    int numerator = 0;
    for(int i = 0; i < size; i++)
    {
        numerator += array[i].count;
    }//end of for loop
    if(numerator == 0)
        return 0.0;
    else
        return (float)numerator/(float)otsu_total;
}

void createRatioArray()
{

    for(int i = 0; i <= max_value; i++)
    {
        ratio_array[i].pixel_value = i;
        ratio_array[i].count = 0;

    }
}

void findRatioArray() {
    for (int x = 0; x < src_gray.rows; x++) {
        for (int y = 0; y < src_gray.cols; y++) {
            ratio_array[src_gray.at<uchar>(x, y)].count++;
        }//inner
    }//outer for loop
    otsu_total = 0;
    //for debug
    for (int x = 0; x <= max_value; x++)
    {
        //std::cout << ratio_array[x].pixel_value << " " << ratio_array[x].count << std::endl;
        otsu_total+= ratio_array[x].count;
    }//outer for loop
}//end of findRatioArray
