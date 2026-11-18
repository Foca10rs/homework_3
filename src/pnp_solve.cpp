#include "pnp_solve.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
void Solve::solve(Mat &src,Mat &K,Mat &D,Mat &rvec,Mat & tvec)
{
     double cube_size = 0.057;                       //手机上tag边长
     vector<Point3f> tagPoint(8);
     tagPoint[0] = Point3f(0,0,0);                                 //前面左上
     tagPoint[1] = Point3f(cube_size,0,0);                         //前面右上
     tagPoint[2] = Point3f(cube_size,cube_size,0);                 //前面右下
     tagPoint[3] = Point3f(0,cube_size,0);                         //前面左下
     
     tagPoint[4] = Point3f(0,0,cube_size);                         //背面左上
     tagPoint[5] = Point3f(cube_size,0,cube_size);                 //背面右上
     tagPoint[6] = Point3f(cube_size,cube_size,cube_size);         //背面右下
     tagPoint[7] = Point3f(0,cube_size,cube_size);                 //背面左下
     int thickness = 2;
     vector <Point2f> pixel;   
     projectPoints(tagPoint, rvec, tvec, K, D, pixel);      //AI给的函数，说能直接投影3D点到2D像素
     line(src,pixel[0],pixel[4],Scalar(0,255,0),thickness);
     line(src,pixel[1],pixel[5],Scalar(0,255,0),thickness);
     line(src,pixel[2],pixel[6],Scalar(0,255,0),thickness);
     line(src,pixel[3],pixel[7],Scalar(0,255,0),thickness);
     line(src,pixel[4],pixel[5],Scalar(0,255,0),thickness);
     line(src,pixel[5],pixel[6],Scalar(0,255,0),thickness);
     line(src,pixel[6],pixel[7],Scalar(0,255,0),thickness);
     line(src,pixel[7],pixel[4],Scalar(0,255,0),thickness);
}