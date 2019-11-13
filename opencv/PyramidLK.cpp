#include "pch.h"
#include "PyramidLK.h"
using namespace std;

static const int MAX_CORNERS = 1000;
void help() {

}
void PyramidLK() {
	cv::Mat imgA = cv::imread("∆Â≈Ã (1).jpg");
	cv::Mat imgB = cv::imread("∆Â≈Ã (1).jpg");
	
	cv::Mat imgC = cv::imread("∆Â≈Ã (1).jpg");
//	pyrDown(imgA, imgA);
//	pyrDown(imgA, imgA);
	//pyrDown(imgA, imgA);
//	pyrDown(imgB, imgB);
	//pyrDown(imgB, imgB);
//	pyrDown(imgB, imgB);
//	pyrDown(imgC, imgC);
	//pyrDown(imgC, imgC);
//	pyrDown(imgC, imgC);
	cv::cvtColor(imgA, imgA, cv::COLOR_BGR2GRAY);
	cv::cvtColor(imgB, imgB, cv::COLOR_BGR2GRAY);
	cv::cvtColor(imgC, imgC, cv::COLOR_BGR2GRAY);
	cv::Size img_sz = imgA.size();
	int win_size = 30;
	vector<cv::Point2f> cornersA, cornersB;
	const int MAX_CORNERS = 500;
	cv::goodFeaturesToTrack(
		imgA,
		cornersA,
		MAX_CORNERS,
		0.01,
		5,
		cv::noArray(),
		3,
		false,
		0.04
	);
	cv::cornerSubPix(
		imgA,
		cornersA,
		cv::Size(win_size, win_size),
		cv::Size(-1, -1),
		cv::TermCriteria(
			cv::TermCriteria::MAX_ITER | cv::TermCriteria::EPS,
			20,
			0.03
		)
	);

	vector<uchar> features_found;
	cv::calcOpticalFlowPyrLK(
		imgA,
		imgB,
		cornersA,
		cornersB,
		features_found,
		cv::noArray(),
		cv::Size(win_size * 2 + 1, win_size * 2 + 1),
		5,
		cv::TermCriteria(
			cv::TermCriteria::MAX_ITER | cv::TermCriteria::EPS,
			20,
			0.3
		)
	);

	for (int i = 0; i < (int)cornersA.size(); i++) {
		if(!features_found[i])
			continue;
		line(imgC, cornersA[i], cornersB[i], cv::Scalar(0, 255, 0), 2, cv::LINE_AA);
	}
	cv::imshow("imageA", imgA);
	cv::imshow("imageB", imgB);
	cv::imshow("LK opetical flow example", imgC);
	cv::waitKey(0);
	 
	
}