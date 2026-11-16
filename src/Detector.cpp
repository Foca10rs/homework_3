#include "Detector.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <vector>
using namespace std;
using namespace cv;
using namespace cv::aruco;
void Detector::detect(Mat & img,vector<vector<Point2f>> &corners,Mat &dst)
{
     if (img.empty())
     {
         return;
     }
     dst = img.clone();             //此处dst作为输出项，对应main函数里的src1
     vector<int> ids;
     Ptr<Dictionary> dict = getPredefinedDictionary(DICT_APRILTAG_36h11);
     detectMarkers(dst,dict,corners,ids);       //对dst进行识别并后续画图，不影响原图像
     if(!ids.empty())
     {
         drawDetectedMarkers(dst,corners,ids);
     }
     return;
}