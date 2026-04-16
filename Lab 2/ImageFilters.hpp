#ifndef IMAGE_FILTERS_H
#define IMAGE_FILTERS_H

#include <opencv2/highgui.hpp>

void maxFilter(cv::Mat input, cv::Mat& output, int K);
void minFilter(cv::Mat input, cv::Mat& output, int K);
void medianFilter(cv::Mat input, cv::Mat& output, int K);

#endif IMAGE_FILTERS_H