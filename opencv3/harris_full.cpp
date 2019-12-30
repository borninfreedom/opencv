#include "pch.h"
#include "harris_full.h"
using namespace cv;

#define WINDOW_NAME1 "window1"
#define WINDOW_NAME2 "window2"

Mat g_srcImgHarris, g_midImgHarris, g_grayImgHarris;
int g_nThreshHarris = 70;
int g_nMaxThreshHarris = 175;

void on_CornerHarris(int, void*);

void harris_full(){
	g_srcImgHarris = imread("1 (197).jpg");
	pyrDown(g_srcImgHarris, g_srcImgHarris);
	pyrDown(g_srcImgHarris, g_srcImgHarris);
	if (!g_srcImgHarris.data) { std::cout << "file no ok" << std::endl; }
	imshow("origin", g_srcImgHarris);
	g_midImgHarris = g_srcImgHarris.clone();

	cvtColor(g_srcImgHarris, g_grayImgHarris, COLOR_BGR2GRAY);
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	createTrackbar("thresh", WINDOW_NAME1, &g_nThreshHarris, g_nMaxThreshHarris, on_CornerHarris);
	on_CornerHarris(0, 0);
	waitKey(0);
}

void on_CornerHarris(int,void*){
	Mat dstImage;
	Mat normImage;
	Mat scaledImage;

	dstImage = Mat::zeros(g_srcImgHarris.size(), CV_32FC1);
	g_midImgHarris = g_srcImgHarris.clone();

	cornerHarris(g_grayImgHarris, dstImage, 2, 3, 0.04, BORDER_DEFAULT);
	normalize(dstImage, normImage, 0, 255, NORM_MINMAX, CV_32FC1);
	convertScaleAbs(normImage, scaledImage);

	for(int j=0;j<normImage.rows;j++)
	{
		for(int i=0;i<normImage.cols;i++){
			if((int)normImage.at<float>(j,i)>g_nThreshHarris+80){
				circle(g_srcImgHarris, Point(i, j), 5, Scalar(10, 10, 255), 2, 8, 0);
				circle(scaledImage, Point(i, j), 5, Scalar(0, 10, 255), 2, 8, 0);
			}
		}
	}
	imshow(WINDOW_NAME1, g_srcImgHarris);
	imshow(WINDOW_NAME2, scaledImage);
}