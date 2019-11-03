
#include "pch.h"
#include "video.h"
#include "hough.h"
#include <stdlib.h>
using namespace cv;
using namespace std;

int main()
{
	//执行视频流的canny检测
//	videoCanny(); 

	//对图片进行多种canny检测
	//canny(bool r,int speed,bool positive)
	//@r: if r==true,会对一张图片的canny的双阈值进行连续设置，输出的图像就会是一个线条逐渐变化的视频,if r==false,静止的canny分析
	//@speed: if r==true,此项才会起作用，控制的是waitKey()的时间，即输出图像的连续性
	//@positve: if r==true,此项才会起作用，if positive==true,阈值会从小到大变化，线条是逐渐减少的

//	canny(false);

	//对图片集进行canny检测
//	r_canny();

//	houghlines();
//	houghlinesp();
//	houghcircles();

	//tune_canny();

	tune_hough_circle();



	//测试区
	//vector<Vec4i> lines;


	return 0;
}

