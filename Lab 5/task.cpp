// 6 intersections on each row
// 9 intersection on each column
// 22 mm x 22 mm squares

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/core/types.hpp>
#include <iostream>

using namespace cv;
using namespace std;


vector<vector<Point3f>> chessboard;
int board_height = 9;
int board_width = 6;
float square_side = 22.0;

void init_chessboard(int num_images){
    
    vector<Point3f> points;

    for(int i = 0; i < board_height; i++) {
        for(int j = 0; j < board_width; j++) {
            points.push_back(Point3f(j*square_side, i*square_side, 0.0f));
        }
    }
    
    chessboard = vector<vector<Point3f>>(num_images, points);
}

int main(int argc, char** argv){

    // loading dataset
    vector<String> filenames;
    
    glob("../assets/*", filenames);

    if(filenames.size() == 0){
        cerr << "couldnt read dataset" << endl;
        return -1;
    }

    vector<Mat> images;
    for(auto &filename : filenames){
        Mat img = imread(filename, IMREAD_GRAYSCALE);
        images.push_back(img);
    }
    
    cout << images.size() << " images loaded succesfully "<< endl;
    // calibration
    
    vector<vector<Point2f>> corners;
    

    for(auto &img : images){
        // finding the corners in the checkboard
        vector<Point2f> curr_corners;
        
        bool pattern_found = findChessboardCorners(img, Size(board_width,board_height),curr_corners, CALIB_CB_ADAPTIVE_THRESH);
        
        if(pattern_found){
            cornerSubPix(img, curr_corners, Size(11,11), Size(-1,-1), 
            TermCriteria(TermCriteria::COUNT + TermCriteria::EPS, 30, 0.1));
            corners.push_back(curr_corners);
        }
        /*
        cvtColor(img, img, COLOR_GRAY2BGR);
        drawChessboardCorners(img, Size(6,9), curr_corners, pattern_found);
        namedWindow("debug");
        imshow("debug",img);
        waitKey(0);
        */
    }

    // initializing the chessboard vector with as many views as the detected patterns
    int pattern_views = corners.size();
    init_chessboard(pattern_views);

    // i/o parameters for calibrateCamera
    Mat cameraMatrix, distCoeffs;
    vector<Mat> rvecs, tvecs;
    
    Size image_size = images.at(0).size();
    double rms = calibrateCamera(
        chessboard,
        corners,
        image_size,
        cameraMatrix,
        distCoeffs,
        rvecs,
        tvecs
    );    

    cout << "RMS: " << rms << endl;

    // TEST: undirstorting newly acquired image
    Mat test = imread("../test/test.jpg");

    Mat map1, map2;
    initUndistortRectifyMap(cameraMatrix, distCoeffs, Mat(), cameraMatrix, image_size, CV_16SC2, map1, map2);

    Mat undistorted;
    remap(test, undistorted, map1, map2, INTER_LINEAR);

    namedWindow("Display");
    imshow("Display", test);
    waitKey(0);

    imshow("Display", undistorted);
    waitKey(0);
    return 0;
}
