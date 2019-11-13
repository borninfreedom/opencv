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






Mat g_srcHoughCircle, g_midHoughCircle, g_dstHoughCircle;
static int g_nDP = 11;
static int g_nUpThresHough = 200;
static int g_nSumThres = 100;
static int g_nMinDist = 10;
static char g_cFileName[50];
static int g_nFileIndex = 1;

static void on_HoughCircle(int, void*) {
	Mat src, mid, dst;
	src=g_srcHoughCircle.clone();	//要注意是clone（），如果直接用=，是把两个变量的内存地址赋值。
//	pyrUp(src, src);
	pyrDown(src, src);
	pyrDown(src, src);
	pyrDown(src, src);
	imshow("原始图像", g_srcHoughCircle);
	cvtColor(src, mid, COLOR_BGR2GRAY);
	GaussianBlur(mid, mid, Size(9, 9), 2, 2);
	
	vector<Vec3f> circles;
	HoughCircles(mid, circles, HOUGH_GRADIENT, g_nDP/10.0==0?1:(g_nDP/10.0), g_nMinDist == 0?1:g_nMinDist, g_nUpThresHough==0?1:g_nUpThresHough, g_nSumThres==0?1:g_nSumThres, 0, 0);

	for (size_t i = 0; i < circles.size(); i++) {
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		circle(src, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		circle(src, center, radius, Scalar(155, 50, 255), 3, 8, 0);
	}
	imshow("霍夫圆检测调参软件", src);
}

static void on_ChoseFile(int, void*) {
//	if (g_nFileIndex == 60)	g_nFileIndex = 61;
	cout << g_cFileName << endl;
	sprintf_s(g_cFileName, "5 (%d).jpg", g_nFileIndex==0?1:g_nFileIndex);
	g_srcHoughCircle = imread(g_cFileName);
	on_HoughCircle(g_nDP, 0);
}

void houghcircles() {

	Mat srcImage = imread("4 (1).jpg");
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

void tune_hough_circle() {
	//cout << g_nFileIndex;
	namedWindow("霍夫圆检测调参软件", WINDOW_NORMAL);
	namedWindow("原始图像", WINDOW_NORMAL);
	g_srcHoughCircle = imread("5 (1).jpg");
	createTrackbar("分辨率/10", "霍夫圆检测调参软件", &g_nDP, 50, on_HoughCircle);
	createTrackbar("Canny阈值", "霍夫圆检测调参软件", &g_nUpThresHough, 500, on_HoughCircle);
	createTrackbar("累加器阈值", "霍夫圆检测调参软件", &g_nSumThres, 500, on_HoughCircle);
	createTrackbar("圆心最小距离", "霍夫圆检测调参软件", &g_nMinDist, 100, on_HoughCircle);
	createTrackbar("选择图片", "霍夫圆检测调参软件", &g_nFileIndex, 100, on_ChoseFile);
	on_HoughCircle(g_nDP, 0);
	on_ChoseFile(g_nFileIndex, 0);
	waitKey(0);

}

Mat g_frame, g_frame1, g_midFrame;
int g_nDPVHC = 10;
int g_nCannyThresVHC = 100;
int g_nSumThresVHC = 100;

static void on_VideoHoughCircle(int,void*) {
	g_nDPVHC = getTrackbarPos("分辨率/10", "视频流霍夫圆检测调参");
	g_nCannyThresVHC = getTrackbarPos("Canny阈值", "视频流霍夫圆检测调参");
	g_nSumThresVHC = getTrackbarPos("累加器阈值", "视频流霍夫圆检测调参");
}
void video_hough_circle() {
	namedWindow("视频流霍夫圆检测调参", 1);
	createTrackbar("分辨率/10", "视频流霍夫圆检测调参", &g_nDPVHC, 200, on_VideoHoughCircle);
	createTrackbar("Canny阈值", "视频流霍夫圆检测调参", &g_nCannyThresVHC, 500, on_VideoHoughCircle);
	createTrackbar("累加器阈值", "视频流霍夫圆检测调参", &g_nSumThresVHC, 500, on_VideoHoughCircle);

	VideoCapture cap;
	cap.open("video.mp4");
	for (;;) {
		cap >> g_frame;
	//	pyrDown(g_frame, g_frame);
		cvtColor(g_frame, g_midFrame, COLOR_BGR2GRAY);
		GaussianBlur(g_midFrame, g_midFrame, Size(9, 9), 2, 2);

		vector<Vec3f> circles;
		HoughCircles(g_midFrame,circles, HOUGH_GRADIENT, 1, g_nDPVHC/10.0==0?1: g_nDPVHC/10.0, g_nCannyThresVHC==0?1:g_nCannyThresVHC, g_nSumThresVHC==0?1:g_nSumThresVHC, 0, 0);
		for (size_t i = 0; i < circles.size(); i++) {
			Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
			int radius = cvRound(circles[i][2]);
			circle(g_frame, center, 3, Scalar(0, 255, 0), -1, 8, 0);
			circle(g_frame, center, radius, Scalar(155, 50, 255), 3, 8, 0);
		}
		imshow("视频流霍夫圆检测调参", g_frame);

		on_VideoHoughCircle(g_nCannyThresVHC, 0);

		if(waitKey(20)==27) break;
	}

}

//static void on_HoughCircle(int, void*) {
//	Mat src, mid, dst;
//	src = g_srcHoughCircle.clone();	//要注意是clone（），如果直接用=，是把两个变量的内存地址赋值。
////	pyrUp(src, src);
//	imshow("原始图像", g_srcHoughCircle);
//	cvtColor(src, mid, COLOR_BGR2GRAY);
//	GaussianBlur(mid, mid, Size(9, 9), 2, 2);
//
//	vector<Vec3f> circles;
//	HoughCircles(mid, circles, HOUGH_GRADIENT, g_nDP / 10.0 == 0 ? 1 : (g_nDP / 10.0), g_nMinDist == 0 ? 1 : g_nMinDist, g_nUpThresHough == 0 ? 1 : g_nUpThresHough, g_nSumThres == 0 ? 1 : g_nSumThres, 0, 0);
//
//	for (size_t i = 0; i < circles.size(); i++) {
//		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
//		int radius = cvRound(circles[i][2]);
//		circle(src, center, 3, Scalar(0, 255, 0), -1, 8, 0);
//		circle(src, center, radius, Scalar(155, 50, 255), 3, 8, 0);
//	}
//	imshow("霍夫圆检测调参软件", src);
//}
//
//void videoCanny() {
//	namedWindow("video", WINDOW_AUTOSIZE);
//	VideoCapture cap;
//	cap.open("video.mp4");
//	Mat frame;
//	Mat frame1, dst, edge, gray;
//
//	for (;;) {
//		cap >> frame;
//		if (frame.empty())	break;
//		imshow("video", frame);
//		frame1 = frame.clone();
//		dst.create(frame1.size(), frame1.type());
//		cvtColor(frame1, gray, COLOR_BGR2GRAY);
//		blur(gray, edge, Size(3, 3));
//		Canny(edge, edge, 10, 30, 3);
//		dst = Scalar::all(0);
//		frame1.copyTo(dst, edge);
//		imshow("canny video", dst);
//		if (waitKey(30) >= 0)	break;
//	}
//}