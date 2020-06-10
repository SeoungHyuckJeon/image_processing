#include "opencv2/opencv.hpp"
using namespace cv;

int histSize[1];
float hranges[2];
const float *ranges[1];
int channels[1];

MatND getHistogram(const Mat &image)
{
    histSize[0] = 256;
    hranges[0] = 0.0;   //히스토그램 최소 값
    hranges[1] = 255.0; //히스토그램 최대 값
    ranges[0] = hranges;
    channels[0] = 0;
    MatND hist;
    calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);

    return hist;
}

Mat getHistogramImage(const Mat &image)
{
    histSize[0] = 256;
    hranges[0] = 0.0;
    hranges[1] = 255.0;
    ranges[0] = hranges;
    channels[0] = 0;

    MatND hist = getHistogram(image); // 히스토그램 계산
    double maxVal = 0;                // 최대 빈도수
    double minVal = 0;                // 최소 빈도수

    minMaxLoc(hist, &minVal, &maxVal, 0, 0);
    Mat histImg(histSize[0], histSize[0], CV_8U, Scalar(255));
    int hpt = static_cast<int>(0.9 * histSize[0]);

    //그래프 그리기
    for (int h = 0; h < histSize[0]; h++)
    {
        float binVal = hist.at<float>(h);
        int intensity = static_cast<int>(binVal * hpt / maxVal);
        line(histImg, Point(h, histSize[0]), Point(h, histSize[0] - intensity), Scalar::all(0));
    }
    return histImg;
}

int main()
{
    Mat src = imread("image.jpg", IMREAD_GRAYSCALE);
    imshow("Original", src);
    //원본 히스토그램
    MatND histo = getHistogram(src);
    imshow("Histogram", getHistogramImage(src));

    waitKey(0);
}
