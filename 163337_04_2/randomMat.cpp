#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;

int main()
{
    Mat img = imread("image.jpg");
    Mat R = Mat(427, 640, CV_8UC3);
    if (img.empty())
        return -1;

    randu(R, Scalar::all(-50), Scalar::all(50));

    imshow("original", img);
    img = img + R;
    imshow("after", img);

    waitKey(0);
    return 0;
}