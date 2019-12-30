#include "pch.h"
#include "generate_video.h"
using namespace cv;
using namespace std;
//static char filename[50];
//static int index = 1;
//Mat frame;
void generate_video(){
	char filename[50];
	int index = 1;
	Mat frame;
	namedWindow("video", 1);
	for (; index < 336;index++) {
		sprintf_s(filename, "myself(%d).jpg",index);
		frame = imread(filename);
		imshow("video", frame);
		//index++;
		if (waitKey(30) == 27) break;
		if(index==335){
			for(;index>=1;index--){
				sprintf_s(filename, "myself(%d).jpg", index);
				frame = imread(filename);
				imshow("video", frame);
				if (waitKey(30) == 27) break;
			}
		}
	}
	waitKey(0);
}