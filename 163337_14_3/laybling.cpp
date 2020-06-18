#include "opencv2/opencv.hpp"
using namespace cv;

int main()
{
    int tv_1 = 193; //세포, 배경 임계값
    int tv_2 = 243; //세포핵 임계값

    Mat src, cell, nucleus, bg, dst;
    src = imread("Fig1.tif", IMREAD_GRAYSCALE);

    //히스토그램 평활화 사용
    equalizeHist(src, src);
    //세포, 세포핵, 배경 분할
    threshold(src, cell, tv_1, 255, THRESH_BINARY);
    threshold(src, nucleus, tv_2, 255, THRESH_BINARY);
    threshold(src, bg, tv_1, 255, THRESH_BINARY_INV);
    //분할한 영역에 색입히기
    cvtColor(cell, cell, COLOR_GRAY2BGR);
    cvtColor(nucleus, nucleus, COLOR_GRAY2BGR);
    cvtColor(bg, bg, COLOR_GRAY2BGR);

    cell -= Scalar(20, 40, 125);
    bg -= Scalar(50, 0, 0);
    nucleus -= Scalar(0, 50, 0);
    //합성
    dst = bg.clone();
    bitwise_or(dst, cell, dst);
    bitwise_or(dst, nucleus, dst);

    imshow("Original", src);
    imshow("cell", cell);
    imshow("nucleus", nucleus);
    imshow("background", bg);
    imshow("dst", dst);

    while (1)
    {
        int key = waitKey(100);
        if (key == 'q')
            return 0;
    }
}