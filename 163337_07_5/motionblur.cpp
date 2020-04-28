#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
    Mat src = imread("image.jpg");
    if (src.empty())
        return -1;
    Mat dst;
    int size = 15;
    float weights[size][size] = {
        0,
    };

    for (int i = 0; i < size; i++) //mask 값 할당
    {
        weights[size / 2 - 1][i] = 1.0 / float(size);
        weights[0][i] = 0; //size가 크면 0행의 값들이 이상하게 들어가서 따로 초기화 함
    }

    Mat mask(size, size, CV_32F, weights);

    //Motion Blur
    filter2D(src, dst, -1, mask);

    imshow("motion blur", dst);

    while (1)
    {
        int key = waitKey(100);
        if (key == 'q')
            break;
    }

    return 0;
}