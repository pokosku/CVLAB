#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

using namespace cv;



Mat src, src_gray;
Mat dst, detected_edges;


int threshold1 = 0;
int threshold2 = 0;
int ratio = 3;
const int max_trackbar_size= 100;
int kernel_size = 3;
const char* window_name = "Edge Map";

static void CannyThreshold( int, void* ){
    blur(src_gray, detected_edges, Size(3,3));
    Canny(detected_edges, detected_edges, threshold1, threshold2*ratio, kernel_size);
    dst = Scalar(0);
    src.copyTo(dst, detected_edges);

    imshow(window_name, dst);
}

int main(int argc, char** argv){

    src = imread("../street_scene.png");
    dst.create(src.size(), src.type());

    namedWindow(window_name);

    cvtColor(src, src_gray, COLOR_BGR2GRAY); 

    createTrackbar("Min threshold", window_name, &threshold1, max_trackbar_size, CannyThreshold);
    createTrackbar("Max threshold", window_name, &threshold2, max_trackbar_size, CannyThreshold);

    CannyThreshold(threshold1,0);
    CannyThreshold(threshold2,0);

    waitKey(0);
    return 0;
}