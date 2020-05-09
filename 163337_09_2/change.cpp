#include "opencv2/opencv.hpp"
using namespace cv;

int main()
{
    Mat src = imread("image.jpg");
    Mat size, trslation, rotate;

    //Resize
    resize(src, size, Size(), 0.5, 0.5);

    //Translation
    int tx = 100;
    int ty = 20;
    Mat tmat = (Mat_<double>(2, 3) << 1, 0, tx, 0, 1, ty);

    warpAffine(src, trslation, tmat, src.size());

    //Rotation
    Size dsize = Size(src.cols, src.rows);
    Point center = Point(src.cols / 2.0, src.rows / 2.0);
    Mat M = getRotationMatrix2D(center, 45, 1.0);

    warpAffine(src, rotate, M, dsize, INTER_LINEAR);

    imshow("Original", src);
    imshow("Resize", size);
    imshow("Translation", trslation);
    imshow("Rotation", rotate);

    while (1)
    {
        int key = waitKey(100);
        if (key == 'q')
            return 0;
    }
}