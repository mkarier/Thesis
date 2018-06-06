//============================================================================
// Name        : EdgeDetection.cpp
// Author      : Marco Karier
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <regex>
#include "OpenCVLibrary.h"
#include "HighContrast.h"
#include "ColorReduce.h"
#include "Wavelet.h"
#include "ArrayBuffer.h"
#include "Otsu.h"
#include "Sobel.h"
#include "Ratio.h"
#include "ImageNode.h"

vector<void (*)(int, void *)>methods =  {
                                            /*addFrame,
                                            //gaussianBlur,
                                            gaussianBlur,
											sobelEdgeDetection,
											regularThreshold,//*/
                                            // highContrast,
                                             //colorReduce,
                                             //dhwt2d,
                                            // sobelEdgeDetection,
                                            // CannyThreshold,
                                            // regularBlur,
                                             //gaussianBlur,
					    // houghTransform,
                                             //regularBlur,
                                             //fill,
                                             //CannyThreshold,
                                             //regularBlur,
                                             
                                             //otsuThreshold,
                                   
                                             //sobelEdgeDetection,

                                             showFinal
                                         };

vector<void  (*)(int, void *)>::iterator fun_it;
int read_in_style = CV_LOAD_IMAGE_GRAYSCALE;
int threshold_value = 0;
int threshold_type = 0;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;
int alpha = 10;
int beta = 0;
int thickness = 1;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int c_ratio = 3;
int kernel_size = 3;
int frame_left = 0, frame_right = 0, frame_top = 0, frame_bottom = 0;


//for otsu
int otsu_total = 0;
Ratio ratio_array[max_value + 1];
string final_name = "final picture";
Mat input, src_gray, hc_src, final_pic, current_final;
string ctrl = "controlWindow", path = "../../ImageDatabase/";
vector<ImageNode> dataBase;

vector<string> split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

vector<ImageNode> LoadDataBase(string path, int end)
{
    ////TODO: I will have to have scan2- someting in the future and right now it can't handle that.
    string fileprefix = "scan1-";
    vector<ImageNode> list;
    int start = 1;
    for(start; start <= end; start++)
    {
        string filename = fileprefix + to_string(start)+".png";
        ImageNode node = ImageNode(path, filename);
        node.loadContours();
        //node.printImage();
        //cout << "Loaded file: " << filename << endl;
        list.push_back(node);
    }

    return list;
}

