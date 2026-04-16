#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>


cv::Mat img;

void onMouse(int event, int x, int y,int, void*){ 
    if(event == cv::EVENT_LBUTTONDOWN){
        
        double sums[3] = {0,0,0};

        
        for(int i = y - 4; i < y + 5; i++){
            for(int j = x - 4; j < x + 5; j++){
                sums[0] += img.at<cv::Vec3b>(i,j)[0];
                sums[1] += img.at<cv::Vec3b>(i,j)[1];
                sums[2] += img.at<cv::Vec3b>(i,j)[2];
            }
        }
        std::cout << "H mean: " << sums[0]/81 << " S mean: " << sums[1]/81  << " V mean: " << sums[2]/81 << std::endl;
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