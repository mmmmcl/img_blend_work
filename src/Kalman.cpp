/*
 * @Date: 2023-07-18 13:43:34
 * @LastEditors: gyt vocvocal@163.com
 * @LastEditTime: 2024-04-25 13:32:31
 * @FilePath: /Kalman_test/src/Kalman.cpp
 */
#include <Kalman.hpp>
Kalman::KalmanFilter::KalmanFilter(cv::Mat A_, cv::Mat B_, cv::Mat H_, cv::Mat P0, cv::Mat x0, cv::Mat R_, cv::Mat Q_, int statsize)
{
    this->A = A_;
    this->B = B_;
    this->H = H_;
    this->R = R_;
    this->Q = Q_;
    this->P_b = P0;
    this->x_b = x0;
    this->statsize = statsize;
    this->I = cv::Mat::eye(statsize, statsize, CV_64F);
}
Kalman::KalmanFilter::~KalmanFilter()
{
}

void Kalman::KalmanFilter::predict(cv::Mat uk, cv::Mat xk, cv::Mat zk)
{
    x_f = A * x_b + B * uk;
    P_f = A * P_b * A.t() + Q;
    K = P_f * H.t() * (H * P_f * H.t() + R).inv();
    xk = x_f + K * (zk - H * x_f);
    x_b = xk;
    
}
void Kalman::KalmanFilter::update()
{
    P_b = (I - K * H) * P_f;
}
