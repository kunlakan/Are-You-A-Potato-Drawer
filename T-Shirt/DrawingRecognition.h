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

#include "TemplateLibrary.h"
#include "opencv2/shape.hpp"

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

	//------------------------- One Parameter Constructor --------------------------
	// A two parameters constructor for class DrawingRecognition.
	// Precondition:	- input must be created and not NULL.
	// Postcondition:	- searchIMG is set to input.
	//------------------------------------------------------------------------------
	DrawingRecognition(const Mat &input);

	//------------------------- One Parameter Constructor --------------------------
	// A two parameters constructor for class DrawingRecognition.
	// Precondition:	- inputFile must be the path of the input file that exist
	//					  in the same directory as the program.
	// Postcondition:	- searchIMG is set to an image that has inputFile name.
	//------------------------------------------------------------------------------
	DrawingRecognition(const string &inputName);

	//--------------------------------- Destructor ---------------------------------
	// Destructor for class DrawingRecognition
	// Precondition:	None
	// Postcondition:	None
	//------------------------------------------------------------------------------
	~DrawingRecognition();


	void findBestMatch();
	//Mat getTemplate(int strokes);

private:
	//static const int MAX_TRY_PER_TEMPLATE = 20;

	Mat searchIMG;
	TemplateLibrary libraryTMPL;
	



	//---------------------------- PRIVATE: detectEdge -----------------------------
	// Detects edge of the input image.
	// Preconditions:	- input must be a gray-level image.
	//					- output must be declaired outside of this function.
	// Postconditions:	output is an edge image of the input.
	//------------------------------------------------------------------------------
	void detectEdge(const Mat &input, Mat &output);

	void matchTMPL(const Mat &search, const Mat &tmpl);

	vector<vector<Point>> getContour(const Mat &input);

	Size getConers(vector<vector<Point>> contours);

	//----------------------------- PRIVATE: rotate90 ------------------------------
	// Rotate input image by 90 degree.
	// Preconditions:	None.
	// Postconditions:	output is an edge image of the input.
	//------------------------------------------------------------------------------
	void rotate90(Mat &input);

	//float hausdorffDistance(const vector<Point> &a, const vector<Point> &b);
};