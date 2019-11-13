#include "pch.h"
//#include "my_gui.h"
//using namespace cv;
//
//
//my_gui::my_gui(int index)
//{
//	trachbarValue = 1;
//	namedWindow("ԭʼͼ", 1);
//	switch (index)
//	{
//	case 1:
//		createTrackbar("select files", "ԭʼͼ", &trachbarValue, 100, selectfileCallback);
//		selectfileCallback(trachbarValue, 0);
//		break;
//	case 2:
//		createTrackbar("select files", "ԭʼͼ", &trachbarValue, 100, selectfileCallback2);
//		selectfileCallback2(trachbarValue, 0);
//		break;
//	case 3:
//		createTrackbar("select files", "ԭʼͼ", &trachbarValue, 100, selectfileCallback3);
//		selectfileCallback3(trachbarValue, 0);
//		break;
//	case 4:
//		createTrackbar("select files", "ԭʼͼ", &trachbarValue, 100, selectfileCallback4);
//		selectfileCallback4(trachbarValue, 0);
//		break;
//	case 5:
//		createTrackbar("select files", "ԭʼͼ", &trachbarValue, 100, selectfileCallback5);
//		selectfileCallback5(trachbarValue, 0);
//		break;
//	case 6:
//		createTrackbar("select files", "ԭʼͼ", &trachbarValue, 100, selectfileCallback6);
//		selectfileCallback6(trachbarValue, 0);
//		break;
//	default:
//		std::cout << "index is out of range." << std::endl;
//		break;
//	}
//	
//	
//}
//
//
//my_gui::~my_gui()
//{
//}
//
//void my_gui::selectfileCallback(int, void*) {
//	sprintf_s(filename, "1 (%d).jpg", trachbarValue == 0 ? 1 : trachbarValue);
//	srcImage = imread(filename);
//	//	imshow("ԭʼͼ", srcImage);
//}
//void my_gui::selectfileCallback2(int, void*) {
//	sprintf_s(filename, "2 (%d).jpg", trachbarValue == 0 ? 1 : trachbarValue);
//	srcImage = imread(filename);
//	//	imshow("ԭʼͼ", srcImage);
//}
//void my_gui::selectfileCallback3(int, void*) {
//	sprintf_s(filename, "3 (%d).jpg", trachbarValue == 0 ? 1 : trachbarValue);
//	srcImage = imread(filename);
//	//	imshow("ԭʼͼ", srcImage);
//}
//void my_gui::selectfileCallback4(int, void*) {
//	sprintf_s(filename, "4 (%d).jpg", trachbarValue == 0 ? 1 : trachbarValue);
//	srcImage = imread(filename);
//	//	imshow("ԭʼͼ", srcImage);
//}
//void my_gui::selectfileCallback5(int, void*) {
//	sprintf_s(filename, "5 (%d).jpg", trachbarValue == 0 ? 1 : trachbarValue);
//	srcImage = imread(filename);
//	//	imshow("ԭʼͼ", srcImage);
//}
//void my_gui::selectfileCallback6(int, void*) {
//	sprintf_s(filename, "6 (%d).jpg", trachbarValue == 0 ? 1 : trachbarValue);
//	srcImage = imread(filename);
//	//	imshow("ԭʼͼ", srcImage);
//}
