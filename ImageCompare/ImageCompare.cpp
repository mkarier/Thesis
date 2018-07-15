#include "ImageCompare.h"
#include "ImageNode.h"


int main(int argc, char ** args)
{
    if(argc < 1)
    {
        cout << "no file was given" << endl;
        exit(0);
    }

    string path = args[1];//"../../../ImageDatabase/";
    string fileprefix = "scan1-";
    vector<ImageNode> list;
    int start = 1, end = 40;
    for(start; start <= end; start++)
    {
            string filename = fileprefix + to_string(start) + ".png";
            ImageNode node = ImageNode(path, filename);
            node.loadContours();
            //node.printImage();
            //cout << "Loaded file: " << filename << endl;
            list.push_back(node);
    }
    ImageNode tester = list[0];
    for(ImageNode current : list)
    {
        current.compareImage(tester.contours);
    }
    waitKey(0);
    destroyAllWindows();
    return 0;
}