#include <opencv2/opencv.hpp> // for all the opencv2 headers
#include <string> // for std::string
#include <iostream> // for std::cout, std::endl

using namespace std;

// assign an image
string image_file = "./distorted.png";

int main(int argc, char** argv) {
    // This is to implement undistortation of an image.
    // OpenCV provides built-in methods to do this.

    // distoration parameters
    double k1 = -0.28340811, k2 = 0.07395907, p1 = 0.00019359, p2 = 1.76187114e-05;
    // camera intrinsics
    double fx = 458.654, fy = 457.296, cx = 367.215, cy = 248.375;

    // read image
    cout << "Reading image..." << image_file << endl;
    cv::Mat image = cv::imread(image_file, 0); // grey image 8UC1, color image is 8UC3 -> 16
    int rows = image.rows, cols = image.cols;
    cv::Mat image_undistort = cv::Mat(rows, cols, CV_8UC1); // undistorted image

    // calculate the undistorted image
    for (int v=0; v<rows; v++) {
        for (int u=0; u<cols; u++) {
            // calculate the undistorted pixel value
            double x = (u-cx)/fx, y = (v-cy)/fy;
            double r = sqrt(x*x + y*y);
            double x_distorted = x*(1+k1*r*r+k2*r*r*r*r) + 2*p1*x*y + p2*(r*r+2*x*x);
            double y_distorted = y*(1+k1*r*r+k2*r*r*r*r) + p1*(r*r+2*y*y) + 2*p2*x*y;
            double u_distorted = fx*x_distorted + cx;
            double v_distorted = fy*y_distorted + cy;

            // bilinear interpolation
            if (u_distorted >= 0 && v_distorted >= 0 && u_distorted < cols && v_distorted < rows) {
                image_undistort.at<uchar>(v,u) = image.at<uchar>(v_distorted, u_distorted);
            }
            else {
                image_undistort.at<uchar>(v,u) = 0;
            }

        }
    }

    // show image
    cv::imshow("distorted", image);
    cv::imshow("undistorted", image_undistort);
    cv::waitKey();
    
    return 0;
}
