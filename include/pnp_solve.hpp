#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
class Solve
{
public:
     void solve(cv::Mat &src,std::vector<cv::Point3f> &boardPoints,std::vector<std::vector<cv::Point2f>> &corners,cv::Mat &K,cv::Mat &D,cv::Mat &rvec,cv::Mat & tvec);
};