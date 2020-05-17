#include "opencv2/opencv.hpp"
using namespace cv;

int main()
{
    VideoCapture cap("vd.mp4");
    Mat bg, frame, sub, binary, result;
    cap.read(bg);

    int threshold_value = 127;
    Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
    cvtColor(bg, bg, COLOR_BGR2GRAY);

    if (!cap.isOpened())
        return -1;

    while (1)
    {
        cap.read(frame);
        if (frame.empty())
        {
            break;
        }
        cvtColor(frame, frame, COLOR_BGR2GRAY);

        //배경 제거
        subtract(frame, bg, sub);
        //이진화
        threshold(sub, binary, threshold_value, 255, THRESH_BINARY);
        //형태학적 처리
        morphologyEx(binary, result, MORPH_GRADIENT, element);

        imshow("Video", result);
        if (waitKey(30) >= 0)
            break;
    }
    imshow("bg", bg);
    waitKey(0);
    return 0;
}