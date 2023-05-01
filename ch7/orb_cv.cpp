#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <chrono>

using namespace std;
using namespace cv;

int main(int argc, char **argv) {
    if (argc != 3) {
        cout << "usage: feature extraction img1 img2" << endl;
        return 1;
    }

    // read images
    Mat img1 = imread(argv[1], IMREAD_COLOR);
    Mat img2 = imread(argv[2], IMREAD_COLOR);
    assert(img1.data != nullptr && img2.data != nullptr);

    imshow("img1", img1);
    imshow("img2", img2);
    waitKey(0);

    // initialize
    std::vector<KeyPoint> keypoints1, keypoints2;
    Mat descriptors1, descriptors2;
    Ptr<FeatureDetector> detector = ORB::create();
    Ptr<DescriptorExtractor> descriptor = ORB::create();
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");

    // step 1: detect Oriented FAST corner points
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    detector->detect(img1, keypoints1);
    detector->detect(img2, keypoints2);

    // step 2: compute BRIEF descriptor according to the corner points
    descriptor->compute(img1, keypoints1, descriptors1);
    descriptor->compute(img2, keypoints2, descriptors2);
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);

    cout << "extract ORB cost = " << time_used.count() << " seconds." << endl;

    Mat outimg1;
    // visualize key points
    drawKeypoints(img1, keypoints1, outimg1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
    imshow("ORB features", outimg1);
    waitKey(0);

    // step 3: match the BRIEF descriptors in the two images, using Hamming distance
    vector<DMatch> matches;
    t1 = chrono::steady_clock::now();
    matcher->match(descriptors1, descriptors2, matches);
    t2 = chrono::steady_clock::now();
    time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    cout << "match ORB cost = " << time_used.count() << " seconds." << endl;

    // step 4: filter out the matching points
    // find the minimum distance and maximum distance, which is the distance between the most similar and the most
    // dissimilar two sets of points, the distance between the most similar two sets of points is close to 0, and the
    // distance between the most dissimilar two sets of points is large
    // auto is equivalent to map<vector<DMatch>::iterator, double>
    auto min_max = minmax_element(matches.begin(), matches.end(),
                                  [](const DMatch &m1, const DMatch &m2) { return m1.distance < m2.distance; });
    
    double min_dist = min_max.first->distance;
    double max_dist = min_max.second->distance;

    printf("-- Max dist : %f \n", max_dist);
    printf("-- Min dist : %f \n", min_dist);

    // when the distance between the descriptors is greater than twice the minimum distance, the match is considered
    // wrong. But sometimes the minimum distance will be very small, and an empirical value of 30 is set as the lower
    // limit.
    std::vector<DMatch> good_matches;
    for (int i = 0; i < descriptors1.rows; i++) {
        if (matches[i].distance <= max(2 * min_dist, 30.0)) {
            good_matches.push_back(matches[i]);
        }
    }

    // print to see results
    for (DMatch m : good_matches) {
        cout << "good matches: distance = " << m.distance << ", trainIdx = " << m.trainIdx << ", queryIdx = "
             << m.queryIdx << endl;
    }

    // step 5: draw the matching results
    Mat img_match;
    Mat img_goodmatch;
    drawMatches(img1, keypoints1, img2, keypoints2, matches, img_match);
    drawMatches(img1, keypoints1, img2, keypoints2, good_matches, img_goodmatch);
    imshow("all matches", img_match);
    imshow("good matches", img_goodmatch);
    waitKey(0);

    return 0;
}