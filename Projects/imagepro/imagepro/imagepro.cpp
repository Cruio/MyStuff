// imagepro.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using std::cout;
using std::cin;
using std::endl;

using namespace cv;

void imhist(Mat image, int histogram[])
{

	// initialize all intensity values to 0
	for (int i = 0; i < 256; i++)
	{
		histogram[i] = 0;
	}

	// calculate the no of pixels for each intensity values
	for (int y = 0; y < image.rows; y++)
		for (int x = 0; x < image.cols; x++)
			histogram[(int)image.at<uchar>(y, x)]++;

}

void cumhist(int histogram[], int cumhistogram[])
{
	cumhistogram[0] = histogram[0];

	for (int i = 1; i < 256; i++)
	{
		cumhistogram[i] = histogram[i] + cumhistogram[i - 1];
	}
}




int main()
{
	// Load the image
	Mat image = imread("Mypic.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	// Generate the histogram
	int histogram[256];
	imhist(image, histogram);

	// Caluculate the size of image
	int size = image.rows * image.cols;
	float alpha = 255.0 / size;

	// Calculate the probability of each intensity
	float PrRk[256];
	for (int i = 0; i < 256; i++)
	{
		PrRk[i] = (double)histogram[i] / size;
	}

	// Generate cumulative frequency histogram
	int cumhistogram[256];
	cumhist(histogram, cumhistogram);

	// Scale the histogram
	int Sk[256];
	for (int i = 0; i < 256; i++)
	{
		Sk[i] = cvRound((double)cumhistogram[i] * alpha);
	}


	// Generate the equlized histogram
	float PsSk[256];
	for (int i = 0; i < 256; i++)
	{
		PsSk[i] = 0;
	}

	for (int i = 0; i < 256; i++)
	{
		PsSk[Sk[i]] += PrRk[i];
	}

	int final[256];
	for (int i = 0; i < 256; i++)
		final[i] = cvRound(PsSk[i] * 255);


	// Generate the equlized image
	Mat new_image = image.clone();

	for (int y = 0; y < image.rows; y++)
		for (int x = 0; x < image.cols; x++)
			new_image.at<uchar>(y, x) = saturate_cast<uchar>(Sk[image.at<uchar>(y, x)]);

	// Display the original Image
	namedWindow("Original Image");
	imshow("Original Image", image);

	// Display the original Histogram


	// Display equilized image
	namedWindow("Equilized Image");
	imshow("Equilized Image", new_image);

	// Display the equilzed histogram


	waitKey();
	return 0;
}