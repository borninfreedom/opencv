#include "pch.h"
#include "flann.h"
using namespace cv;

void flann_feature_match(){
	Mat srcImage1 = imread("11.jpg", 1);
	Mat srcImage2 = imread("22.jpg", 1);
	pyrDown(srcImage2, srcImage2);
	pyrDown(srcImage2, srcImage2);
	pyrDown(srcImage1, srcImage1);
	pyrDown(srcImage1, srcImage1);
	if (!srcImage2.data || !srcImage1.data)	printf("error");

	int minHessian = 9000;
	SURF detector(minHessian);
	std::vector<KeyPoint> keypoint_1, keypoint_2;
	detector.detect(srcImage1, keypoint_1);
	detector.detect(srcImage2, keypoint_2);

	SURF extractor;
	Mat desc_1, desc_2;
	extractor.compute(srcImage1, keypoint_1, desc_1);
	extractor.compute(srcImage2, keypoint_2, desc_2);

	FlannBasedMatcher matcher;
	std::vector<DMatch> matches;
	matcher.match(desc_1, desc_2, matches);
	double max_dist = 0;
	double min_dist = 100;

	for(int i=0;i<desc_1.rows;i++){
		double dist = matches[i].distance;
		if (dist < min_dist)	min_dist = dist;
		if (dist > max_dist)	max_dist = dist;

	}

	printf(">max_dist:%f\n", max_dist);
	printf(">min_dist:%f\n", min_dist);

	std::vector<DMatch> good_matches;
	for(int i=0;i<desc_1.rows;i++){
		if (matches[i].distance < 2 * min_dist)
			good_matches.push_back(matches[i]);
	}

	Mat img_matches;
	drawMatches(srcImage1, keypoint_1, srcImage2, keypoint_2, good_matches, img_matches, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	for(int i=0;i<good_matches.size();i++){
		printf(">符合条件的匹配点[%d] 特征点1:%d -- 特征点2:%d\n", i, good_matches[i].queryIdx, good_matches[i].trainIdx);
	}

	imshow("match", img_matches);
	waitKey(0);
}