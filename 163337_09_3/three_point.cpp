#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;

int mx, my;
bool flag = false;
int count = 0;
Mat src, warp_dst = Mat::zeros(src.rows, src.cols, src.type());
Mat warp_mat(2, 3, CV_32FC1);
Point2f srcTri[3];
Point2f dstTri[3];

void onMouse(int event, int x, int y, int flags, void *param)
{
    if (event == EVENT_LBUTTONDOWN)
    {
        mx = x;
        my = y;
        flag = true;
    }
    else if (event == EVENT_LBUTTONUP)
    {
        if (flag == true)
        {
            switch (count)
            {
            case 0:
                srcTri[0] = Point2f(mx, my);
                break;
            case 1:
                srcTri[1] = Point2f(mx, my);
                break;
            case 2:
                srcTri[2] = Point2f(mx, my);
                break;
            case 3:
                dstTri[0] = Point2f(mx, my);
                break;
            case 4:
                dstTri[1] = Point2f(mx, my);
                break;
            case 5:
                dstTri[2] = Point2f(mx, my);
                warp_mat = getAffineTransform(srcTri, dstTri);
                warpAffine(src, warp_dst, warp_mat, warp_dst.size());
                imshow("3Point", warp_dst);
                break;
            }
            count++;
            flag = false;
        }
    }
}

int main()
{
    src = imread("image.jpg");
    imshow("Original", src);

    setMouseCallback("Original", onMouse);

    while (1)
    {
        int key = waitKey(100);
        if (key == 'q')
            return 0;
    }
}