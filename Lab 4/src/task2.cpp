#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include "include/functions.hpp"

using namespace cv;
using namespace std;


string window_name = "Edges";

int main(int argc, char** argv){

    
    namedWindow(window_name, WINDOW_NORMAL);

    Mat src, src_gray;

    if(argc < 2){
        cerr<<"Pass an image by CLI"<<endl;
        return -1;
    }

    Mat dst, detected_edges;
    src = imread(argv[1],IMREAD_COLOR_BGR);
    

    cvtColor(src, src_gray, COLOR_BGR2GRAY); 
    threshold(src_gray,src_gray, 200, 255, THRESH_BINARY);
    GaussianBlur(src_gray, detected_edges, Size(3,3), 0);


    vector<Point> pts = {Point(0.15*src.cols, src.rows -1), Point(0.45*src.cols, 0.5* src.rows), Point(0.55*src.cols, 0.5*src.rows), Point(0.85*src.cols, src.rows -1)};

    

    Canny(detected_edges, dst, 50, 150, 3);  

    
    imshow(window_name, dst);
    waitKey(0);

    Mat restricted_edges = define_roi(dst, pts);

    imshow(window_name, restricted_edges);
    waitKey(0);


    vector<Vec2f> lines;
    HoughLines(restricted_edges, lines, 1, CV_PI/180, 50, 0, 0);
    
    vector<Vec2f> best_lines = select_lines(lines);

    draw_lane(src, best_lines, restricted_edges);
   

    imshow(window_name, src);
    waitKey(0);

    
    return 0;
}