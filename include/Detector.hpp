#include <opencv2/opencv.hpp>
class Detector
{
public:
     void detect(cv::Mat &image,std::vector<std::vector<cv::Point2f>> &corners,cv::Mat &dst);
};