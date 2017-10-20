// OpenCVBlobTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "opencv2/opencv.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

#include <iostream>
using namespace std;
using namespace cv;
int main(int argc, char** argv)
{
		//Mat im = imread("blob.JPG", IMREAD_GRAYSCALE);
		//cv::Mat invim = cv::Scalar::all(255) - im;
		//// Set up the detector with default parameters.
		//vector<KeyPoint> keypoints;
		//Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create();
		//detector->detect(invim, keypoints);
		//// Detect blobs.
		//

		//// Draw detected blobs as red circles.
		//// DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures the size of the circle corresponds to the size of blob
		//Mat im_with_keypoints;
		//drawKeypoints(invim, keypoints, im_with_keypoints, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

		//// Show blobs
		//imshow("keypoints", im_with_keypoints);
		//waitKey(0);
	VideoCapture cap;
	// open the default camera, use something different from 0 otherwise;
	// Check VideoCapture documentation.
	if (!cap.open(1))
		return 0;
	for (;;)
	{
		Mat frame;
		Mat bwFrame;
		cap >> frame;
		if (frame.empty()) break; // end of video stream
		cvtColor(frame, bwFrame, cv::COLOR_RGB2GRAY);
		Mat biFrame;
		cv::threshold(bwFrame, biFrame, 100.0, 255.0, THRESH_BINARY);
		vector<KeyPoint> keypoints;
		SimpleBlobDetector::Params params;
		// Change thresholds
		params.minThreshold = 10;
		params.maxThreshold = 200;

		// Filter by Area.
		params.filterByArea = true;
		params.minArea = 1000;
		//params.maxArea = 2500;

		// Filter by Circularity
		params.filterByCircularity = false;
		params.minCircularity = 0.1f;

		// Filter by Convexity
		params.filterByConvexity = false;
		params.minConvexity = 0.0f;

		// Filter by Inertia
		params.filterByInertia = false;
		params.minInertiaRatio = 0.01f;
		Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);
		detector->detect(bwFrame, keypoints);
		Mat frameWithKeypoints;
		drawKeypoints(frame, keypoints, frameWithKeypoints, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
		imshow("this is you, smile! :)", frameWithKeypoints);
		if (waitKey(10) == 27) break; // stop capturing by pressing ESC 
	}
	// the camera will be closed automatically upon exit
	// cap.close();
	return 0;
}

