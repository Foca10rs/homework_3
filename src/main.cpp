#include "Detector.hpp"
#include "line.hpp"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
     Mat K,D;
     FileStorage fs("calib.yaml", FileStorage::READ);
     fs["camera_matrix"] >> K;
     fs["distortion_coefficients"] >> D;
     Mat src,srcHSV,mask,src_result,src_gray;
     Detector detector;
     Line line_points;
     vector<Point3f> boardPoints;
     vector<vector<Point2f>> corners;
     vector<int> ids;
     Mat rvec,tvec;
     vector<vector<Point>> contours,contours_result;
     VideoCapture cap(0);
     cap >> src;
     double cube_size = 0.057;
     boardPoints.push_back(Point3f(0, 0, 0));       //左上
     boardPoints.push_back(Point3f(0, cube_size, 0));       //左下
     boardPoints.push_back(Point3f(cube_size, cube_size, 0));       //右下
     boardPoints.push_back(Point3f(cube_size, 0, 0));       //右上
     
     
     while (cap.read(src))
     {
         if (src.empty())
         {
             break;
         }
         imshow("Image_raw",src);
         cvtColor(src,src_gray,COLOR_BGR2GRAY);
         GaussianBlur(src_gray,src_gray,Size(3,3),3,3);
         //Canny(src_gray,src_gray,110,255);
         threshold(src_gray,mask,110,255,THRESH_BINARY_INV);
         morphologyEx(mask,mask,MORPH_OPEN,Mat());
         imshow("Image_binary",mask);
         
         /*cvtColor(src,srcHSV,COLOR_BGR2HSV);
         inRange(srcHSV,Scalar(0,0,110),Scalar(180,255,255),mask);
         morphologyEx(mask,mask,MORPH_CLOSE,Mat());
         imshow("Image_binary",mask);*/

         detector.detect(src,corners,src_result,ids,mask,contours,contours_result);         //Detector.cpp中克隆src并识别且画了正面的四条线
         if (!contours_result.empty())
         {
             std::vector<cv::Point2f> quad(contours_result[0].begin(), contours_result[0].end());
             solvePnP(boardPoints, quad, K, D, rvec, tvec, false, SOLVEPNP_IPPE);
             //solvePnP(boardPoints,contours_result[0],K,D,rvec,tvec,false,SOLVEPNP_IPPE);
             if (!ids.empty() && !corners.empty())
             {
                 line_points.line_points(src_result,K,D,rvec,tvec,ids,contours_result);
             }
         }
         imshow("result", src_result);
         
         if (waitKey(1) == 27)                  //按esc退出
         {
             break;
         }
      }
}