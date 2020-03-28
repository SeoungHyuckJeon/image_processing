#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;

void onMouse(int event, int x, int y, int flags, void *param)
{
    if (event == EVENT_LBUTTONDOWN)
    {
        Mat &img = *(Mat *)(param);
        rectangle(img, Point(x, y), Point(x + 300, y + 200), Scalar(0, 0, 255), 10);
        imshow("Image", img);
    }
    else if (event == EVENT_RBUTTONDOWN)
    {
        Mat &img = *(Mat *)(param);
        circle(img, Point(x, y), 200, Scalar(255, 0, 0), 10);
        imshow("Image", img);
    }
    else if (event == EVENT_MBUTTONDOWN)
    {
    }
    else if (event == EVENT_MOUSEMOVE)
    {
    }
}

int main()
{
    Mat image = Mat(600, 800, CV_8UC3, Scalar(255, 255, 255));
    imshow("Image", image);

    setMouseCallback("Image", onMouse, &image);
    waitKey(0);
    return (0);
}