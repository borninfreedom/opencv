#include "pch.h"
#include "findObject.h"


using namespace cv;

void find_object(){
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

	for (int i = 0; i < desc_1.rows; i++) {
		double dist = matches[i].distance;
		if (dist < min_dist)	min_dist = dist;
		if (dist > max_dist)	max_dist = dist;

	}

	printf(">max_dist:%f\n", max_dist);
	printf(">min_dist:%f\n", min_dist);

	std::vector<DMatch> good_matches;
	for (int i = 0; i < desc_1.rows; i++) {
		if (matches[i].distance < 2 * min_dist)
			good_matches.push_back(matches[i]);
	}

	Mat img_matches;
	drawMatches(srcImage1, keypoint_1, srcImage2, keypoint_2, good_matches, img_matches, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	vector<Point2f> obj;
	vector<Point2f> scene;

	for(unsigned int i=0; i<good_matches.size();i++){
		obj.push_back(keypoint_1[good_matches[i].queryIdx].pt);
		scene.push_back(keypoint_2[good_matches[i].trainIdx].pt);
	}

	Mat H = findHomography(obj, scene, CV_RANSAC);

	vector<Point2f> obj_corners(4);
	obj_corners[0] = cvPoint(0, 0);
	obj_corners[1] = cvPoint(srcImage1.cols, 0);
	obj_corners[2] = cvPoint(srcImage1.cols, srcImage1.rows);
	obj_corners[3] = cvPoint(0, srcImage1.rows);
	vector<Point2f> scene_corners(4);

	perspectiveTransform(obj_corners, scene_corners, H);

	line(img_matches, scene_corners[0] + Point2f(static_cast<float>(srcImage1.cols), 0), scene_corners[1] + Point2f(static_cast<float>(srcImage1.cols), 0), Scalar(255, 0, 123), 4);
	line(img_matches, scene_corners[1] + Point2f(static_cast<float>(srcImage1.cols), 0), scene_corners[2] + Point2f(static_cast<float>(srcImage1.cols), 0), Scalar(255, 0, 123), 4);
	line(img_matches, scene_corners[2] + Point2f(static_cast<float>(srcImage1.cols), 0), scene_corners[3] + Point2f(static_cast<float>(srcImage1.cols), 0), Scalar(255, 0, 123), 4);
	line(img_matches, scene_corners[3] + Point2f(static_cast<float>(srcImage1.cols), 0), scene_corners[0] + Point2f(static_cast<float>(srcImage1.cols), 0), Scalar(255, 0, 123), 4);

	imshow("good_matches&find object", img_matches);
	waitKey(0);
}