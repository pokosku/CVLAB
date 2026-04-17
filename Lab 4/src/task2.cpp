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

        if(left_chosen && right_chosen)
            break;
    } 


    selected_lines.push_back(left_line);
    selected_lines.push_back(right_line);

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
    

    for( size_t i = 0; i < best_lines.size(); i++ )
    {
        cout << best_lines.at(i) << endl;
        float rho = best_lines[i][0], theta = best_lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
        line( src, pt1, pt2, Scalar(0,0,255), 1, LINE_AA);
    }

    imshow(window_name, src);
    waitKey(0);

    
    return 0;
}