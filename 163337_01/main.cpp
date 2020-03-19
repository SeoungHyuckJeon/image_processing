#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    cout << "Hello OpenCV " << CV_VERSION << endl;

    Mat img, dst;
    img = imread("JeonSeoungHyuck.jpg");

    if (img.empty())
    {
        cerr << "Image load failed!" << endl;
        return -1;
    }

    cout << "변환 전 이미지 크기 " << img.rows << " " << img.cols << endl;
    resize(img, dst, Size(384, 512));
    cout << "변환 후 이미지 크기 " << dst.rows << " " << dst.cols << endl;

    imshow("출력 영상", dst);
    waitKey(0);
    return 0;
}