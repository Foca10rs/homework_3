#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
class Line
{
public:
     void line_points(cv::Mat &src,cv::Mat &K,cv::Mat &D,cv::Mat &rvec,cv::Mat & tvec,std::vector<int> &ids,std::vector<std::vector<cv::Point>> &contours_result);
};