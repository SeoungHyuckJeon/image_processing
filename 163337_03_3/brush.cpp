#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

Mat img = Mat(400, 800, CV_8UC3, Scalar(255, 255, 255));
int drawing = false;
int thickness;

void on_trackbar(int, void *) {}

void drawCircle(int event, int x, int y, int, void *param)
{
    if (event == EVENT_LBUTTONDOWN)
        drawing = true;
    else if (event == EVENT_MOUSEMOVE)
    {
        if (drawing == true)
            circle(img, Point(x, y), 3, Scalar(0, 0, 255), thickness);
    }
    else if (event == EVENT_LBUTTONUP)
        drawing = false;
    imshow("Image", img);
}

int main()
{
    namedWindow("Image", 1);
    imshow("Image", img);

    setMouseCallback("Image", drawCircle);
    createTrackbar("Thickness", "Image", &thickness, 20, on_trackbar);

    waitKey(0);
    return 0;
}