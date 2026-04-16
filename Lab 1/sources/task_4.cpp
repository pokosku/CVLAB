#include <opencv2/highgui.hpp>
#include <iostream>

bool has_three_channels(cv::Mat& img) {
	return img.channels() == 3;
}

void set_channel_to_zero(cv::Mat& img, int channel_index) {
	if(channel_index < 0 || channel_index >= img.channels()) {
		std::cerr << "Invalid channel index" << std::endl;
		return;
	}
	for (int i = 0; i < img.rows; ++i) {
			for (int j = 0; j < img.cols; ++j) {
				img.at<cv::Vec3b>(i, j)[channel_index] = 0;
			}
		}
}

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

	std::vector<cv::Mat> channels;
	if (has_three_channels(img)){
		cv::split(img,channels);
		for (int i = 0; i < channels.size(); i++){
			cv::namedWindow("Example");
			cv::imshow("Example", channels.at(i));
			cv::waitKey(0);
		}
	}
	return 0;
}