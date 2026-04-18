#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat define_roi(Mat src, vector<Point> pts);

vector<Vec2f> select_lines(vector<Vec2f> houghlines);

Point compute_intersection(vector<Vec2f> lines);

void draw_lane(Mat src, vector<Vec2f> lane_bounds, Mat roi_mask);

