//------------------------------------------------------------------------------
// ObjectRecognition.cpp
// Created by Kunlakan Cherdchusilp
// Created on 11/16/2016
//------------------------------------------------------------------------------
// Recoginzing drawing that is passed in to the program.
//
// ASSUMPTION:
//		- All templates used must be in grayscale.
//		- The detection may not be accurate due to the various doodling styles
//		  of individuals.
//------------------------------------------------------------------------------

#include "DrawingRecognition.h"


//----------------------------- Default Constructor ----------------------------
// Default constructor for class DrawingRecognition.
// Precondition:	None.
// Postcondition:	None.
//------------------------------------------------------------------------------
DrawingRecognition::DrawingRecognition() {}

//------------------------- One Parameter Constructor --------------------------
// A two parameters constructor for class DrawingRecognition.
// Precondition:	- input must be created and not NULL.
// Postcondition:	- searchIMG is set to input.
//------------------------------------------------------------------------------
DrawingRecognition::DrawingRecognition(const Mat &input)
{
	searchIMG = input;
	libraryTMPL.createLibrary();
}

//------------------------- One Parameter Constructor --------------------------
// A two parameters constructor for class DrawingRecognition.
// Precondition:	- inputFile must be the path of the input file that exist
//					  in the same directory as the program.
// Postcondition:	- searchIMG is set to an image that has inputFile name.
//------------------------------------------------------------------------------
DrawingRecognition::DrawingRecognition(const string &inputFile)
{
	searchIMG = imread(inputFile, IMREAD_GRAYSCALE);
	libraryTMPL.createLibrary();
}

//--------------------------------- Destructor ---------------------------------
// Destructor for class DrawingRecognition
// Precondition:	None
// Postcondition:	None
//------------------------------------------------------------------------------
DrawingRecognition::~DrawingRecognition() {}



//------------------------------ findBestMatch() -------------------------------
// find the best match of the searchIMG with the template images.
// Precondition:	libraryTMPL must be created with all templates stored.
// Postcondition:	name of the best match shape is returned
//------------------------------------------------------------------------------
string DrawingRecognition::findBestMatch()
{
	double bestMatchDistance = FLT_MAX;

	Mat inputIMG(searchIMG);
	TemplateImage bestMatchTMPL;
	vector<Point> contours;

	// Get contours of the searchIMG
	int numContours = getContour(inputIMG, contours);

	// Get list of all templates that have the same number of contours
	vector<TemplateImage> listTMPL = libraryTMPL.getTemplateImageList(numContours);
	
	// If there's on a one template for that numContours, return that template
	// as the best match.
	if (listTMPL.size() == 1)
		return listTMPL[0].getShape();

	// Find best match
	float score = 0;
	vector<Point> TMPLcontours;
	for (int i = 0; i < listTMPL.size(); i++)
	{		
		getContour(listTMPL[i].getImage(), TMPLcontours);
		score = matchShapes(contours, TMPLcontours, 1, 0.0);

		if (score < bestMatchDistance)
		{
			if (score == 0)
				return listTMPL[i].getShape();

			bestMatchDistance = score;
			bestMatchTMPL = listTMPL[i];
		}
	}

	return bestMatchTMPL.getShape();
}

//---------------------------- PRIVATE: getContour -----------------------------
// Get contours of input image and its number of polygon curves.
// Preconditions:	- input must be a gray-level image.
//					- output vector of Poitn must be declaired outside of this
//					  function.
// Postconditions:	- output stores vector of contours
//					- number of polygon curves is returned
//------------------------------------------------------------------------------
int DrawingRecognition::getContour(const Mat &input, vector<Point> &output)
{
	Mat edge;
	detectEdge(input, edge);

	vector<vector<Point>> contours;
	findContours(edge, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

	for (int i = 0; i < contours.size(); i++)
		output.insert(output.end(), contours[i].begin(), contours[i].end());

	Mat approx;
	approxPolyDP(Mat(output), approx, arcLength(Mat(contours[0]), true)*0.02, true);

	return approx.size().height;
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

//-------------------------------- getAllShapes --------------------------------
// Get a list of all shapes name available in the template library.
// Preconditions:	libraryTMPL must be created before calling this function.
// Postconditions:	return a list of all shapes name in the template library.
//------------------------------------------------------------------------------
vector<string> DrawingRecognition::getAllShapes() 
{
	return libraryTMPL.getAllShapes();
}