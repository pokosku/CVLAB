#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include "ImageFilters.hpp"

void maxFilter(cv::Mat input, cv::Mat& output, int K){
    if (K % 2 == 0){
        std::cout<<"Please use odd kernel size!!"<<std::endl;
        return;
    }
    int offset = K/2;
    std::vector<uchar> values;
    for(int i = offset ; i < input.rows - offset; i++){
        for(int j = offset; j < input.cols - offset; j++){
            uchar curr_max = 0;
            for (int k_i = -offset; k_i <= offset; k_i++) {
                for (int k_j = -offset; k_j <= offset; k_j++) {
                    
                    values.push_back(input.at<uchar>(i + k_i, j + k_j));
                }
            }
            output.at<uchar>(i, j) = curr_max;
        }
    }
}

void minFilter(cv::Mat input, cv::Mat& output, int K){
    if (K % 2 == 0){
        std::cout<<"Please use odd kernel size!!"<<std::endl;
        return;
    }
    int offset = K/2;
    
    for(int i = offset ; i < input.rows - offset; i++){
        for(int j = offset; j < input.cols - offset; j++){
            uchar curr_min = 255;
            for (int k_i = -offset; k_i <= offset; k_i++) {
                for (int k_j = -offset; k_j <= offset; k_j++) {
                    
                    uchar val = input.at<uchar>(i + k_i, j + k_j);
                    if (val < curr_min) {
                        curr_min = val;
                    }
                }
            }
            output.at<uchar>(i, j) = curr_min;
        }
    }
}

void medianFilter(cv::Mat input, cv::Mat& output, int K){
    if (K % 2 == 0){
        std::cout<<"Please use odd kernel size!!"<<std::endl;
        return;
    }
    int offset = K/2;
    std::vector<uchar> values(K*K);

    for(int i = offset ; i < input.rows - offset; i++){
        for(int j = offset; j < input.cols - offset; j++){
            uchar curr_min = 255;
            int k = 0;
            for (int k_i = -offset; k_i <= offset; k_i++) {
                for (int k_j = -offset; k_j <= offset; k_j++) {
                    values[k++] = input.at<uchar>(i + k_i, j + k_j);
                }
            }
            std::sort(values.begin(),values.end());
            output.at<uchar>(i, j) = values.at((int)(K*K/2));
        }
    }
}

