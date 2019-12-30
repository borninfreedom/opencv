#include "pch.h"
#include "pingpang_detect.h"
using namespace cv;
using namespace std;

void pingpang_detect_callback(int, void*);

static int g_nReso = 11;
static int g_nCannyThresh = 90;
static int g_nSumThresh = 90;

void pingpang_detect(){

	namedWindow("pingpang_detect", 1);
	createTrackbar("resolution", "pingpang_detect", &g_nReso, 200, pingpang_detect_callback);
	createTrackbar("CannyThresh", "pingpang_detect", &g_nCannyThresh, 500, pingpang_detect_callback);
	createTrackbar("SumThresh", "pingpang_detect", &g_nSumThresh, 500, pingpang_detect_callback);

	VideoCapture cap;
	cap.open(0);
	if(!cap.isOpened()){
		cap.open(-1);
	}
	if(!cap.isOpened()){
		cout << "error";
	}

	Mat frame;
	Mat mid_frame;
	Mat dst_frame;

	for(;;){
		cap >> frame;
		if (frame.empty())	break;
		cvtColor(frame, mid_frame, COLOR_BGR2GRAY);
		GaussianBlur(mid_frame, mid_frame, Size(9, 9), 2, 2);

		vector<Vec3f> circles;
		HoughCircles(
			mid_frame,
			circles,
			HOUGH_GRADIENT,
			(g_nReso / 10.0 == 0 ? 1 : g_nReso / 10.0),
			10,
			(g_nCannyThresh == 0 ? 1 : g_nCannyThresh),
			(g_nSumThresh == 0 ? 1 : g_nSumThresh),
			0,
			0
		);

		for(size_t i=0;i<circles.size();i++){
			Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
			int radius = cvRound(circles[i][2]);
			circle(frame, center, 3, Scalar(0, 255, 0), 3, 8, 0);
			circle(frame, center, radius, Scalar(155, 50, 255), 3, 8, 0);
		}
		imshow("pingpang_detect", frame);
		if (waitKey(5) == 27)	break;
	}

	waitKey(0);
}

void pingpang_detect_callback(int, void*){

}