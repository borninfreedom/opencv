#include "pch.h"
#include "opticalFlow.h"

using namespace cv;
using namespace std;

void optical_flow(){
	VideoCapture cap(0);
	if (!cap.isOpened()) {
		cerr << "Unable to open camera" << endl;
	}

	vector<Scalar> colors;
	RNG rng;
	for(int i=0;i<100;i++){
		int r = rng.uniform(0, 256);
		int g = rng.uniform(0, 256);
		int b = rng.uniform(0, 256);
		colors.push_back(Scalar(r, g, b));
	}

	Mat old_frame, old_gray;
	vector<Point2f> p0, p1;

	cap >> old_frame;
	cvtColor(old_frame, old_gray, COLOR_BGR2GRAY);
	goodFeaturesToTrack(old_gray, p0, 100, 0.3, 7, Mat(), 7, false, 0.04);

	//  void goodFeaturesToTrack(InputArray image, OutputArray corners,
	//	int maxCorners, double qualityLevel, double minDistance,
	//	InputArray mask = noArray(), int blockSize = 3,
	//	bool useHarrisDetector = false, double k = 0.04);
	//  第一个参数image：8位或32位单通道灰度图像;
	//  第二个参数corners: 位置点向量,保存的是检测到角点的坐标;
	//  第三个参数maxCorners: 定义可以检测到的角点的数量的最大值;
	//  第四个参数qualityLevel: 检测到的角点的质量等级,角点特征值小于qualityLevel*最大特征
	//  值的点将被舍弃;
	//  第五个参数minDistance: 两个角点间最小间距,以像素为单位;
	//  第六个参数mask: 指定检测区域,若检测整幅图像,mask置为空Mat();
	//  第七个参数blockSize: 计算协方差矩阵时窗口大小;
	//  第八个参数useHarrisDector: 是否使用Harris角点检测,为false,则使用Shi-Tomasi算子;
	//  第九个参数K: 留给Harris角点检测算子用的中间参数,一般取经验值0.04~0.06.第8个参数为false时,改参数不起作用;

	 // Create a mask image for drawing purposes
	Mat mask = Mat::zeros(old_frame.size(), old_frame.type());
	while(true){
		Mat frame, frame_gray;
		cap >> frame;
		if (frame.empty())
			break;
		cvtColor(frame, frame_gray, COLOR_BGR2GRAY);

		//calculate optical flow
		vector<uchar> status;
		vector<float> err;
		TermCriteria criteria = TermCriteria((TermCriteria::COUNT) + (TermCriteria::EPS), 10, 0.03);

		calcOpticalFlowPyrLK(old_gray, frame_gray, p0, p1, status, err, Size(15, 15), 2, criteria);

		//calcOpticalFlowPyrLK
		/*Calculates an optical flow for a sparse feature set using the iterative Lucas - Kanade method with pyramids.

			C++: void calcOpticalFlowPyrLK(InputArray prevImg, InputArray nextImg, InputArray prevPts, InputOutputArray nextPts, OutputArray status, OutputArray err, Size winSize = Size(21, 21), int maxLevel = 3, TermCriteria criteria = TermCriteria(TermCriteria::COUNT + TermCriteria::EPS, 30, 0.01), int flags = 0, double minEigThreshold = 1e-4)
			Parameters:
				prevImg – first 8-bit input image or pyramid constructed by buildOpticalFlowPyramid().
				nextImg – second input image or pyramid of the same size and the same type as prevImg.
				prevPts – vector of 2D points for which the flow needs to be found; point coordinates must be single-precision floating-point numbers.
				nextPts – output vector of 2D points (with single-precision floating-point coordinates) containing the calculated new positions of input features in the second image; when OPTFLOW_USE_INITIAL_FLOW flag is passed, the vector must have the same size as in the input.
				status – output status vector (of unsigned chars); each element of the vector is set to 1 if the flow for the corresponding features has been found, otherwise, it is set to 0.
				err – output vector of errors; each element of the vector is set to an error for the corresponding feature, type of the error measure can be set in flags parameter; if the flow wasn’t found then the error is not defined (use the status parameter to find such cases).
					winSize – size of the search window at each pyramid level.
				maxLevel – 0-based maximal pyramid level number; if set to 0, pyramids are not used (single level), if set to 1, two levels are used, and so on; if pyramids are passed to input then algorithm will use as many levels as pyramids have but no more than maxLevel.
				criteria – parameter, specifying the termination criteria of the iterative search algorithm (after the specified maximum number of iterations criteria.maxCount or when the search window moves by less than criteria.epsilon.
*/
		vector<Point2f> good_new;
		for(uint i=0;i<p0.size();i++){
			if(status[i]==1){
				good_new.push_back(p1[i]);
				//draw the tracks
				line(mask, p1[i], p0[i], colors[i], 2);
				circle(frame, p1[i], 5, colors[i], -1);
			}

		}

		Mat img;
		add(frame, mask, img);
		imshow("Frame", img);

		int keyboard = waitKey(30);
		if(keyboard=='q' || keyboard==27)
			break;

		old_gray = frame_gray.clone();
		p0 = good_new;


	}
}