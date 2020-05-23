#include "opencv2/opencv.hpp"
using namespace cv;

int main()
{

    Mat img = imread("image.jpg", IMREAD_COLOR);
    if (img.empty())
    {
        return -1;
    }

    Mat imgHSV, imgThresholded, imgivtThresholded, dst, dstivt, inverted;

    cvtColor(img, imgHSV, COLOR_BGR2HSV);

    inRange(imgHSV, Scalar(10, 0, 0),
            Scalar(40, 255, 255), imgThresholded);
    inRange(imgHSV, Scalar(60, 130, 112),
            Scalar(180, 255, 255), imgivtThresholded);

    bitwise_not(imgivtThresholded, inverted);
    bitwise_and(img, img, dstivt, inverted);
    bitwise_and(img, img, dst, imgThresholded);

    imshow("Original", img);
    imshow("only face", dst);
    imshow("inverted inRange", dstivt);

    while (1)
    {
        int key = waitKey();
        if (key == 'q')
            return 0;
    }
}