#include <opencv2/opencv.hpp>
#include <iostream>
#include <string> 
class LaplacianBlending {
private:
    cv::Mat left;
    cv::Mat right;
    cv::Mat blendMask;

    //Laplacian Pyramids
    std::vector<cv::Mat> leftLapPyr, rightLapPyr, resultLapPyr;
    cv::Mat leftHighestLevel, rightHighestLevel, resultHighestLevel;
    //mask为三通道方便矩阵相乘
    std::vector<cv::Mat> maskGaussianPyramid; 

    int levels;

    void buildPyramids();

    void buildGaussianPyramid();

    void buildLaplacianPyramid(const cv::Mat& img, std::vector<cv::Mat>& lapPyr, cv::Mat& HighestLevel);

    cv::Mat reconstructImgFromLapPyramid();

    void blendLapPyrs();

public:
    LaplacianBlending(const cv::Mat& _left, const cv::Mat& _right, const cv::Mat& _blendMask, int _levels); //construct function, used in LaplacianBlending lb(l,r,m,4);
    cv::Mat blend();
};