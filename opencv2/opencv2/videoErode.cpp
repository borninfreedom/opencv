#include "pch.h"
#include "videoErode.h"

using namespace cv;

void video_erode(){
	VideoCapture cap(0);
	Mat edges;

	while (1) {
		Mat frame;
		Mat dstImage;
		cap >> frame;

		Mat element = getStructuringElement(MORPH_RECT, Size(25, 25));
		erode(frame, dstImage, element);
		imshow("erode", dstImage);
		if (waitKey(30) >= 0) break;
	}
}