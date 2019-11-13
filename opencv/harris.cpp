#include "pch.h"
#include "harris.h"
using namespace cv;
int g_nFileIndex = 1;
char filename[50];

static void harrisCallback(int,void*){
	sprintf_s(filename, "∆Â≈Ã (%d).jpg", g_nFileIndex);
	Mat srcImage = imread(filename);
	if(srcImage.empty()){
		///*do
		//{
		//	g_nFileIndex ++;
		//	setTrackbarPos("file", "harris", g_nFileIndex);
		//	Mat srcImage = imread(filename);
		//	if (waitKey(10) == 27) break;
		//} while (srcImage.empty());*/
		//while(1){
		//	g_nFileIndex ++;
		//	setTrackbarPos("file", "harris", g_nFileIndex);
		//	Mat srcImage = imread(filename);
		//	if (srcImage.empty())
		//		continue;
		//	else
		//		break;
		//}
		std::cout << "file is not ok" << std::endl;
		g_nFileIndex++;
		setTrackbarPos("file", "harris", g_nFileIndex);
	}
	//pyrDown(srcImage, srcImage);
	//pyrDown(srcImage, srcImage);
	cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);
	imshow("origin", srcImage);

	Mat cornerStrength;
	cornerHarris(srcImage, cornerStrength, 2, 3, 0.01);

	Mat harrisCorner;
	threshold(cornerStrength, harrisCorner, 0.00001, 255, THRESH_BINARY);
	imshow("harris", harrisCorner);
}
void corner_harris() {
	namedWindow("harris", 1);
	createTrackbar("file", "harris", &g_nFileIndex, 300, harrisCallback);
	harrisCallback(g_nFileIndex, 0);
	
	waitKey(0);

}