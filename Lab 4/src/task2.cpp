#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void draw_lane_area(Mat src, vector<Vec2f> lane){
    float rho1 = lane[0][0], theta1 = lane[0][1];
    float rho2 = lane[1][0], theta2 = lane[1][1];

    Mat A = Mat({1,2}, {1,2});
}

int main(int argc, char** argv){

    Mat src, src_gray;
    Mat dst, cdst, detected_edges;
    src = imread("../street_scene.png");
    

    cvtColor(src, src_gray, COLOR_BGR2GRAY); 

    threshold(src_gray,src_gray, 250, 255, THRESH_BINARY);

    GaussianBlur(src_gray, detected_edges, Size(3,3), 1.5, 1.5);

    erode(detected_edges, detected_edges, Mat());

    Canny(detected_edges, dst, 50, 200, 3);

    
    cvtColor(dst, cdst, COLOR_GRAY2BGR);
    


    vector<Vec2f> lines;
    HoughLines(dst, lines, 1, CV_PI/180, 50, 0, 0);
    
    vector<Vec2f> chosen_lines;
    
    float orientation = 0.0;
    bool done = false;
   
    for( size_t i = 0; i < lines.size() and !done; i++)
    {
        float rho = lines[i][0], theta = lines[i][1];
        
        if(((theta > ((CV_PI/5) + orientation)) and (theta <(CV_PI/3) + orientation)) and orientation < CV_PI){
            chosen_lines.push_back(lines.at(i));
            Point pt1, pt2;
            cout << rho <<" "<< theta<<endl;
            double a = cos(theta), b = sin(theta);
            double x0 = a*rho, y0 = b*rho;
            pt1.x = cvRound(x0 + 1000*(-b));
            pt1.y = cvRound(y0 + 1000*(a));
            pt2.x = cvRound(x0 - 1000*(-b));
            pt2.y = cvRound(y0 - 1000*(a));
            line( src, pt1, pt2, Scalar(0,0,255), 1, LINE_AA);
            orientation += CV_PI/2;
        }
        done = orientation == CV_PI;
    }




    namedWindow("Edges");
    imshow("Edges", src);


    waitKey(0);
    return 0;
}