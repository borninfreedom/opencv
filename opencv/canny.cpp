
#include "pch.h"

using namespace cv;
using namespace std;

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