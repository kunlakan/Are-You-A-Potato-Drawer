//------------------------------------------------------------------------------
// ObjectRecognition.h
// Created by Kunlakan Cherdchusilp
// Created on 11/16/2016
//------------------------------------------------------------------------------
// ObjectRecognition class is
//------------------------------------------------------------------------------

#include <algorithm>
#include <vector>
//#include <vector>

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
	
	int hausdorffDistance(const vector<Point> &a, const vector<Point> &b);
	int getDistance(const vector<Point> &a, const vector<Point> &b);
	
};