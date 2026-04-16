#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include "ImageFilters.hpp"
 
int main(int argc, char** argv){
    cv::Mat img = cv::imread(argv[1]);
    if(img.empty()){
        std::cout<<"Missing img.jpg image"<<std::endl;
        return -1;
    }
    cv::namedWindow("img RGB");
    cv::imshow("img RGB", img);
    cv::waitKey(0);

    cv::Mat img_gray = img.clone();
    cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);

    cv::namedWindow("img Gray");
    cv::imshow("img Gray", img_gray);
    cv::waitKey(0);

    cv::Mat img_gaussian = img_gray.clone();
    
    cv::Mat img_median = img_gray.clone();
    medianFilter(img_gray, img_median, 11);

    cv::namedWindow("img Median");
    cv::imshow("img Median", img_median);
    cv::waitKey(0);

    cv::GaussianBlur(img_gray, img_gaussian, cv::Size(11,11), 5);

    cv::namedWindow("img Gaussian");
    cv::imshow("img Gaussian", img_gaussian);
    cv::waitKey(0);

    return 0;
}