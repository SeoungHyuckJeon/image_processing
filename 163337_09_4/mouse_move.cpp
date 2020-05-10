#include "opencv2/opencv.hpp"
using namespace cv;

int mx, my, tx, ty;
bool flag = false;
Mat src, tmat, dst;

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
            tx = x;
            ty = y;
            tmat = (Mat_<double>(2, 3) << 1, 0, tx - mx, 0, 1, ty - my);
            warpAffine(src, src, tmat, src.size());
            imshow("Original", src);
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