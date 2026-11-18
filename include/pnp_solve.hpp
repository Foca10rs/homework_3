#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
class Solve
{
public:
     void solve(cv::Mat &src,cv::Mat &K,cv::Mat &D,cv::Mat &rvec,cv::Mat & tvec);
};