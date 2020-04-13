#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;

int main()
{
    Mat img1 = imread("image.jpg", IMREAD_GRAYSCALE);
    imshow("original", img1);

    Mat table(1, 256, CV_8U);

    uchar *p = table.ptr(); //행렬의 첫번째 원소의 주소를 얻는다
    for (int i = 0; i < 256; ++i)
    {
        if (i > 100 && i < 192)
            p[i] = 0;
        else
            p[i] = i;
    }

    Mat img2;
    LUT(img1, table, img2);

    imshow("New", img2);

    while (1)
    {
        int key = waitKey(100);
        if (key == 'q')
            break;
    }
    return 0;
}