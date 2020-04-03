#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
    Mat img = imread("image.jpg");
    if (img.empty())
    {
        return -1;
    }
    //red increase
    img = img + Scalar(0, 0, 255);
    //image print
    imshow("img", img);
    //image save
    imwrite("red_inc.jpg", img);
    waitKey(0);
    return 0;
}