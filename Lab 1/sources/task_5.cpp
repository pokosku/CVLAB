#include <opencv2/highgui.hpp>
#include <iostream>

cv::Mat create_checkboard(int board_size, int square_size){
    cv::Mat check_board = cv::Mat::zeros(board_size, board_size, CV_8UC1);
    
    for(int i = 0; i < board_size; i+=square_size ){
        for(int j = 0; j < board_size; j+=square_size){
            int grid_row = i / square_size;
            int grid_col = j / square_size;

            if((grid_row + grid_col) % 2 == 0){
                cv::Rect roi(i,j,square_size, square_size);
                check_board(roi) = cv::Scalar(255);
            }
        }
    }
    return check_board;

}
int main(int argc, char** argv){
    
    cv::Mat img1 (256, 256, CV_8UC1);
    cv::Mat img2 (256, 256, CV_8UC1);

    for(int i = 0; i < 256; i++){
        for(int j = 0; j < 256; j++){
            img1.at<uchar>(i,j) = 255 - i;
            img2.at<uchar>(i,j) = j;
        }
    }

    cv::namedWindow("Example 1");
    cv::imshow("Example 1", img1);

    cv::waitKey(0);

    cv::namedWindow("Example 2");
    cv::imshow("Example 2", img2);
    
    cv::waitKey(0);

    // Lets create the checkboards now
    /*
    cv::Mat check_1 = cv::Mat::zeros(300, 300,CV_8UC1);
    cv::Mat check_2 = cv::Mat::zeros(300, 300,CV_8UC1);

    int square_1 = 20;
    int square_2 = 50;
    bool white_1 = true;
    bool white_2 = true;
    
    for (int i = 0; i < check_1.rows; i++){
        for (int j = 0; j < check_1.cols; j++){
            if (j % square_1 == 0)
                    white_1 = !white_1;
            if (j % square_2 == 0)
                    white_2 = !white_2;
            if (white_1)
                check_1.at<uchar>(i,j) = 255;
            if (white_2)
                check_2.at<uchar>(i,j) = 255;
        }
        if (i % square_1 != 0 || i == 0)
            white_1 = !white_1;
        if (i % square_2 == 0)
            white_2 = !white_2;
    }

    */

    cv::Mat check_1 = create_checkboard(300,20);
    cv::Mat check_2 = create_checkboard(300,50);

    cv::namedWindow("Example 3");
    cv::imshow("Example 3", check_1);
    cv::waitKey(0);
    cv::namedWindow("Example 4");
    cv::imshow("Example 4", check_2);
    cv::waitKey(0);




    return 0;


}