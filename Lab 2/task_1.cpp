#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

int main(int argc, char** argv){
    cv::Mat garden = cv::imread("../Garden.jpg");
    if(garden.empty()){
        std::cout<<"Missing Garden.jpg image"<<std::endl;
        return -1;
    }
    cv::namedWindow("Garden RGB");
    cv::imshow("Garden RGB", garden);
    cv::waitKey(0);

    cv::Mat garden_gray = garden.clone();
    cv::cvtColor(garden, garden_gray, cv::COLOR_BGR2GRAY);

    cv::namedWindow("Garden RGB");
    cv::imshow("Garden RGB", garden_gray);
    cv::waitKey(0);

    return 0;
}