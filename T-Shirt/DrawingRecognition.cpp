//------------------------------------------------------------------------------
// ObjectRecognition.cpp
// Created by Kunlakan Cherdchusilp
// Created on 11/16/2016
//------------------------------------------------------------------------------
// ASSUMPTION:
//		- All templates used must be in grayscale.
//		- input must be in grayscale.
//------------------------------------------------------------------------------

#include "DrawingRecognition.h"

//----------------------------- Default Constructor ----------------------------
// Default constructor for class DrawingRecognition.
// Precondition:	None.
// Postcondition:	None.
//------------------------------------------------------------------------------
DrawingRecognition::DrawingRecognition()
{
	storkes = 0;
}

//------------------------ Single Parameter Constructor ------------------------
// A single parameter constructor for class DrawingRecognition.
// Precondition:	input must be created and not NULL.
// Postcondition:	serachIMG is set to input, and strokes is set to 0.
//------------------------------------------------------------------------------
DrawingRecognition::DrawingRecognition(const Mat &input)
{
    DrawingRecognition(input, 0);
}

//------------------------- Two Parameter Constructor --------------------------
// A two parameters constructor for class DrawingRecognition.
// Precondition:	- input must be created and not NULL.
//					- userNOS (NOS: number of strokes) must be >= 0. 
// Postcondition:	serachIMG is set to input, and strokes is set to userNOS.
//------------------------------------------------------------------------------
DrawingRecognition::DrawingRecognition(const Mat &input, const int &userNOS)
{
    searchIMG = input;
    strokes = userNOF;
}

//--------------------------------- Destructor ---------------------------------
// Destructor for class DrawingRecognition
// Precondition:	None
// Postcondition:	None
//------------------------------------------------------------------------------
DrawingRecognition::~DrawingRecognition(){}


void findBestMatch()
{
	//matchTemplate();
}

//------------------------------ edgeDetection() -------------------------------
// Precondition :	
// Postcondition :
//------------------------------------------------------------------------------
void DrawingRecognition::edgeDetection(Mat &img)
{
	double sigmaX = 2.0;
	double sigmaY = 2.0;
	
	double threshold1 = 20;
	double threshold2 = 60;

	flip(img, img, 1);
	GaussianBlur(img, img, Size(7, 7), sigmaX, sigmaY);
	Canny(img, img, threshold1, threshold2);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*float ObjectRecognition::hausdorffDistance(const vector<Point> &a, const vector<Point> &b)
{
	//findContours of inputs and template image.

	HausdorffDistanceExtractor* hd = createHausdorffDistanceExtractor();

	float distanceAB = hd->computeDistance(a, b);
	float distanceBA = hd->computeDistance(b, a);

	delete(hd);

	return max(distanceAB, distanceBA);
}*/