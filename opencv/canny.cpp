
#include "pch.h"
#include "canny.h"

using namespace cv;
using namespace std;

Mat g_src, g_src1, g_dst, g_edge, g_gray;
int g_nLowThres = 10;
int g_nUpThres = 30;
int g_nRatio = 0;

static void on_TuneCanny(int, void*) {
	if (getTrackbarPos("固定阈值比", "tune canny") == 1) {
		setTrackbarPos("低阈值", "tune canny", g_nLowThres);
		setTrackbarPos("高阈值", "tune canny", getTrackbarPos("低阈值", "tune canny") * 3);
	}
	else {
		
		setTrackbarPos("低阈值", "tune canny", g_nLowThres);
		setTrackbarPos("高阈值", "tune canny", g_nUpThres);
	}
	Mat edge = g_edge;
	Mat dst = g_dst;
	Mat src1 = g_src1;
	Mat gray = g_gray;
	cvtColor(src1, gray, COLOR_BGR2GRAY);
	blur(gray, edge, Size(3, 3));
	/*Canny(edge, edge, g_nLowThres, g_nLowThres * 3, 3);*/
	Canny(edge, edge, g_nLowThres, g_nUpThres, 3);
	dst = Scalar::all(0);
	src1.copyTo(dst, edge);
	imshow("tune canny", dst);
	//waitKey(0);
}

void tune_canny() {
	namedWindow("tune canny", 1);
	
	g_src = imread("2 (2).jpg");
	pyrUp(g_src, g_src);
	//pyrDown(g_src, g_src);
	//pyrDown(g_src, g_src);
	g_src1 = g_src.clone();
	g_dst.create(g_src1.size(), g_src1.type());
	/*
	cvtColor(g_src1, g_gray, COLOR_BGR2GRAY);
	blur(g_gray, g_edge, Size(3, 3));
	Canny(g_edge, g_edge, g_nLowThres, g_nLowThres * 3, 3);
	g_dst = Scalar::all(0);
	g_src1.copyTo(g_dst, g_edge);

	imshow("tune canny", g_dst);*/
	createTrackbar("低阈值", "tune canny", &g_nLowThres, 200, on_TuneCanny);
	createTrackbar("高阈值", "tune canny", &g_nUpThres, 200, on_TuneCanny);
	createTrackbar("固定阈值比", "tune canny", &g_nRatio, 1, on_TuneCanny);
	on_TuneCanny(g_nLowThres, 0);
	//on_FixRatio(g_nRatio, 0);
	waitKey(0);
}
void canny(bool r,int speed,bool positive) {
	namedWindow("canny", WINDOW_AUTOSIZE);
	Mat src = imread("1 (4).jpg");
	pyrDown(src, src);
	pyrDown(src, src);
	Mat src1 = src.clone();
	imshow("[origin]Canny", src);

	Mat dst, edge, gray;
	if (r == true) {
		if (positive == true) {
			for (int alpha = 0; alpha <= 220; alpha++) {
				dst.create(src1.size(), src1.type());
				cvtColor(src1, gray, COLOR_BGR2GRAY);
				blur(gray, edge, Size(3, 3));
				Canny(edge, edge, alpha, 3 * alpha, 3);
				dst = Scalar::all(0);
				src1.copyTo(dst, edge);
				cout << "Current ALPHA= " << alpha << endl;
				imshow("Canny Process", dst);
				waitKey(speed);
			}
			waitKey(5000);
			for (int alpha = 220; alpha >= 0; alpha--) {
				dst.create(src1.size(), src1.type());
				cvtColor(src1, gray, COLOR_BGR2GRAY);
				blur(gray, edge, Size(3, 3));
				Canny(edge, edge, alpha, 3 * alpha, 3);
				dst = Scalar::all(0);
				src1.copyTo(dst, edge);
				cout << "Current ALPHA= " << alpha << endl;
				imshow("Canny Process", dst);
				waitKey(speed);
			}
			waitKey(0);
		}
		if (positive == false) {
			for (int alpha = 220; alpha >= 0; alpha--) {
				dst.create(src1.size(), src1.type());
				cvtColor(src1, gray, COLOR_BGR2GRAY);
				blur(gray, edge, Size(3, 3));
				Canny(edge, edge, alpha, 3 * alpha, 3);
				dst = Scalar::all(0);
				src1.copyTo(dst, edge);
				cout << "Current ALPHA= " << alpha << endl;
				imshow("Canny Process", dst);
				waitKey(speed);
			}
			waitKey(5000);
			for (int alpha = 0; alpha <= 220; alpha++) {
				dst.create(src1.size(), src1.type());
				cvtColor(src1, gray, COLOR_BGR2GRAY);
				blur(gray, edge, Size(3, 3));
				Canny(edge, edge, alpha, 3 * alpha, 3);
				dst = Scalar::all(0);
				src1.copyTo(dst, edge);
				cout << "Current ALPHA= " << alpha << endl;
				imshow("Canny Process", dst);
				waitKey(speed);
			}
			waitKey(0);
		}
	}
	
	else
	{
		dst.create(src1.size(), src1.type());
		cvtColor(src1, gray, COLOR_BGR2GRAY);
		blur(gray, edge, Size(3, 3));
		Canny(edge, edge, 9, 27, 3);
		dst = Scalar::all(0);
		src1.copyTo(dst, edge);
		imshow("Canny Process", dst);
		waitKey(0);
	}
	
	
}

void r_canny() {
	char filename[50];
	Mat src, src1;
	Mat dst, edge, gray;
	namedWindow("origin", WINDOW_AUTOSIZE);
	for (int i = 1; i <= 141; i++) {
		sprintf_s(filename, "1 (%d).jpg", i);
		src = imread(filename);
		pyrDown(src, src);
		pyrDown(src, src);
		imshow("origin", src);
		src1 = src.clone();
		dst.create(src1.size(), src1.type());
		cvtColor(src1, gray, COLOR_BGR2GRAY);
		blur(gray, edge, Size(3, 3));
		Canny(edge, edge, 8, 24, 3);
		dst = Scalar::all(0);
		src1.copyTo(dst, edge);
		imshow("process", dst);
		cout << "Current file = " << filename << endl;
		waitKey(10);
	}
}