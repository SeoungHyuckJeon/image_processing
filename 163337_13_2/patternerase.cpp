#include "opencv2/opencv.hpp"
using namespace cv;

void shuffleDFT(Mat &src)
{
    int cX = src.cols / 2;
    int cY = src.rows / 2;

    Mat q1(src, Rect(0, 0, cX, cY));
    Mat q2(src, Rect(cX, 0, cX, cY));
    Mat q3(src, Rect(0, cY, cX, cY));
    Mat q4(src, Rect(cX, cY, cX, cY));

    Mat tmp;
    q1.copyTo(tmp);
    q4.copyTo(q1);
    tmp.copyTo(q4);
    q2.copyTo(tmp);
    q3.copyTo(q2);
    tmp.copyTo(q3);
}

void displayDFT(Mat &src)
{
    Mat image_array[2] = {Mat::zeros(src.size(), CV_32F), Mat::zeros(src.size(), CV_32F)};
    //DFT 결과 영상을 분할함
    split(src, image_array);
    Mat mag_image;
    //푸리에 변환 계수들의 절대값을 계산
    magnitude(image_array[0], image_array[1], mag_image);
    //푸리에 변환 계수들을 로그 스케일로 변환하고, 0값이 나오지 않도록 1을 더해줌
    mag_image += Scalar::all(1);
    log(mag_image, mag_image);
    //정규화
    normalize(mag_image, mag_image, 0, 1, NORM_MINMAX);
    imshow("DFT", mag_image);
}

Mat getFilter(Size size)
{
    Mat tmp = Mat(size, CV_32F);

    for (int i = 0; i < tmp.rows; i++)
    {
        for (int j = 0; j < tmp.cols; j++)
        {
            if (j > (tmp.cols / 2 - 10) && j < (tmp.cols / 2 + 10) && i > (tmp.rows / 2 + 10))
                tmp.at<float>(i, j) = 0;
            else if (j > (tmp.cols / 2 - 10) && j < (tmp.cols / 2 + 10) && i < (tmp.rows / 2 - 10))
                tmp.at<float>(i, j) = 0;
            else
                tmp.at<float>(i, j) = 1;
        }
    }

    Mat toMerge[] = {tmp, tmp};
    Mat filter;
    merge(toMerge, 2, filter);

    return filter;
}

Mat getFilter2(Size size)
{
    Mat tmp = Mat(size, CV_32F);

    for (int i = 0; i < tmp.rows; i++)
    {
        for (int j = 0; j < tmp.cols; j++)
        {
            if (j > (tmp.cols / 2 - 10) && j < (tmp.cols / 2 + 10) && i > (tmp.rows / 2 + 10))
                tmp.at<float>(i, j) = 1;
            else if (j > (tmp.cols / 2 - 10) && j < (tmp.cols / 2 + 10) && i < (tmp.rows / 2 - 10))
                tmp.at<float>(i, j) = 1;
            else
                tmp.at<float>(i, j) = 0;
        }
    }

    Mat toMerge[] = {tmp, tmp};
    Mat filter;
    merge(toMerge, 2, filter);

    return filter;
}

void patternErase(Mat src)
{
    Mat src_float, dft_image;

    //실수 영상으로 변환
    src.convertTo(src_float, CV_32FC1, 1.0 / 255.0);
    dft(src_float, dft_image, DFT_COMPLEX_OUTPUT);
    shuffleDFT(dft_image);
    displayDFT(dft_image);

    Mat lowpass = getFilter(dft_image.size());
    Mat result;

    multiply(dft_image, lowpass, result);
    displayDFT(result);

    Mat inverted_image;

    shuffleDFT(result);
    idft(result, inverted_image, DFT_SCALE | DFT_REAL_OUTPUT);
    imshow("inverted", inverted_image);
}

void patternErase2(Mat src)
{
    Mat src_float, dft_image;

    //실수 영상으로 변환
    src.convertTo(src_float, CV_32FC1, 1.0 / 255.0);
    dft(src_float, dft_image, DFT_COMPLEX_OUTPUT);
    shuffleDFT(dft_image);
    displayDFT(dft_image);

    Mat lowpass = getFilter2(dft_image.size());
    Mat result;

    multiply(dft_image, lowpass, result);
    displayDFT(result);

    Mat inverted_image;

    shuffleDFT(result);
    idft(result, inverted_image, DFT_SCALE | DFT_REAL_OUTPUT);
    imshow("inverted", inverted_image);
}

int main()
{
    Mat src = imread("Q2.tif", IMREAD_GRAYSCALE);
    imshow("Original", src);

    patternErase(src);
    patternErase2(src);

    while (1)
    {
        int key = waitKey();
        if (key == 'q')
            return 0;
    }
}