#include <opencv2/opencv.hpp>
class Detector
{
public:
     void detect(cv::Mat &image,std::vector<std::vector<cv::Point2f>> &corners,cv::Mat &dst,std::vector<int> &ids,cv::Mat &mask,std::vector<std::vector<cv::Point>> &contours,std::vector<std::vector<cv::Point>> &contours_result);
};