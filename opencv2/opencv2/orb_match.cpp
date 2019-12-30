#include "pch.h"
#include "orb_match.h"

using namespace cv;

void orb_match(){
	Mat srcImage = imread("11.jpg", 1);
	pyrDown(srcImage, srcImage);
	pyrDown(srcImage, srcImage);

	imshow("srcImage", srcImage);
	Mat grayImage;
	cvtColor(srcImage, grayImage, CV_BGR2GRAY);

	OrbFeatureDetector featureDetector;
	vector<KeyPoint> keypoints;
	Mat desc;

	featureDetector.detect(grayImage, keypoints);

	OrbDescriptorExtractor featureExtractor;
	featureExtractor.compute(grayImage, keypoints, desc);

	flann::Index flannIndex(desc, flann::LshIndexParams(12, 20, 2), cvflann::FLANN_DIST_HAMMING);

	VideoCapture cap(0);
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 360);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 900);

	unsigned int frameCount = 0;
	while(1) //直到按下esc
	{
		double time0 = static_cast<double>(getTickCount());
		Mat capImage, gray_capImage;
		cap >> capImage;
		if(capImage.empty())
			continue;

		cvtColor(capImage, gray_capImage, CV_BGR2GRAY);

		vector<KeyPoint> capKeypoint;
		Mat capDesc;
		featureDetector.detect(gray_capImage, capKeypoint);
		featureExtractor.compute(gray_capImage, capKeypoint, capDesc);

		Mat matchIndex(capDesc.rows, 2, CV_32SC1),
			matchDistance(capDesc.rows, 2, CV_32FC1);
		flannIndex.knnSearch(capDesc, matchIndex, matchDistance, 2, flann::SearchParams());

		vector<DMatch> goodMatches;
		for(int i=0;i<matchDistance.rows;i++){
			if(matchDistance.at<float>(i,0)<0.6*matchDistance.at<float>(i,1)){
				DMatch dmatches(i, matchIndex.at<int>(i, 0), matchDistance.at<float>(i, 0));
				goodMatches.push_back(dmatches);
			}
		}

		Mat resultImage;
		drawMatches(capImage, capKeypoint, srcImage, keypoints, goodMatches, resultImage);
		imshow("match", resultImage);

		std::cout << getTickFrequency() / (getTickCount() - time0) << std::endl;
		if (char(waitKey(1)) == 27)
			break;
	}
}