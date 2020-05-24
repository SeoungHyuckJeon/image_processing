#include "opencv2/opencv.hpp"
using namespace cv;

void histogramStretching(Mat img, Mat &out)
{
    int lowvalue = 255, highvalue = 0;
    int i, j;
    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            if (lowvalue > img.at<uchar>(i, j))
                lowvalue = img.at<uchar>(i, j);
            if (highvalue < img.at<uchar>(i, j))
                highvalue = img.at<uchar>(i, j);
        }
    }
    // histogram stretching 계산
    float mult = 255 / (float)(highvalue - lowvalue);
    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
            out.at<uchar>(i, j) = (uchar)(img.at<uchar>(i, j) - lowvalue) * mult;
    }
}

int main()
{
    Mat img = imread("image.jpg", IMREAD_COLOR);
    Mat hsv, dst, array[3], strcharray[3];
    cvtColor(img, hsv, COLOR_BGR2HSV);

    split(hsv, array);

    strcharray[0] = array[0].clone(); //h
    strcharray[1] = array[1].clone(); //s
    strcharray[2] = array[2].clone(); //v

    //색상을 해치지 않기 위해 hsv에서 색상값은 스트레칭을 하지 않는다.
    // histogramStretching(array[0], strcharray[0]);
    histogramStretching(array[1], strcharray[1]);
    histogramStretching(array[2], strcharray[2]);

    merge(strcharray, 3, hsv);
    cvtColor(hsv, dst, COLOR_HSV2BGR);

    imshow("src", img);
    imshow("hsv", dst);

    while (1)
    {
        int key = waitKey();
        if (key == 'q')
            return 0;
    }
}