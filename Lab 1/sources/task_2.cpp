#include <opencv2/highgui.hpp>
#include <iostream>
int main(int argc, char** argv){
	if (argc < 2) {
		std::cout << "Usage: display_image ImageToLoadAndDisplay" << std::endl;
		return -1;
	}
	cv::Mat img = cv::imread(argv[1]);
	
	if (img.empty()) {
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}
    std::cout << "#Channels: " << img.channels() << std::endl;
	cv::namedWindow("Example 1");
	cv::imshow("Example 1", img);
	char entered_key = cv::waitKey(0);
	std::cout << "Entered key: " << entered_key << std::endl;
	return 0;
}
