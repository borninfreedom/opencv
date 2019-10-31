#include "pch.h"
#include "hough.h"
using namespace std;
using namespace cv;

Mat g_srcImage, g_midImage, g_dstImage;
vector<Vec4i> g_lines;
int g_nthreshold = 100;

static void on_HoughLines(int, void*) {
	cout << "calling on_hough" << endl;
	Mat dstImage = g_dstImage.clone();
	Mat midImage = g_midImage.clone();
	vector<Vec4i> mylines;
	cout << "mylines : " << endl;
	
	HoughLinesP(midImage, mylines, 1, CV_PI / 180, g_nthreshold+1, 50, 10);
	/*for (auto val : mylines) {
		cout << val << endl;
	}*/
	for (size_t i = 0; i < mylines.size(); i++) {
		Vec4i l = mylines[i];
		line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(23, 180, 55), 1, LINE_AA);

	}
	imshow("houghp", dstImage);
}

void houghlines() {
	Mat srcImage = imread("1 (83).jpg");
	pyrDown(srcImage, srcImage);
	pyrDown(srcImage, srcImage);
	Mat midImage, dstImage;
	Canny(srcImage, midImage, 50, 200, 3);
	cvtColor(midImage, dstImage, CV_GRAY2BGR);
	namedWindow("hough", WINDOW_AUTOSIZE);
	//imshow("hough", dstImage);

	vector<Vec2f> lines;
	cout << "lines : " << endl;
	for (auto val : lines) {
		cout << val << endl;
	}
	HoughLines(midImage, lines, 1, CV_PI / 180, 260, 0, 0);

	for (size_t i = 0; i < lines.size(); i++) {
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(dstImage, pt1, pt2, Scalar(155, 100, 195), 1, LINE_AA);
	}
	imshow("origin", srcImage);
	imshow("canny", midImage);
	imshow("hough", dstImage);
	waitKey(0);
}

void houghlinesp() {
	system("color 3F");

	Mat g_srcImage = imread("1 (83).jpg");
	pyrDown(g_srcImage, g_srcImage);
	pyrDown(g_srcImage, g_srcImage);
	imshow("origin", g_srcImage);
	namedWindow("houghp", 1);
	createTrackbar("threshold", "houghp", &g_nthreshold, 200, on_HoughLines);
	Canny(g_srcImage, g_midImage, 50, 200, 3);
	cvtColor(g_midImage, g_dstImage, COLOR_GRAY2BGR);
	on_HoughLines(g_nthreshold, 0);
	HoughLinesP(g_midImage, g_lines, 1, CV_PI / 180, 80, 50, 10);
	imshow("houghp", g_dstImage);
	waitKey(0);
	/*Mat midImage, dstImage;
	Canny(srcImage, midImage, 50, 200, 3);
	cvtColor(midImage, dstImage, COLOR_GRAY2BGR);

	vector<Vec4i> lines;
	HoughLinesP(midImage, lines, 1, CV_PI / 180, 100, 50, 10);
	for (size_t i = 0; i < lines.size(); i++) {
		Vec4i l = lines[i];
		line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186, 88, 255), 1, LINE_AA);

	}
	imshow("origin", srcImage);
	imshow("canny", midImage);
	imshow("houghp", dstImage);
	waitKey(0);*/
}

void houghcircles() {
	Mat srcImage = imread("2 (1).jpg");
	Mat midImage, dstImage;
	//pyrDown(srcImage, srcImage);
//	pyrDown(srcImage, srcImage);
	imshow("origin", srcImage);
	cvtColor(srcImage, midImage, COLOR_BGR2GRAY);
	GaussianBlur(midImage, midImage, Size(9, 9), 2, 2);
	vector<Vec3f> circles;
	HoughCircles(midImage, circles, HOUGH_GRADIENT, 1.1, 10, 200, 100, 0, 0);
	for (size_t i = 0; i < circles.size(); i++) {
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]); 
		circle(srcImage, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		circle(srcImage, center, radius, Scalar(155, 50, 255), 3, 8, 0);

	}
	imshow("houghc", srcImage);
	waitKey(0);
}