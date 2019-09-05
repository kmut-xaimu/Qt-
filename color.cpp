#include<opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <iostream>
using namespace cv;
using namespace std;
void on_low_r_thresh_trackbar(int, void*);
void on_high_r_thresh_trackbar(int, void*);
void on_low_g_thresh_trackbar(int, void*);
void on_high_g_thresh_trackbar(int, void*);
void on_low_b_thresh_trackbar(int, void*);
void on_high_b_thresh_trackbar(int, void*);
int low_r = 105, low_g = 25, low_b = 25;
int high_r = 255, high_g = 61, high_b = 109;


int color()
{
    VideoCapture capture;
    capture.open(0);
    if (!capture.isOpened())
    {
        printf("can not open video file   \n");
        return -1;
    }
    Mat frame, dst;
    Mat kernel;
    //开操作处理
    kernel = getStructuringElement(MORPH_RECT, Size(5, 5));

    namedWindow("input", CV_WINDOW_AUTOSIZE);
    namedWindow("output", CV_WINDOW_AUTOSIZE);

    namedWindow("Object Detection", WINDOW_NORMAL);
    //-- Trackbars to set thresholds for RGB values
    createTrackbar("Low R", "Object Detection", &low_r, 255, on_low_r_thresh_trackbar);
    createTrackbar("High R", "Object Detection", &high_r, 255, on_high_r_thresh_trackbar);
    createTrackbar("Low G", "Object Detection", &low_g, 255, on_low_g_thresh_trackbar);
    createTrackbar("High G", "Object Detection", &high_g, 255, on_high_g_thresh_trackbar);
    createTrackbar("Low B", "Object Detection", &low_b, 255, on_low_b_thresh_trackbar);
    createTrackbar("High B", "Object Detection", &high_b, 255, on_high_b_thresh_trackbar);



    std::vector<std::vector<Point>> contours;
    std::vector<Vec4i> hireachy;
    Rect rect;
    Point2f center;
    float radius = 20;

    while (capture.read(frame))
    {
        //blur(frame, dst, Size(5,5));
        inRange(frame, Scalar(low_b, low_g, low_r), Scalar(high_b, high_g, high_r), dst);
        //开操作
        morphologyEx(dst, dst, MORPH_OPEN, kernel);
        //获取边界
        findContours(dst, contours, hireachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
        //框选面积最大的边界
        if (contours.size() > 0)
        {
            double maxArea = 0;
            for (int i = 0; i < contours.size(); i++)
            {
                double area = contourArea(contours[static_cast<int>(i)]);
                if (area > maxArea)
                {
                    maxArea = area;
                    rect = boundingRect(contours[static_cast<int>(i)]);
                    minEnclosingCircle(contours[static_cast<int>(i)], center, radius);
                }
            }
        }
        //矩形框
        //rectangle(frame,rect, Scalar(0,255,0),2);
        //圆形框
        circle(frame, Point(center.x, center.y), (int)radius, Scalar(0, 0, 255), 2);
        imshow("input", frame);
        imshow("output", dst);

        if (waitKey(100) == 27)
            break;
    }

    capture.release();
    return 0;
}

void on_low_r_thresh_trackbar(int, void*)
{
    low_r = min(high_r - 1, low_r);

    setTrackbarPos("Low R", "Object Detection", low_r);
}
void on_high_r_thresh_trackbar(int, void*)
{
    high_r = max(high_r, low_r + 1);
    cout << high_r << endl;
    setTrackbarPos("High R", "Object Detection", high_r);
}
void on_low_g_thresh_trackbar(int, void*)
{
    low_g = min(high_g - 1, low_g);

    setTrackbarPos("Low G", "Object Detection", low_g);
}
void on_high_g_thresh_trackbar(int, void*)
{
    high_g = max(high_g, low_g + 1);
    cout << high_g << endl;
    setTrackbarPos("High G", "Object Detection", high_g);
}
void on_low_b_thresh_trackbar(int, void*)
{
    low_b = min(high_b - 1, low_b);
    setTrackbarPos("Low B", "Object Detection", low_b);
}
void on_high_b_thresh_trackbar(int, void*)
{
    high_b = max(high_b, low_b + 1);
    cout << high_b << endl;
    setTrackbarPos("High B", "Object Detection", high_b);
}
