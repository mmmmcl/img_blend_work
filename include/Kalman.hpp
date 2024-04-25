/*
 * @Date: 2023-07-18 13:43:29
 * @LastEditors: gyt vocvocal@163.com
 * @LastEditTime: 2024-04-23 13:01:57
 * @FilePath: /Kalman_test/include/Kalman.hpp
 */
#ifndef _KALMAN
#define _KALMAN

#include <iostream>
#include <opencv2/opencv.hpp>
namespace Kalman
{

    class KalmanFilter
    {

    public:
        KalmanFilter(cv::Mat A_, cv::Mat B_, cv::Mat H_, cv::Mat P0, cv::Mat x0, cv::Mat  R_, cv::Mat Q_, int statsize);
        ~KalmanFilter();

        void predict(cv::Mat uk,  cv::Mat xk,cv::Mat zk);
        void update();

    private:
        

        double statsize;
        cv::Mat Q;
        cv::Mat R;
        cv::Mat x_f;
        cv::Mat x_b;

        cv::Mat z;
        cv::Mat u;
        cv::Mat P_f;
        cv::Mat P_b;
        cv::Mat K;
        cv::Mat A;
        cv::Mat B;
        cv::Mat H;
        cv::Mat I;
    };

};
#endif