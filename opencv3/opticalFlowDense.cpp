#include "pch.h"
#include "opticalFlowDense.h"

using namespace cv;
using namespace std;

void optical_flow_dense(){
	VideoCapture cap(0);
	if (!cap.isOpened())
		cerr << "Unable to open camera" << endl;

	Mat frame1, prvs;
	cap >> frame1;
	cvtColor(frame1, prvs, COLOR_BGR2GRAY);

	while(true){
		Mat frame2, next;
		cap >> frame2;
		if (frame2.empty())
			break;
		cvtColor(frame2, next, COLOR_BGR2GRAY);

		Mat flow(prvs.size(), CV_32FC2);
		//calcOpticalFlowPyrLK(prvs, next, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
		calcOpticalFlowFarneback(prvs, next, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
		//void cv::calcOpticalFlowFarneback(InputArray _prev0, InputArray _next0,
		//	OutputArray _flow0, double pyr_scale, int levels, int winsize,
		//	int iterations, int poly_n, double poly_sigma, int flags)
		//	// 参数说明如下：
		//	// _prev0：输入前一帧图像
		//	// _next0：输入后一帧图像
		//	// _flow0：输出的光流
		//	// pyr_scale：金字塔上下两层之间的尺度关系
		//	// levels：金字塔层数
		//	// winsize：均值窗口大小，越大越能denoise并且能够检测快速移动目标，但会引起模糊运动区域
		//	// iterations：迭代次数
		//	// poly_n：像素领域大小，一般为5，7等
		//	// poly_sigma：高斯标注差，一般为1-1.5
		//	// flags：计算方法。主要包括OPTFLOW_USE_INITIAL_FLOW和OPTFLOW_FARNEBACK_GAUSSIAN
		
		Mat flow_parts[2];
		split(flow, flow_parts);
		Mat magnitude, angle, magn_norm;
		cartToPolar(flow_parts[0], flow_parts[1], magnitude, angle, true);
		normalize(magnitude, magn_norm, 0.0f, 1.0f, NORM_MINMAX);
		angle *= (1.f / 360.f)*(180.f / 255.f);

		//build hsv image
		Mat _hsv[3], hsv, hsv8, bgr;
		_hsv[0] = angle;
		_hsv[1] = Mat::ones(angle.size(), CV_32F);
		_hsv[2] = magn_norm;
		merge(_hsv, 3, hsv);
		hsv.convertTo(hsv8, CV_8U, 255.0);
		cvtColor(hsv8, bgr, COLOR_HSV2BGR);

		imshow("frame2", bgr);

		if (waitKey(30) == 'q' || waitKey(30) == 27)
			break;

		prvs = next;
	}
}