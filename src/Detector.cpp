#include "Detector.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <vector>
using namespace std;
using namespace cv;
using namespace cv::aruco;
void Detector::detect(Mat & img,vector<vector<Point2f>> &corners,Mat &dst,vector<int> &ids,Mat &mask,vector<vector<Point>> &contours,vector<vector<Point>> &contours_result)
{
     if (img.empty())
     {
         return;
     }
     contours_result.clear();
     dst = img.clone();             //此处dst作为输出项，对应main函数里的src1
     findContours(mask,contours,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
     for(int i = 0; i < contours.size(); i++)
     {
         double area = contourArea(contours[i]);
         if(area < 1000)
         {
             continue;
         }
         vector<Point> poly;
         approxPolyDP(contours[i],poly,5,true);
         if(poly.size() != 4)
         {
             continue;
         }
         contours_result.push_back(poly);
         drawContours(dst,contours_result,-1,Scalar(0,255,0),2,LINE_8,noArray(),INT_MAX,Point());
     }
     Ptr<Dictionary> dict = getPredefinedDictionary(DICT_APRILTAG_36h11);
     detectMarkers(img,dict,corners,ids);       //对dst进行识别，不影响原图像
     //cout << "detectMarkers: corners=" << corners.size() << " ids=" << ids.size() << endl;
     /*if(!ids.empty())
     {
         drawDetectedMarkers(dst,corners,ids);
     }*/
     return;
}