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
    Mat filter = Mat::ones(size, CV_32FC2);
    circle(filter, size / 2, 50, Vec2f(0, 0), -1);
    return filter;
}

Mat highfrequency(Mat src)
{
    Mat src_float;

    src.convertTo(src_float, CV_32FC1, 1.0 / 255.0);
    Mat dft_image;
    dft(src_float, dft_image, DFT_COMPLEX_OUTPUT);
    shuffleDFT(dft_image);

    Mat highpass = getFilter(dft_image.size());
    Mat result;

    multiply(dft_image, highpass, result);
    displayDFT(result);

    Mat inverted_image;
    shuffleDFT(result);
    idft(result, inverted_image, DFT_SCALE | DFT_REAL_OUTPUT);

    return inverted_image;
}

Mat sharpening(Mat src)
{
    Mat img;
    float weights[9] = {-1, -1, -1, -1, 9, -1, -1, -1, -1};
    Mat mask = Mat(3, 3, CV_32F, weights);
    filter2D(src, img, -1, mask, Point(-1, -1), 0, BORDER_DEFAULT);
    return img;
}

Mat binary(Mat src)
{
    Mat dst;
    int threshold_value = 0.1;
    threshold(src, dst, threshold_value, 255, THRESH_BINARY_INV);
    return dst;
}

int main()
{
    Mat src = imread("Q3.tif", IMREAD_GRAYSCALE);
    imshow("Original", src);

    //고역통과
    Mat inverted_image = highfrequency(src);
    imshow("invert", inverted_image);
    waitKey(0);

    //이진화
    Mat binary_image = binary(inverted_image);
    imshow("binary", binary_image);

    while (1)
    {
        int key = waitKey();
        if (key == 'q')
            return 0;
    }
}