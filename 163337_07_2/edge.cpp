#include "opencv2/opencv.hpp"
using namespace cv;

int main()
{
    Mat src = imread("image.jpg", IMREAD_GRAYSCALE);
    if (src.empty())
        return -1;
    Mat avgf;
    int scale = 1;
    int delta = 0;
    Mat src_x, src_y, abs_src_x, abs_src_y;
    Mat avgf_x, avgf_y, abs_avgf_x, abs_avgf_y;

    blur(src, avgf, Size(3, 3));

    Sobel(src, src_x, CV_16S, 1, 0, 3, scale, delta, BORDER_DEFAULT);
    Sobel(src, src_y, CV_16S, 1, 0, 3, scale, delta, BORDER_DEFAULT);
    Sobel(avgf, avgf_x, CV_16S, 1, 0, 3, scale, delta, BORDER_DEFAULT);
    Sobel(avgf, avgf_y, CV_16S, 1, 0, 3, scale, delta, BORDER_DEFAULT);

    convertScaleAbs(src_x, abs_src_x);
    convertScaleAbs(src_y, abs_src_y);
    convertScaleAbs(avgf_x, abs_avgf_x);
    convertScaleAbs(avgf_y, abs_avgf_y);
    addWeighted(abs_src_x, 0.5, abs_src_y, 0.5, 0, src);
    addWeighted(abs_avgf_x, 0.5, abs_avgf_y, 0.5, 0, avgf);

    imshow("평균값 필터링 적용", avgf);
    imshow("평균값 필터링 미적용", src);

    while (1)
    {
        int key = waitKey(100);
        if (key == 'q')
            break;
    }

    return 0;
}