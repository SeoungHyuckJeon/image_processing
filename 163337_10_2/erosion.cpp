#include "opencv2/opencv.hpp"
using namespace cv;

int main()
{
        Mat src, dst, erosion3, erosion5;
        src = imread("image.jpg", IMREAD_GRAYSCALE);

        threshold(src, dst, 127, 255, THRESH_BINARY);
        imshow("dst", dst);

        Mat element3 = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
        Mat element5 = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));

        erode(dst, erosion3, element3);
        imshow("3x3 Erosion", erosion3);

        erode(dst, erosion5, element5);
        imshow("5x5 Erosion", erosion5);

        while (1)
        {
                int key = waitKey(100);
                if (key == 'q')
                        return 0;
        }
}