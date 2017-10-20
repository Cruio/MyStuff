// img.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include "opencv2/core/core.hpp"
#include <opencv2/highgui/highgui.hpp>


using namespace std;
using namespace cv;

void loadpicture();
void equa();


Mat img;


int main()
{
	loadpicture();
	equa();

	return 0;
}

void loadpicture() {
	img = imread("MyPic.jpg");
	namedWindow("image", CV_WINDOW_AUTOSIZE);
	imshow("image", img);

}

void equa() {


	Mat new_image = img.clone();

	if (img.data && !img.empty()) {
		for (size_t y = 0; y < img.rows; ++y) {
			for (size_t x = 0; x < img.cols; ++x) {
				
			}
		}
		namedWindow("histogram equalization", CV_WINDOW_AUTOSIZE);
		imshow("histogram equalization", img);
		waitKey(0);
	}
}