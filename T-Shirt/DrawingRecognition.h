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

class DrawingRecognition {

public:
	//----------------------------- Default Constructor ----------------------------
	// Default constructor for class DrawingRecognition
	// Precondition:	None
	// Postcondition:	None
	//------------------------------------------------------------------------------
	DrawingRecognition();
	DrawingRecognition(const Mat &input);
	DrawingRecognition(const Mat &input, const int &userNOS);
	
	//--------------------------------- Destructor ---------------------------------
	// Destructor for class DrawingRecognition
	// Precondition:	None
	// Postcondition:	None
	//------------------------------------------------------------------------------
	~DrawingRecognition();

	void findBestMatch();
	Mat getTemplate(int strokes);

private:
	Mat searchIMG;
	Mat templateIMG;
	
	int strokes;
	
	void edgeDetection(Mat &img);
	//float hausdorffDistance(const vector<Point> &a, const vector<Point> &b);
};