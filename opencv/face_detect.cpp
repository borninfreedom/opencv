#include "pch.h"
#include "face_detect.h"

using namespace std;
using namespace cv;

String face_cascade_name = "haarcascade_frontalface_default.xml";
String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
cv::CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
String window_name = "face_detect";

void face_detect() {
	Mat frame = imread("»À¡≥_6.jpg");
	if (!face_cascade.load(face_cascade_name))	cout << "error";
	if (!eyes_cascade.load(eyes_cascade_name)) cout << "error";

	vector<Rect> faces;
	Mat frame_gray;

	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	face_cascade.detectMultiScale(frame_gray,
		faces,
		1.1, 3, CV_HAAR_DO_ROUGH_SEARCH,
		Size(70, 70), Size(100, 100));

	for(size_t i=0;i<faces.size();i++){
		rectangle(frame, faces[i], Scalar(255, 0, 0), 2, 8, 0);

		Mat faceROI = frame_gray(faces[i]);
		vector<Rect> eyes;
		eyes_cascade.detectMultiScale(
			faceROI,
			eyes,
			1.1,
			1,
			CV_HAAR_DO_ROUGH_SEARCH,
			Size(3, 3)
			);

		for(size_t j=0;j<eyes.size();j++){
			Rect rect(
				faces[i].x + eyes[j].x,
				faces[i].y + eyes[j].y,
				eyes[j].width,
				eyes[j].height);
			rectangle(frame, rect, Scalar(0, 255, 0), 2, 8, 0);
		}

	}
	namedWindow(window_name, 2);
	imshow(window_name, frame);
	waitKey(0);
}