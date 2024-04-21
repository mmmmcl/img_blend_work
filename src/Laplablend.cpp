/*
 * @Date: 2024-03-23 21:25:24
 * @LastEditors: gyt vocvocal@163.com
 * @LastEditTime: 2024-04-21 20:08:19
 * @FilePath: /img_fusion/src/Laplablend.cpp
 */
#include "Laplablend.hpp"
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <string>


LaplacianBlending::LaplacianBlending(const cv::Mat &_left, const cv::Mat &_right, const cv::Mat &_blendMask, int _levels) : // construct function, used in LaplacianBlending lb(l,r,m,4);
                                                                                                         left(_left), right(_right), blendMask(_blendMask), levels(_levels)
{
    assert(_left.size() == _right.size());
    assert(_left.size() == _blendMask.size());
    //创建拉普拉斯金字塔和高斯金字塔
    buildPyramids();
    //每层金字塔图像合并为一个
    blendLapPyrs();
};
void LaplacianBlending::buildPyramids()
{
    buildLaplacianPyramid(left, leftLapPyr, leftHighestLevel);
    buildLaplacianPyramid(right, rightLapPyr, rightHighestLevel);
    buildGaussianPyramid();
}

void LaplacianBlending::buildGaussianPyramid()
{
    //金字塔内容为每一层的掩模
    assert(leftLapPyr.size() > 0);

    maskGaussianPyramid.clear();
    cv::Mat currentImg;
    cv::cvtColor(blendMask, currentImg, cv::COLOR_GRAY2BGR);
    //保存mask金字塔的每一层图像
    maskGaussianPyramid.push_back(currentImg); // 0-level
    
    currentImg = blendMask;
    for (int l = 1; l < levels + 1; l++)
    {
        cv::Mat _down;
        if (leftLapPyr.size() > l)
            cv::pyrDown(currentImg, _down, leftLapPyr[l].size());
        else
            cv::pyrDown(currentImg, _down, leftHighestLevel.size()); // lowest level

        cv::Mat down;
        cv::cvtColor(_down, down, cv::COLOR_GRAY2BGR);
        // add color blend mask into mask Pyramid
        maskGaussianPyramid.push_back(down);
        currentImg = _down;
    }
}

void LaplacianBlending::buildLaplacianPyramid(const cv::Mat &img, std::vector<cv::Mat> &lapPyr, cv::Mat &HighestLevel)
{
    lapPyr.clear();
    cv::Mat currentImg = img;
    for (int l = 0; l < levels; l++)
    {
        cv::Mat down, up;
        cv::pyrDown(currentImg, down);
        cv::pyrUp(down, up, currentImg.size());
        cv::Mat lap = currentImg - up;
        lapPyr.push_back(lap);
        currentImg = down;
    }
    currentImg.copyTo(HighestLevel);
}

cv::Mat LaplacianBlending::reconstructImgFromLapPyramid()
{
    //将左右laplacian图像拼成的resultLapPyr金字塔中每一层
    //从上到下插值放大并与残差相加，即得blend图像结果
    cv::Mat currentImg = resultHighestLevel;
    for (int l = levels - 1; l >= 0; l--)
    {
        cv::Mat up;
        cv::pyrUp(currentImg, up, resultLapPyr[l].size());
        currentImg = up + resultLapPyr[l];
    }
    return currentImg;
}

void LaplacianBlending::blendLapPyrs()
{
    //获得每层金字塔中直接用左右两图Laplacian变换拼成的图像resultLapPyr
    resultHighestLevel = leftHighestLevel.mul(maskGaussianPyramid.back()) +
                         rightHighestLevel.mul(cv::Scalar(1.0, 1.0, 1.0) - maskGaussianPyramid.back());
    for (int l = 0; l < levels; l++)
    {
        cv::Mat A = leftLapPyr[l].mul(maskGaussianPyramid[l]);
        cv::Mat antiMask = cv::Scalar(1.0, 1.0, 1.0) - maskGaussianPyramid[l];
        cv::Mat B = rightLapPyr[l].mul(antiMask);
        cv::Mat blendedLevel = A + B;

        resultLapPyr.push_back(blendedLevel);
    }
}



cv::Mat LaplacianBlending::blend()
{
    //重建拉普拉斯金字塔
    return reconstructImgFromLapPyramid();
}
