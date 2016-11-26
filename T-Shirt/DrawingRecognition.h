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

#include "TemplateImage.h"

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

	//------------------------- Two Parameter Constructor --------------------------
	// A two parameters constructor for class DrawingRecognition.
	// Precondition:	- input must be created and not NULL.
	//					- userNOS (NOS: number of strokes) must be >= 0. 
	// Postcondition:	- searchIMG is set to input, and strokes is set to userNOS.
	//					- edgeIMG stores an edge image of searchIMG
	//------------------------------------------------------------------------------
	DrawingRecognition(const Mat &input, const int &userNOS);

	//--------------------------------- Destructor ---------------------------------
	// Destructor for class DrawingRecognition
	// Precondition:	None
	// Postcondition:	None
	//------------------------------------------------------------------------------
	~DrawingRecognition();


	void findBestMatch();
	//Mat getTemplate(int strokes);

private:
	static const int MAX_TRY_PER_TEMPLATE = 20;

	Mat searchIMG;
	Mat edgeIMG;
	int strokes;

	vector<TemplateImage> templateList;


	//---------------------------- PRIVATE: detectEdge -----------------------------
	// Detects edge of the input image.
	// Preconditions:	- input must be a gray-level image.
	//					- output must be declaired outside of this function.
	// Postconditions:	output is an edge image of the input.
	//------------------------------------------------------------------------------
	void detectEdge(const Mat &input, Mat &output);

	//----------------------------- PRIVATE: rotate90 ------------------------------
	// Rotate input image by 90 degree.
	// Preconditions:	None.
	// Postconditions:	output is an edge image of the input.
	//------------------------------------------------------------------------------
	void rotate90(Mat &input);

	//float hausdorffDistance(const vector<Point> &a, const vector<Point> &b);
};