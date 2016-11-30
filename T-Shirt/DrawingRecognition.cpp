//------------------------------------------------------------------------------
// ObjectRecognition.cpp
// Created by Kunlakan Cherdchusilp
// Created on 11/16/2016
//------------------------------------------------------------------------------
// ASSUMPTION:
//		- All templates used must be in grayscale.
//------------------------------------------------------------------------------

#include "DrawingRecognition.h"

//----------------------------- Default Constructor ----------------------------
// Default constructor for class DrawingRecognition.
// Precondition:	None.
// Postcondition:	None.
//------------------------------------------------------------------------------
DrawingRecognition::DrawingRecognition()
{
	strokes = 0;
}

//------------------------- Two Parameter Constructor --------------------------
// A two parameters constructor for class DrawingRecognition.
// Precondition:	- input must be created and not NULL.
//					- userNOS (NOS: number of strokes) must be >= 0. 
// Postcondition:	- searchIMG is set to input and strokes is set to userNOS.
//					- edgeIMG stores an edge image of searchIMG
//------------------------------------------------------------------------------
DrawingRecognition::DrawingRecognition(const Mat &input)
{
	searchIMG = input;
	imshow("D", input);

	waitKey();
}

//--------------------------------- Destructor ---------------------------------
// Destructor for class DrawingRecognition
// Precondition:	None
// Postcondition:	None
//------------------------------------------------------------------------------
DrawingRecognition::~DrawingRecognition() {}


//------------------------------ findBestMatch() -------------------------------
// *** Region of Interest
// Precondition:	None
// Postcondition:	None
//------------------------------------------------------------------------------
void DrawingRecognition::findBestMatch()
{
	float bestMatchValue = 0;
	string bestMatchName = "";

	Mat rotation90;	// rotate 90*
	Mat rotation180; // flip vertically (0)
	Mat rotation270; // flip horizontally of the 90* (1)


					 // generate templateList

	//for each (auto &currentTemplate in templateList)
	//{
	//	//matchTemplate
	//		// loop for scaling
	//		// if the resize search img is smaller than the tempplate
	//		// quit the loop
	//}
}


//---------------------------- PRIVATE: detectEdge -----------------------------
// Detects edge of the input image.
// Preconditions:	- input must be a gray-level image.
//					- output must be declaired outside of this function.
// Postconditions:	output is an edge image of the input.
//------------------------------------------------------------------------------
void DrawingRecognition::detectEdge(const Mat &input, Mat &output)
{
	double sigmaX = 2.0;
	double sigmaY = 2.0;

	double threshold1 = 20;
	double threshold2 = 60;

	flip(input, output, 1);
	GaussianBlur(output, output, Size(7, 7), sigmaX, sigmaY);
	Canny(output, output, threshold1, threshold2);
}

//----------------------------- PRIVATE: rotate90 ------------------------------
// Rotate input image by 90 degree.
// Preconditions:	None.
// Postconditions:	output is an edge image of the input.
//------------------------------------------------------------------------------
void DrawingRecognition::rotate90(Mat &input) {
	transpose(input, input);
	flip(input, input, 0);
}