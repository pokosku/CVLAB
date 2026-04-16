#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
int main(int argc, char** argv){
    if (argc < 2){
        std::cout << "Usage: display_image ImageToLoadAndDisplay" << std::endl;
        return -1;
    }

    cv::Mat input = cv::imread(argv[1]);
    cv::namedWindow("Input image");
    cv::imshow("Input image", input);
    cv::waitKey(0);
    
    cv::Mat gray;
    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);
    cv::Mat output;

    cv::namedWindow("Gray image");
    cv::imshow("Gray image", gray);
    cv::waitKey(0);

    //average filter
    cv::Mat kernel = cv::Mat::ones(5,5,CV_32F) / 25.0;
    cv::filter2D(gray, output, -1, kernel); 
    
    cv::namedWindow("Output image");
    cv::imshow("Output image", output);
    cv::waitKey(0);

    //Sobel filter
    cv::Sobel(gray, output, -1, 1, 1, 3);
    cv::namedWindow("Sobel image");
    cv::imshow("Sobel image", output);
    cv::waitKey(0);

    //Max filter
    cv::dilate(gray, output, cv::Mat());
    cv::namedWindow("Max image");
    cv::imshow("Max image", output);
    cv::waitKey(0);

    //Min filter
    cv::erode(gray, output, cv::Mat());
    cv::namedWindow("Min image");
    cv::imshow("Min image", output);
    cv::waitKey(0);
    return 0;
}  