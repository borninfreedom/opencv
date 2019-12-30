#include "pch.h"
#include "videoBlur.h"

using namespace cv;

void video_blur(){
	VideoCapture cap(0);
	Mat edges;

	while (1) {
		Mat frame;
		Mat dstImage;
		cap >> frame;

		//cvtColor(frame, edges, CV_BGR2GRAY);

		blur(frame, dstImage, Size(20, 20));

	//	Canny(edges, edges, 30, 90, 3);
		imshow("blur", dstImage);
		if (waitKey(30) >= 0) break;
	}
}