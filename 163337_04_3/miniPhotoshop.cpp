#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;

Mat img, roi, original; //원본을 저장할 original Mat 변수 선언
int mx1, my1, mx2, my2;
bool cropping = false; //사각형 선택 중임을 나타내는 플래그 변수

void onMouse(int event, int x, int y, int flags, void *param)
{
    if (event == EVENT_LBUTTONDOWN)
    {
        mx1 = x;
        my1 = y;
        cropping = true;
    }
    else if (event == EVENT_LBUTTONUP)
    {
        img = original.clone(); //드래그를 다시하면 앞전에 드래그했던 걸 없애고 다시 그림
        mx2 = x;
        my2 = y;
        cropping = false;
        rectangle(img, Rect(mx1, my1, mx2 - mx1, my2 - my1), Scalar(0, 255, 0), 2);
        imshow("image", img);
    }
}

int main()
{
    img = imread("image.jpg");
    imshow("image", img);
    Mat clone = img.clone();
    original = img.clone();

    setMouseCallback("image", onMouse);

    while (1)
    {
        int key = waitKey(100);
        if (key == 'q')
            break;
        else if (key == 'c') //드래그한 부분 저장
        {
            roi = clone(Rect(mx1, my1, mx2 - mx1, my2 - my1));
            imwrite("result.jpg", roi);
        }
    }
}