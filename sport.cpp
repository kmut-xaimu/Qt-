#include "opencv2/opencv.hpp"
#include <opencv2\imgproc\types_c.h>
#include<iostream>
using namespace std;
using namespace cv;



Mat MoveDetect(Mat frame1, Mat frame2)
{
    Mat result = frame2.clone();
    Mat gray1, gray2;
    cvtColor(frame1, gray1, CV_BGR2GRAY);
    cvtColor(frame2, gray2, CV_BGR2GRAY);

    Mat diff;
    absdiff(gray1, gray2, diff);
    imshow("absdiss", diff);
    threshold(diff, diff, 45, 255, CV_THRESH_BINARY);
    imshow("threshold", diff);

    Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
    Mat element2 = getStructuringElement(MORPH_RECT, Size(25, 25));
    erode(diff, diff, element);
    imshow("erode", diff);

    dilate(diff, diff, element2);
    imshow("dilate", diff);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarcy;
    //画椭圆及中心
    findContours(diff, contours, hierarcy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    cout << "num=" << contours.size() << endl;
    vector<RotatedRect> box(contours.size());
    for (int i = 0; i < contours.size(); i++)
    {
        box[i] = fitEllipse(Mat(contours[i]));
        ellipse(result, box[i], Scalar(0, 255, 0), 2, 8);
        circle(result, box[i].center, 3, Scalar(0, 0, 255), -1, 8);
    }
    return result;
}



int sport()
{


    VideoCapture capture;
    capture.open(0);
    if (!capture.isOpened())
    {
        printf("can not open video file   \n");
        return -1;
    }


    Mat frame;
    Mat result;
    Mat background;
    int count = 0;
    while (1)
    {
        capture >> frame;

        if (frame.empty())
            break;
        else
        {
            count++;
            if (count == 1)
            {
                background = frame.clone(); //提取第一帧为背景帧
            }

            imshow("video", frame);
            result = MoveDetect(background, frame);
            imshow("result", result);
            if (waitKey(50) == 27)
                break;
        }
    }


    capture.release();
    return 0;
}
