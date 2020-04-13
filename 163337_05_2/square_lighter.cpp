#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;

Mat img, original;
int mx1, my1, mx2, my2;
bool cropping = false;

void brighten(Mat &img, int beta)
{
    cout << "brighten" << img.cols << " " << img.rows << endl;
    for (int r = 0; r < img.rows; r++)
    {
        for (int c = 0; c < img.cols; c++)
        {
            for (int a = 0; a < 3; a++)
            {
                img.at<Vec3b>(r, c)[a] = saturate_cast<uchar>(1 * (img.at<Vec3b>(r, c)[a] + beta));
            }
        }
    }
}

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
        img = original.clone();
        mx2 = x;
        my2 = y;
        cropping = false;
        try
        {
            Mat roi = img(Rect(mx1, my1, mx2 - mx1, my2 - my1));
            brighten(roi, 30);
        }
        catch (Exception &e)
        {
        }
        imshow("image", img);
    }
}

int main()
{
    img = imread("image.jpg");
    imshow("image", img);
    original = img.clone();

    setMouseCallback("image", onMouse);

    while (1)
    {
        int key = waitKey(100);
        if (key == 'q')
            break;
    }
    return 0;
}
