#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>


cv::Mat img;

void onMouse(int event, int x, int y,int, void*){ 
    if(event == cv::EVENT_LBUTTONDOWN){

        int b = img.at<cv::Vec3b>(y, x)[0];
        int g = img.at<cv::Vec3b>(y, x)[1];
        int r = img.at<cv::Vec3b>(y, x)[2];
        
        std::cout<<"B: " << b << " G: "<< g << " R: "<< r<<std::endl;
    }
}
int main(int argc, char** argv){
    if (argc < 2){
        std::cout << "Usage: ./test <img>"<<std::endl;
        return -1;
    }
    img = cv::imread(argv[1]);

    if (img.empty()) {
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}

    cv::namedWindow("Image");
    cv::imshow("Image",img);
    cv::setMouseCallback("Image", onMouse, 0);
    cv::waitKey(0);

    return 0;
}