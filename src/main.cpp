#include "Detector.hpp"
#include "pnp_solve.hpp"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
     Mat K = (Mat_<double>(3,3) << 640.112724,0.000000,292.438835,
0.000000,640.242488,230.378112,
0.000000,0.000000,1.000000);
     Mat D = (Mat_<double>(1,5) << 0.034492,-0.151948,0.003248,0.000364,0.000000);
     Mat src,srcHSV,mask,src1;
     Detector detector;
     Solve solve;
     vector<Point3f> boardPoints;
     vector<vector<Point2f>> corners;
     Mat rvec,tvec;
     VideoCapture cap(0);
     cap >> src;
     double a = 0.057;
     boardPoints.push_back(Point3f(0, 0, 0));       //左上
     boardPoints.push_back(Point3f(a, 0, 0));       //右上
     boardPoints.push_back(Point3f(a, a, 0));       //右下
     boardPoints.push_back(Point3f(0, a, 0));       //左下
     while (cap.read(src))
     {
         if (src.empty())
         {
             break;
         }
         imshow("Image_raw",src);
         detector.detect(src,corners,src1);         //Detector.cpp中克隆src并识别且画了正面的四条线
         solve.solve(src1,boardPoints,corners,K,D,rvec,tvec);
         imshow("result", src1);
         cvtColor(src,srcHSV,COLOR_BGR2HSV);
         inRange(srcHSV,Scalar(0,0,0),Scalar(130,180,180),mask);
         imshow("Image_binary",mask);
         if (waitKey(1) == 27)                  //按esc退出
         {
             break;
         }
      }
}