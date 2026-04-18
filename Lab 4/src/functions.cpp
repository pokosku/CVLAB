#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

using namespace cv;
using namespace std;


Mat define_roi(Mat src, vector<Point> pts){
    // pts wrt y coordinates
    Mat mask = Mat::zeros(Size(src.cols, src.rows), CV_8UC1);
    
    fillPoly(mask, pts, Scalar(255));
    
    Mat masked_src = src.clone();
    bitwise_and(src, mask, masked_src);

    return masked_src;
}

vector<Vec2f> select_lines(vector<Vec2f> houghlines){
    vector<Vec2f> selected_lines;
    
    Vec2f left_line(0,0), right_line(0,0);
    
    bool left_chosen = false;
    bool right_chosen = false;
    

    
    // best possible candidate by opposite orientation
    for(int i = 0; (i < houghlines.size()); i++){
        Vec2f line = houghlines.at(i);
        double theta = houghlines[i][1];
        cout << line << endl;
        if(!left_chosen and ((theta > (CV_PI/6)) and (theta < (CV_PI/3)))){
            left_line = line;
            left_chosen = true;
        }else if(!right_chosen and ((theta > (2*CV_PI/3)) and (theta < (5*CV_PI/6)))){
            right_line = line;
            right_chosen = true;
        }

        if(left_chosen and right_chosen)
            break;
    } 


    selected_lines.push_back(left_line);
    selected_lines.push_back(right_line);

    return selected_lines;

}

Point compute_intersection(vector<Vec2f> lines){
    Vec2f line1 = lines[0], line2 = lines[1];

    float rho1 = line1[0], theta1 = line1[1];
    float rho2 = line2[0], theta2 = line2[1];

    float det = cos(theta1) * sin(theta2) - sin(theta1) * cos(theta2);

    if (std::abs(det) < 1e-6) {
        return Point2f(-1, -1);
    }

    float x = (rho1 * sin(theta2) - rho2 * sin(theta1)) / det;
    float y = (rho2 * cos(theta1) - rho1 * cos(theta2)) / det;

    return Point2f(x, y);

}
void draw_lane(Mat src, vector<Vec2f> lane_bounds, Mat roi_mask){

    double rho1 = lane_bounds[0][0], rho2 = lane_bounds[0][1];
    double theta1 = lane_bounds[0][1], theta2 = lane_bounds[1][1];

    float y_base = src.rows - 1;
    float x_b1 = (lane_bounds[0][0] - y_base * sin(lane_bounds[0][1])) / cos(lane_bounds[0][1]);
    float x_b2 = (lane_bounds[1][0] - y_base * sin(lane_bounds[1][1])) / cos(lane_bounds[1][1]);

    Point v = compute_intersection(lane_bounds);
    vector<cv::Point> pts = { v, Point(x_b1, y_base), cv::Point(x_b2, y_base) };   
    fillPoly(src, pts, Scalar(0, 0, 255));

}