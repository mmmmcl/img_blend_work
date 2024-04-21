#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <Laplablend.hpp>
cv::Mat LaplacianBlend(const cv::Mat &left, const cv::Mat &right, const cv::Mat &mask) 
{
    LaplacianBlending laplaceBlend(left, right, mask, 15);
    return laplaceBlend.blend();
}
int main() {
    cv::Mat img8UL = cv::imread("../data/pic1.png");  //build与图片与main同级目录
    cv::Mat img8UR = cv::imread("../data/pic2.png");

    assert(!img8UR.empty());
    assert(!img8UL.empty());
    
    cv::resize(img8UL, img8UL, cv::Size(img8UR.cols, img8UR.rows));
    int imgH = img8UL.rows;
    int imgW = img8UL.cols;
    cv::imshow("left", img8UL);
    cv::imshow("right", img8UR);

    cv::Mat img32fL, img32fR; 
    img8UL.convertTo(img32fL, CV_32F);
    img8UR.convertTo(img32fR, CV_32F);


    //创建mask
    cv::Mat mask = cv::Mat::zeros(imgH, imgW, CV_32FC1);
    mask(cv::Range::all(), cv::Range(0, mask.cols * 0.5)) = 1.0;

    cv::Mat blendImg = LaplacianBlend(img32fL, img32fR, mask);

    blendImg.convertTo(blendImg, CV_8UC3);
    cv::imshow("blended", blendImg);
    cv::imwrite("../data/blend.png",blendImg);
    cv::waitKey(0);
    return 0;
}
