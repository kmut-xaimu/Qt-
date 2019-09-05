#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

// 控制编译版本宏
//#define VERSION_2_4

//参数 : 输入图像、级联分类器、缩放倍数
void DetectAndDraw(Mat& img, CascadeClassifier& cascade, double scale);

int face()
{
    CascadeClassifier faceCascade;
    double scale = 4;
    int		nRet = 0;

    VideoCapture capture(0);
    //capture.open(0);
   //capture.open("video.avi");
    if (!capture.isOpened())
    {
        cout << "open camera failed. " << endl;
        return -1;
    }
    cout << "open camera succeed. " << endl;

    //加载分类器
#ifdef VERSION_2_4

#else
    nRet = faceCascade.load("./haarcascade_frontalface_alt.xml");
#endif

    if (!nRet)
    {
        printf("load xml failed.\n");
        return -1;
    }

    Mat frame;
    vector<Rect> faces;
    while (1)
    {
        capture >> frame;
        if (frame.empty())
        {
            continue;
        }

        Mat frame1 = frame.clone();
        DetectAndDraw(frame1, faceCascade, scale);

        if (waitKey(30) == 27)
            break;
    }

    return 0;
}

void DetectAndDraw(Mat& img, CascadeClassifier& cascade, double scale)
{
    double t = 0;
    vector<Rect> faces;
    Mat gray, smallImg;
    double fx = 1 / scale;

    cvtColor(img, gray, COLOR_BGR2GRAY);	// 将源图像转为灰度图0

    // 缩放图像
#ifdef VERSION_2_4
    resize(gray, smallImg, Size(), fx, fx, INTER_LINEAR);
#else
    resize(gray, smallImg, Size(), fx, fx, INTER_LINEAR_EXACT);
#endif

    equalizeHist(smallImg, smallImg);	// 直方图均衡化，提高图像质量

    //检测目标
    t = (double)getTickCount();
    cascade.detectMultiScale(smallImg, faces,
        1.1, 2, 0
        //|CASCADE_FIND_BIGGEST_OBJECT
        //|CASCADE_DO_ROUGH_SEARCH
        | CASCADE_SCALE_IMAGE,
        Size(30, 30));
    t = (double)getTickCount() - t;
    printf("detection time = %g ms\n", t * 1000 / getTickFrequency());

    //画矩形框出目标
    for (size_t i = 0; i < faces.size(); i++) // faces.size():检测到的目标数量
    {
        Rect rectFace = faces[i];

        rectangle(img, Point(rectFace.x, rectFace.y) * scale,
            Point(rectFace.x + rectFace.width, rectFace.y + rectFace.height) * scale,
            Scalar(0, 255, 0), 2, 8);
    }

    imshow("FaceDetect", img);	// 显示
}
