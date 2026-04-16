#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

int main(int argc, char** argv){
    cv::Mat img = cv::imread(argv[1]);
    if(img.empty()){
        std::cout<<"Missing img.jpg image"<<std::endl;
        return -1;
    }

    cv::Mat img_gray = img.clone();
    cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);

    cv::namedWindow("img Gray");
    cv::imshow("img Gray", img_gray);
    cv::waitKey(0);

    int bins = 256;
    float grange[] = {0, 256}; // Upper bound is exclusive in calcHist
    const float* ranges[] = {grange};

    cv::Mat hist;

    cv::calcHist(&img_gray, 1, 0, cv::Mat(), hist, 1, &bins, ranges, true, false);

    cv::Mat histImg = cv::Mat::zeros(bins, bins, CV_8UC1);

    
    

    cv::normalize(hist, hist, 0, histImg.rows, cv::NORM_MINMAX, -1, cv::Mat());
    
    int bin_w = histImg.cols / bins;
    for(int i = 0; i < bins; i++){
        cv::line(histImg,
                 cv::Point(i * bin_w, histImg.rows - 1),
                 cv::Point(i * bin_w, histImg.rows - cvRound(hist.at<float>(i)) - 1),
                 cv::Scalar(255), bin_w, 8, 0);
    }

    cv::namedWindow("histImg");
    cv::imshow("histImg", histImg);
    cv::waitKey(0);

    return 0;
}