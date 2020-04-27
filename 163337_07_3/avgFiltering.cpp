#include "opencv2/opencv.hpp"
using namespace cv;

int main()
{
    Mat src = imread("image.jpg", IMREAD_GRAYSCALE);
    if (src.empty())
        return -1;
    Mat avg_3, avg_5, avg_333;

    blur(src, avg_3, Size(3, 3));
    blur(src, avg_5, Size(5, 5));
    blur(src, avg_333, Size(3, 3));
    blur(avg_333, avg_333, Size(3, 3));
    blur(avg_333, avg_333, Size(3, 3));
    blur(avg_333, avg_333, Size(3, 3));
    blur(avg_333, avg_333, Size(3, 3));

    imshow("3x3 평균값 필터링 적용", avg_3);
    imshow("5x5 평균값 필터링 적용", avg_5);
    imshow("3x3 평균값 필터링 5번 적용", avg_333);

    while (1)
    {
        int key = waitKey(100);
        if (key == 'q')
            break;
    }

    return 0;
}