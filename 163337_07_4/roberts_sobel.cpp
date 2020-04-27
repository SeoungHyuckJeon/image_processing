#include "opencv2/opencv.hpp"
using namespace cv;

int main()
{
    Mat src = imread("image1.jpeg", IMREAD_GRAYSCALE);
    Mat rb, sb;
    src.copyTo(rb);
    src.copyTo(sb);
    if (src.empty() || rb.empty() || sb.empty())
        return -1;

    float weights_x[] = {
        0, 0, -1,
        0, 1, 0,
        0, 0, 0};
    float weights_y[] = {
        -1, 0, 0,
        0, 1, 0,
        0, 0, 0};
    int scale = 1, delta = 0;

    Mat rb_x, rb_y, abs_rb_x, abs_rb_y;
    Mat sb_x, sb_y, abs_sb_x, abs_sb_y;
    Mat mask_x(3, 3, CV_16S, weights_x);
    Mat mask_y(3, 3, CV_16S, weights_y);

    //Roberts Edge Detection
    filter2D(src, rb_x, CV_16S, mask_x);
    filter2D(src, rb_y, CV_16S, mask_y);
    addWeighted(rb_x, 0.5, rb_y, 0.5, 0, rb);

    //Sobel Edge Detection
    Sobel(src, sb_x, CV_16S, 1, 0, 3, scale, delta, BORDER_DEFAULT);
    Sobel(src, sb_y, CV_16S, 0, 1, 3, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(sb_x, abs_sb_x);
    convertScaleAbs(sb_y, abs_sb_y);
    addWeighted(abs_sb_x, 0.5, abs_sb_y, 0.5, 0, sb);

    imshow("original", src);
    imshow("Roberts", rb);
    imshow("Sobel", sb);

    while (1)
    {
        int key = waitKey(100);
        if (key == 'q')
            break;
    }

    return 0;
}