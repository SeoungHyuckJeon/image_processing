#include "opencv2/opencv.hpp"
using namespace cv;
#include <iostream>
using namespace std;

int main()
{
    int threshold_value = 127; //처음 추정치 T
    int lowsum = 0, highsum = 0, lowcount = 0, highcount = 0;
    int u1 = 0, u2 = 0;

    Mat src, dst;
    src = imread("image.jpg", IMREAD_GRAYSCALE);
    cout << "threshold value : " << threshold_value << endl;
    while (1)
    {
        for (int i = 0; i < src.rows; i++)
        {
            for (int j = 0; j < src.cols; j++)
            { //임계치를 기준으로 임계치보다 아래 화소면 low, 높으면 high로 구분
                if (src.at<uchar>(i, j) < threshold_value)
                {
                    lowsum += src.at<uchar>(i, j);
                    lowcount++;
                }
                else
                {
                    highsum += src.at<uchar>(i, j);
                    highcount++;
                }
            }
        }
        //평균 임계값 u1과 u2가 더이상 변하지 않으면 빠져나옴
        if (lowsum / lowcount == u1 && highsum / highcount == u2)
            break;
        else //그 외에는 새로운 임계값을 설정함
        {
            u1 = lowsum / lowcount;
            u2 = highsum / highcount;

            threshold_value = (u1 + u2) / 2.0f;
            cout << "threshold value : " << threshold_value << endl;

            lowsum = lowcount = highsum = highcount = 0;
        }
    }
    threshold(src, dst, threshold_value, 255, THRESH_BINARY);

    imshow("Original", src);
    imshow("Thresholding", dst);

    while (1)
    {
        int key = waitKey();
        if (key == 'q')
            return 0;
    }
}