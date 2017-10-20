// img.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include "opencv2/core/core.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace std;
using namespace cv;

void loadpicture();
void histogram();
void histcounter();
void equa();

int histo[];
int histo2[];
int histogramcount[];
Mat img;



int main()
{
	loadpicture();
	histogram();
	histcounter();
	equa();

	return 0;
}

void loadpicture() {
	img = imread("MyPic.jpg");
	namedWindow("Input image", CV_WINDOW_AUTOSIZE);
	imshow("Input image", img);

}

void histogram(){

	// initialize all intensity values to 0
	for (int i = 0; i < 256; i++)
	{
		histo[i] = 0;
	}

	// calculate the no of pixels for each intensity values
	for (int y = 0; y < img.rows; y++)
		for (int x = 0; x < img.cols; x++)
			histo[(int)img.at<uchar>(y, x)]++;

}

void histcounter()
{
	histogramcount[0] = histo2[0];

	for (int i = 1; i < 256; i++)
	{
		histogramcount[i] = histo2[i] + histogramcount[i - 1];
	}
}

void equa() {


	Mat new_image = img.clone();


		
		namedWindow("histogram equalization", CV_WINDOW_AUTOSIZE);
		imshow("histogram equalization", img);
		waitKey(0);
	
}