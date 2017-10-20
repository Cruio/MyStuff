

#include "stdafx.h"
#include "opencv2\opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;



int main(int argc, char** argv)
{
	VideoCapture cap(0);
	if (!cap.isOpened()) {
		cout << "cam could not open" << endl;
		return -1;
	}

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
		params.maxThreshold = 255;

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

		




	return 0;
}

