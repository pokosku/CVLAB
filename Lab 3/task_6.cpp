#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

int main(int argc, char** argv){
    cv::Mat input;
    if (argc < 2){
        std::cout << "Usage: ./test <img>"<<std::endl;
        return -1;
    }
    input = cv::imread(argv[1]);

    if (input.empty()) {
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}
    
    cv::Mat gray;
    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(gray, gray, cv::Size(7,7), 0);
    
    cv::Mat mask;
    cv::threshold(gray, mask, 70, 255 , cv::THRESH_BINARY_INV);

    cv::Mat markers;
    cv::connectedComponents(mask, markers);

    cv::watershed(input,markers);

    
    cv::Mat result = input.clone();
    for (int i = 0; i < markers.rows; i++) {
        for (int j = 0; j < markers.cols; j++) {
            if (markers.at<int>(i, j) == -1) {
                
                result.at<cv::Vec3b>(i, j) = cv::Vec3b(0, 0, 255);
            }
        }
    }

    cv::namedWindow("Segmented Result");
    cv::imshow("Segmented Result", result);
    cv::waitKey(0);

    return 0;
}