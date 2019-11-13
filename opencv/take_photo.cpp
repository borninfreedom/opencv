#include "pch.h"
#include "take_photo.h"
using namespace std;
using namespace cv;
static char filename[50];
void take_photo(){
	int index = 0;
	Mat frame;
	VideoCapture cap;
	cap.open(0);
	if(!cap.isOpened()){
		cap.open(-1);
	}
	if(!cap.isOpened()){
		cout << "error";
	}
	
	for(;;){
		cap >> frame;
		if (frame.empty())	break;
		sprintf_s(filename, "myself(%d).jpg", index);
		imwrite(filename, frame);
		imshow("myself", frame);
		index++;
		if (waitKey(1000) == 27) break;
	}
	waitKey(0);
}