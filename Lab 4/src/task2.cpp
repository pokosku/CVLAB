#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

using namespace cv;
using namespace std;


string window_name = "Edges";

Mat define_roi(Mat src, vector<Point> pts){
    // pts wrt y coordinates
    Mat mask = Mat::zeros(Size(src.cols, src.rows), CV_8UC1);
    
    fillPoly(mask, pts, Scalar(255));

    imshow(window_name, mask);
    waitKey(0);
    Mat masked_src = src.clone();
    bitwise_and(src, mask, masked_src);

    return masked_src;
}

vector<Vec2f> select_lines(vector<Vec2f> houghlines){
    vector<Vec2f> selected_lines;
    selected_lines.push_back(houghlines.at(0));
    
    
    int i = 0;
    

    double theta1 = selected_lines[0][1];

    // best possible candidate by opposite orientation
    while (selected_lines.size() < 2){
        if (houghlines[i][0] < 0){
            selected_lines.push_back(houghlines.at(i));
            break;
        }
        i++;
    }

    return selected_lines;

}


void draw_lane(){

}
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

    vector<Point> pts = {Point(0.2*src.cols, src.rows -1), Point(src.cols/2,src.rows/2), Point(0.8*src.cols, src.rows -1)};

    

    Canny(detected_edges, dst, 50, 150, 3);  

    
    imshow(window_name, dst);
    waitKey(0);

    Mat restricted_edges = define_roi(dst, pts);

    imshow(window_name, restricted_edges);
    waitKey(0);


    vector<Vec2f> lines;
    HoughLines(restricted_edges, lines, 1, CV_PI/180, 100, 0, 0);
    
    vector<Vec2f> best_lines = select_lines(lines);
    

    for( size_t i = 0; i < best_lines.size(); i++ )
    {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
        line( src, pt1, pt2, Scalar(0,0,255), 3, LINE_AA);
    }

    imshow(window_name, src);
    waitKey(0);

    cout << best_lines[0] << endl << best_lines[1] << endl;
    
    return 0;
}