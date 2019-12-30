#include "pch.h"
#include "video.h"
using namespace cv;
void videoCanny() {
	namedWindow("video", WINDOW_AUTOSIZE);
	VideoCapture cap;
	cap.open("video.mp4");
	Mat frame;
	Mat frame1, dst, edge, gray;

	for (;;) {
		cap >> frame;
		if (frame.empty())	break;
		imshow("video", frame);
		frame1 = frame.clone();
		dst.create(frame1.size(), frame1.type());
		cvtColor(frame1, gray, COLOR_BGR2GRAY);
		blur(gray, edge, Size(3, 3));
		Canny(edge, edge, 10, 30, 3);
		dst = Scalar::all(0);
		frame1.copyTo(dst, edge);
		imshow("canny video", dst);
		if (waitKey(30) >= 0)	break;
	}
}

//void r_canny() {
//	char filename[50];
//	Mat src, src1;
//	Mat dst, edge, gray;
//	namedWindow("origin", WINDOW_AUTOSIZE);
//	for (int i = 1; i <= 141; i++) {
//		sprintf_s(filename, "1 (%d).jpg", i);
//		src = imread(filename);
//		pyrDown(src, src);
//		pyrDown(src, src);
//		imshow("origin", src);
//		src1 = src.clone();
//		dst.create(src1.size(), src1.type());
//		cvtColor(src1, gray, COLOR_BGR2GRAY);
//		blur(gray, edge, Size(3, 3));
//		Canny(edge, edge, 8, 24, 3);
//		dst = Scalar::all(0);
//		src1.copyTo(dst, edge);
//		imshow("process", dst);
//		cout << "Current file = " << filename << endl;
//		waitKey(10);
//	}
//}