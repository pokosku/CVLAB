#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include "include/functions.hpp"

using namespace cv;
using namespace std;

//Canny thresholds
int threshold_c_1 = 10;
int threshold_c_2 = 10;
int threshold_th = 150;
int ratio = 3;

//Hough circle params
int param_1 = 150;
int param_2 = 50;
string canny_window = "canny";
string hough_window = "hough";


Mat src, src_gray;
Mat dst, detected_edges;


static void houghcircle_params(int, void*){
    vector<Vec3f> circles;
    Mat display = src.clone();

    

    HoughCircles(src_gray, circles, HOUGH_GRADIENT, 1, src_gray.cols/10, param_1, param_2);
    

    if(circles.empty()){
        cerr << "No circles found" << endl;
        return;
    }

    for (auto &c : circles){
        cout << c<< endl;
        double x = c[0], y = c[1], radius = c[2];
        circle(display, Point(x, y), radius, Scalar(0,255,0), 2);
    }

    imshow(hough_window, display);
}

int main(int argc, char** argv){

    
    //namedWindow(canny_window, WINDOW_NORMAL);
    

    if(argc < 2){
        cerr<<"Pass an image by CLI"<<endl;
        return -1;
    }

    
    src = imread(argv[1],IMREAD_COLOR_BGR);

    cvtColor(src, src_gray, COLOR_BGR2GRAY); 

    GaussianBlur(src_gray, src_gray, Size(5, 5), 0);

   
    namedWindow(hough_window, WINDOW_NORMAL);
    
    imshow(hough_window, src_gray);
    waitKey(0);
    createTrackbar("Param 1", hough_window, &param_1, 300, houghcircle_params);
    createTrackbar("Param 2", hough_window, &param_2, 150, houghcircle_params);
    


    houghcircle_params(param_1,0);
    houghcircle_params(param_2,0);

    
    waitKey(0);
    
    return 0;
}