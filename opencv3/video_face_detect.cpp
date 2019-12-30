#include "pch.h"
#include "video_face_detect.h"
using namespace std;
using namespace cv;

static const String window_name = "videoFaceDetect";
static String face_cascade_name = "haarcascade_frontalface_default.xml";
static String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
static CascadeClassifier face_cascade;
static CascadeClassifier eyes_cascade;

void video_face_detect(){
	namedWindow(window_name, 1);
	if (!face_cascade.load(face_cascade_name))	cout << "error";
	if (!eyes_cascade.load(eyes_cascade_name))	cout << "error";

	VideoCapture cap;
	cap.open(0);
	if(!cap.isOpened()){
		cap.open(-1);
	}
	if(!cap.isOpened()){
		cout << "error";
	}
	Mat frame;
	vector<Rect> faces;
	Mat gray_frame;

	for(;;){
		cap >> frame;
		if (frame.empty())	break;
		cvtColor(frame, gray_frame, COLOR_BGR2GRAY);
		equalizeHist(gray_frame, gray_frame);
		face_cascade.detectMultiScale(
			gray_frame,
			faces,
			1.1,
			3,
			CV_HAAR_DO_ROUGH_SEARCH,
			Size(70, 70),
			Size(200, 200));

		for(size_t i=0;i<faces.size();i++){
			rectangle(frame, faces[i], Scalar(255, 0, 0), 2, 8, 0);
			Mat faceROI = gray_frame(faces[i]);
			vector<Rect> eyes;
			eyes_cascade.detectMultiScale(
				faceROI,
				eyes,
				1.1,
				1,
				CV_HAAR_DO_ROUGH_SEARCH,
				Size(3, 3));

			for(size_t j=0;j<eyes.size();j++){
				Rect rect(
					faces[i].x + eyes[j].x,
					faces[i].y + eyes[j].y,
					eyes[j].width,
					eyes[j].height);
				rectangle(frame, rect, Scalar(0, 255, 0), 2, 8, 0);
			}

		}

		cv::imshow(window_name, frame);
		waitKey(20);
	}
}

