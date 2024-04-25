/*
 * @Date: 2023-07-18 13:43:18
 * @LastEditors: gyt vocvocal@163.com
 * @LastEditTime: 2024-04-25 13:49:43
 * @FilePath: /Kalman_test/main.cpp
 */
#include "Kalman.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/hal/interface.h>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

int main()
{
    //系统状态数
    int statsize = 2;
    //量测维数
    int statsize_mea = 1;
    //量测次数
    int N = 20;
    double g = 9.8;
    double v0 = 10;
    double h0 = 1900;

    cv::Mat Q = (cv::Mat_<double>(statsize, statsize) << 0, 0, 0, 0);
    cv::Mat R = (cv::Mat_<double>(statsize_mea, statsize_mea) << 1);
    cv::Mat A = (cv::Mat_<double>(statsize, statsize) << 1, 0, -1, 1);
    cv::Mat B = cv::Mat::eye(2, 2, CV_64F);
    cv::Mat H = (cv::Mat_<double>(statsize_mea, statsize) << 0, 1);

    cv::Mat P0 = (cv::Mat_<double>(statsize, statsize) << 2, 0, 0, 100);
    cv::Mat x0 = (cv::Mat_<double>(statsize, 1) << v0, h0);

    cv::Mat x_rec = cv::Mat::zeros(statsize, N, CV_64F);
    cv::Mat u_rec = cv::Mat::zeros(statsize, N, CV_64F);
    cv::Mat z_rec = 1000 * (cv::Mat_<double>(statsize_mea, N) << 1.9945, 1.9794, 1.9554, 1.9214, 1.8777, 1.8250, 1.7598, 1.6867, 1.6036, 1.5092, 1.4076, 1.2944, 1.1724, 1.0399, 0.8980, 0.7455, 0.5850, 0.4125, 0.2318, 0.0399);

    Kalman::KalmanFilter Kal(A, B, H, P0, x0, R, Q, statsize);

    for (int i = 0; i < N; i++)
    {
        u_rec.at<double>(0, i) = g;
        u_rec.at<double>(1, i) = -0.5 * g;

        Kal.predict(u_rec.col(i), x_rec.col(i), z_rec.col(i));
        Kal.update();
    }

    std::vector<double> z_values, x_values;
    for (int i = 0; i < N; i++)
    {
        z_values.push_back(z_rec.at<double>(0, i));
        x_values.push_back(x_rec.at<double>(1, i)); 
    }
    // for (int i = 0; i < N; i++)
    // {
    //     std::cout << z_rec.col(i) << std::endl;
    //     std::cout << x_rec.col(i) << std::endl;
    //     std::cout << std::endl;
    // }

    
    std::ofstream outputFile("../result.txt");
    // 写入数据到文件
    for (int i = 0; i < N; i++)
    {
        outputFile << std::setprecision(10) << z_rec.at<double>(0, i) << " " << x_rec.at<double>(1, i) << " " << x_rec.at<double>(0, i) << std::endl;
    }
    outputFile.close();
    // 调用Python脚本来绘制滤波结果
    std::system("python ../plot_results.py");
    return 0;
}
