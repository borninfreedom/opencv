#include "pch.h"
#include "videoCanny.h"

using namespace cv;

void video_canny(){
	VideoCapture cap(0);
	Mat edges;

	while(1){
		Mat frame;
		cap >> frame;

		cvtColor(frame, edges, CV_BGR2GRAY);

		blur(edges, edges, Size(7, 7));

		Canny(edges, edges, 30, 90, 3);
		imshow("canny", edges);
		if(waitKey(30)>=0) break;
	}
}