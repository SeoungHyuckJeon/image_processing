#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

void on_trackbar(int, void *) {}

int main()
{
    int aValue = 50;
    double alpha = (double)aValue / 100;
    double beta, input;
    Mat img1, img2, dst;

    img1 = imread("image.jpg");
    img2 = imread("offering.jpg");
    if (img1.empty() || img2.empty())
        return -1;

    beta = 1.0 - alpha;
    addWeighted(img1, alpha, img2, beta, 0.0, dst);

    imshow("Original 1", img1);
    imshow("Original 2", img2);
    imshow("Manipulation", dst);

    createTrackbar("Alpha", "Manipulation", &aValue, 100, on_trackbar);

    while (1)
    {
        alpha = (double)aValue / 100;
        beta = 1.0 - alpha;
        addWeighted(img1, alpha, img2, beta, 0.0, dst);
        imshow("Manipulation", dst);
        int key = waitKey(100);
        if (key == 'q')
            break;
    }
    return 0;
}