//------------------------------------------------------------------------------
// ObjectRecognition.h
// Created by Kunlakan Cherdchusilp
// Created on 11/16/2016
//------------------------------------------------------------------------------
// ObjectRecognition class is
//------------------------------------------------------------------------------

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <algorithm>
#include <vector>

#include "opencv2/shape/shape.hpp"
using namespace std;
using namespace cv;

class ObjectRecognition {

public:
	ObjectRecognition();
	ObjectRecognition(Mat input);
	~ObjectRecognition();



private:
	Mat input;
	Mat temp;
	
	void edgeDetection();
	float hausdorffDistance(const vector<Point> &a, const vector<Point> &b);
};