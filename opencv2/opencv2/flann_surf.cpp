#include "pch.h"
#include "flann_surf.h"

using namespace cv;
void flann_surf_feature_match() {
	system("color 6F");
	Mat trainImage = imread("11.jpg");
	Mat trainImage_gray;
	pyrDown(trainImage, trainImage);
	pyrDown(trainImage, trainImage);
	imshow("srcImage", trainImage);
	cvtColor(trainImage, trainImage_gray, CV_BGR2GRAY);
	
	vector<KeyPoint> train_keypoint;
	Mat trainDesc;
	SurfFeatureDetector featureDetector(2000);
	featureDetector.detect(trainImage_gray, train_keypoint);
	SurfDescriptorExtractor featureExtractor;
	featureExtractor.compute(trainImage_gray, train_keypoint, trainDesc);

	FlannBasedMatcher matcher;
	vector<Mat> train_desc_collection(1, trainDesc);
	matcher.add(train_desc_collection);
	matcher.train();

	VideoCapture cap(0);
	unsigned int frameCount = 0;

	while(char(waitKey(1))!='q'){
		int64 time0 = getTickCount();
		Mat testImage, testImage_gray;
		cap >> testImage;
		if(testImage.empty()){
			continue;
		}

		cvtColor(testImage, testImage_gray, CV_BGR2GRAY);
		vector<KeyPoint> test_keypoint;
		Mat testDesc;
		featureDetector.detect(testImage_gray, test_keypoint);
		featureExtractor.compute(testImage_gray, test_keypoint, testDesc);

		vector<vector<DMatch>> matches;
		matcher.knnMatch(testDesc, matches, 2);
		vector<DMatch> good_matches;
		for(unsigned int i=0;i<matches.size();i++){
			if (matches[i][0].distance < 0.6*matches[i][1].distance)
				good_matches.push_back(matches[i][0]);


			
		}


		Mat dstImage;
		drawMatches(testImage, test_keypoint, trainImage, train_keypoint, good_matches, dstImage);
		imshow("match", dstImage);

		std::cout << "current fps:" << getTickFrequency() / (getTickCount() - time0) << std::endl;
	}
}