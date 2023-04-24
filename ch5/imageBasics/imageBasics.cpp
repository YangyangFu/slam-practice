#include <iostream>
#include <chrono> // standard c++ 11 library
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

int main(int argc, char** argv) {
    // read argv[1] image
    cv::Mat image;
    image = cv::imread(argv[1]); // cv::imread() read image from argv[1] and store it in image

    // check if image is read successfully
    if (image.data == nullptr) { // file might not exist
        cerr << "File " << argv[1] << " does not exist." << endl;
        return 0;
    }

    // print image info
    cout << "Image width: " << image.cols << ", height: " << image.rows << ", channels: " << image.channels() << endl;
    cv::imshow("image", image); // show image
    cv::waitKey(0); // wait for a key to be pressed

    // check image type
    cout << "CV_8UC1: " << CV_8UC1 << endl;
    cout << "CV_8UC3: " << CV_8UC3 << endl;
    cout << "Image type: " << image.type() << endl;
    if (image.type() != CV_8UC1 && image.type() != CV_8UC3) {
        // image type is not 8UC1 or 8UC3
        cout << "Please input a color or gray image." << endl;
        return 0;
    }

    // traverse image: the same method can be used to randomly access pixel value
    // use std::chrono to measure time
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    for (size_t y = 0; y<image.rows; y++) {
        // use cv::Mat::ptr to get the pointer of row y
        unsigned char* row_ptr = image.ptr<unsigned char>(y); // row_ptr is the head pointer of row y
        // traverse row y
        for (size_t x=0; x<image.cols; x++) {
            // access pixel value at (y,x)
            unsigned char *data_ptr = &row_ptr[x*image.channels()]; // data_ptr point to the pixel value at (y,x)
            // output each channel of pixel, if image is gray, there is only one channel
            for (int c=0; c!=image.channels(); c++) {
                unsigned char data = data_ptr[c]; // data is the value of c-th channel of pixel (y,x)
            }
        }
    }

    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2-t1);
    cout << "Traversal time: " << time_used.count() << " seconds." << endl;

    // copy image
    // assign image to another variable does not copy the data
    cv::Mat image_another = image;

    // modify image_another will also change the data of image
    image_another(cv::Rect(0,0,100,100)).setTo(0); // set the top-left corner of image_another to 0
    cv::imshow("image", image);
    cv::waitKey(0);

    // use clone to copy data
    cv::Mat image_clone = image.clone();
    image_clone(cv::Rect(0,0,100,100)).setTo(255);
    cv::imshow("image", image);
    cv::imshow("image_clone", image_clone);
    cv::waitKey(0);

    // other operation can be referred to opencv official document
    cv::destroyAllWindows();

    // final return
    return 0;
}