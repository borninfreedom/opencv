#include "pch.h"
#include "surf.h"
 
using namespace cv;

void surf_keypoint_detect(){
	system("color 2F");
	//ShowHelpText();
	namedWindow("srcImage1", 1);
	namedWindow("srcImage2", 1);
	namedWindow("detect_result_1", 1);
	namedWindow("detect_result_2", 1);
	Mat srcImage1 = imread("1.jpg", 1);
	Mat srcImage2 = imread("2.jpg", 1);
	pyrDown(srcImage1,srcImage1);    //需要包含imgproc模块
	pyrDown(srcImage1,srcImage1);
	pyrDown(srcImage2,srcImage2);
	pyrDown(srcImage2,srcImage2);
	if(!srcImage1.data||!srcImage2.data){
		printf("error");
	}
	imshow("srcImage1", srcImage1);
	imshow("srcImage2", srcImage2);

	int minHessian = 400;
	SurfFeatureDetector detector(minHessian);
	std::vector<KeyPoint> keypoints_1, keypoints_2;

	detector.detect(srcImage1, keypoints_1);
	detector.detect(srcImage2, keypoints_2);

	Mat img_keypoints_1;
	Mat img_keypoints_2;

	drawKeypoints(srcImage1, keypoints_1, img_keypoints_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	drawKeypoints(srcImage2, keypoints_2, img_keypoints_2, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	imshow("detect_result_1", img_keypoints_1);
	imshow("detect_result_2", img_keypoints_2);

	waitKey(0);
}

void surf_feature_match(){
	Mat srcImage1 = imread("11.jpg", 1);
	Mat srcImage2 = imread("22.jpg", 1);
	pyrDown(srcImage1, srcImage1);
	pyrDown(srcImage1, srcImage1);
	pyrDown(srcImage2, srcImage2);
	pyrDown(srcImage2, srcImage2);
	if (!srcImage2.data || !srcImage1.data)	printf("error");
	namedWindow("matches", 1);
	int minHessian = 20000;
	SurfFeatureDetector detector(minHessian);

	std::vector<KeyPoint> keypoint_1, keypoint_2;

	detector.detect(srcImage1, keypoint_1);
	detector.detect(srcImage2, keypoint_2);

	SurfDescriptorExtractor extractor;
	Mat descriptors1, descriptors2;
	extractor.compute(srcImage1, keypoint_1, descriptors1);
	extractor.compute(srcImage2, keypoint_2, descriptors2);

	BruteForceMatcher< L2<float> > matcher;
	std::vector<DMatch> matches;
	matcher.match(descriptors1, descriptors2, matches);

	Mat imgMatches;
	drawMatches(srcImage1, keypoint_1, srcImage2, keypoint_2, matches, imgMatches);

	imshow("matches", imgMatches);
	waitKey(0);
}