void printDatabase()
{
    int debug_index = 0;
    for(ImageNode temp : dataBase)
    {
        temp.printImage();
        cout << "printed index " << debug_index++ << endl;
    }
}
void callImageCompare(Mat pic)
{
    //TODO: make this method call image compare to add the processed pic to the data base
    //vector<ImageNode> dataBase = LoadDataBase(path, 1);

    vector<vector<Point>> tempContours;
    vector<Vec4i> tempHierarchy;
    Mat gray_scale = getGrayscale(current_final);
    findContours(gray_scale, tempContours, tempHierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    for(ImageNode node : dataBase)
    {
        node.compareImage(tempContours);
    }
}

void callFindDiscreteName(Mat pic)
{
    //TODO: make this method get find the discrete set of an image
    //cout << "this method is to find discrete set of names but it doesn't yet" << endl;
    string name = processImage(current_final);
    //cout << name << endl;
}

void callPrintIndividualContour(Mat pic)
{
    printIndividualContours(current_final);
}

bool checkInput(regex reg, string input)
{
    //TODO: make this work
}

void callPrintGroup()
{
    cout << "please enter contours you want to out put comma delimited. There is no error checking" << endl;
    string input;
    cin >> input;
    cout << "input: " << input << endl;
    vector<string> list = split(input, ',');
    vector<int> windows;
    for(string index : list)
    {
        stringstream temp(index);
        int value;
        temp >> value;
        windows.push_back(value);
    }
    printGroups(windows, current_final);
}
void callSearchContours(Mat pic)
{
    ///TODO: ask for user input about the specific contours to look for then search for contours
    cout << "please enter contours you want to out put comma delimited. There is no error checking" << endl;
    string input;
    cin >> input;
    cout << "input: " << input << endl;
    vector<string> list = split(input, ',');
    vector<int> indexContours;
    cout<<"creating a list of index of contours " << endl;
    for(string index : list)
    {
        stringstream temp(index);
        int value;
        temp >> value;
        indexContours.push_back(value);
    }//end of for loop to use user input
    vector<vector<Point>> tempContours;
    vector<Vec4i> tempHierarchy;
    Mat gray_scale = getGrayscale(current_final);
    findContours(gray_scale, tempContours, tempHierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    vector<vector<Point>> mainContours;
    cout << "adding contours to a list" << endl;
    for(int index = 0; index < indexContours.size(); index++)
    {
        mainContours.push_back(tempContours[indexContours[index]]);
    }//end of for loop add index to list
    cout << "searching the \"datatbase\" for input contours" << endl;
    for(ImageNode node : dataBase)
    {
        node.compareImage(mainContours);
    }//end of for loop for database
	//cout << "End of Search" << endl;
}//end of callSearchContours

int main(int argc, char * argv[]) {
    namedWindow(ctrl, CV_WINDOW_NORMAL);
    namedWindow(final_name, CV_WINDOW_NORMAL);
    input = imread(argv[1], read_in_style);
    Mat original = imread(argv[1], read_in_style);
	int numFiles = 0;
    if (input.empty()) {
        std::cout << "!!! Failed imread()" << std::endl;
        string path_to_file = "/home/mkarier/Dropbox/Thesis/basicImages/scan1-6.jpg";
        input = imread(path_to_file, read_in_style);
        original = imread(path_to_file, read_in_style);
        if (input.empty()) {
            cout << "Still couldn't find the file" << endl;
            return -1;
        }
    }
    if(argc = 4)
    {
        path = argv[2];
		stringstream str(argv[3]);
		str >> numFiles;
    }
    dataBase = LoadDataBase(path, numFiles);
    void (*contrastMethod)(int, void *) = highContrast;
    vector<void (*)(int, void *)>::iterator searchResults;
    searchResults = find(methods.begin(), methods.end(), contrastMethod);
    if (searchResults != methods.end()) {
        ///create a Trackbar for high contrast
        createTrackbar("alpha", ctrl, &alpha, 30, methods[0]);
        createTrackbar("beta", ctrl, &beta, 100, methods[0]);
    }

    searchResults = find(methods.begin(), methods.end(), addFrame);
    if (searchResults != methods.end()) {

        ///Create a Trackbar to create edges around the imgage addFrame.
        int maxRows = input.rows * input.channels();
        int maxCols = input.cols * input.channels();
        createTrackbar("Frame_Left", ctrl, &frame_left, maxRows, methods[0]);
        createTrackbar("Frame_Right", ctrl, &frame_right, maxRows, methods[0]);
        createTrackbar("Frame_Top", ctrl, &frame_top, maxCols, methods[0]);
        createTrackbar("Frame_Bottom", ctrl, &frame_bottom, maxCols, methods[0]);
    }

    searchResults = find(methods.begin(), methods.end(), CannyThreshold);
    if (searchResults != methods.end())
    {
        ///Create a Trackbar for user to enter threshold
        createTrackbar("Canny Min Threshold:", ctrl, &lowThreshold, max_lowThreshold, methods[0]);
    }
    searchResults = find(methods.begin(), methods.end(), regularThreshold);

    if(searchResults != methods.end())
    {
        ///create a track bar for Threshold
        createTrackbar("regular Threshold value", ctrl, &threshold_value, max_value, methods[0]);
        createTrackbar("threshold style", ctrl, &threshold_type, max_type, methods[0]);
    }//end of if regular threshold

    ///creat a track bar for thickness of contour. No way to decect whether it is needed or not so comment this out if unneeded. I picked 20 out of random usually I use 8
    createTrackbar("thickness", ctrl, &thickness, 20, methods[0]);
    ///this is to create buttons for functions
    createButton("Print Database", reinterpret_cast<ButtonCallback>(printDatabase), nullptr, CV_PUSH_BUTTON);
    createButton("Search All Contours In ImageForDatabase", reinterpret_cast<ButtonCallback>(callImageCompare), &final_pic, CV_PUSH_BUTTON, 0);
    createButton("PrintImageOneWindow:NotOriginalPurpose", reinterpret_cast<ButtonCallback>(callFindDiscreteName), &final_pic, CV_PUSH_BUTTON, 0);
    createButton("Print individual Contours", reinterpret_cast<ButtonCallback>(callPrintIndividualContour), &final_pic, CV_PUSH_BUTTON);
    createButton("Print Certain contours", reinterpret_cast<ButtonCallback>(callPrintGroup), nullptr, CV_PUSH_BUTTON);
    createButton("Search Contours", reinterpret_cast<ButtonCallback>(callSearchContours), nullptr, CV_PUSH_BUTTON);
    //buffArray(input);
    input.copyTo(final_pic);
    fun_it = methods.begin();
    methods[0](0,0);

    ///Uncomment this so for the script
        callImageCompare(final_pic);
		//callSearchContours(final_pic);
        destroyAllWindows();
        return 0;//*/


    imshow(ctrl, original);
    //imwrite("output.jpg", input);
    waitKey(0);
    destroyAllWindows();

	return 0;
}//end of main


