//------------------------------------------------------------------------------
// ObjectRecognition.h
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

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "TemplateLibrary.h"
#include "opencv2/shape.hpp"

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


	//------------------------------ findBestMatch() -------------------------------
	// find the best match of the searchIMG with the template images.
	// Precondition:	libraryTMPL must be created with all templates stored.
	// Postcondition:	name of the best match shape is returned
	//------------------------------------------------------------------------------
	string findBestMatch();

	//-------------------------------- getAllShapes --------------------------------
	// Get a list of all shapes name available in the template library.
	// Preconditions:	libraryTMPL must be created before calling this function.
	// Postconditions:	return a list of all shapes name in the template library.
	//------------------------------------------------------------------------------
	vector<string> getAllShapes();

private:
	Mat searchIMG;
	TemplateLibrary libraryTMPL;
	
	//---------------------------- PRIVATE: detectEdge -----------------------------
	// Detects edge of the input image.
	// Preconditions:	- input must be a gray-level image.
	//					- output must be declaired outside of this function.
	// Postconditions:	output is an edge image of the input.
	//------------------------------------------------------------------------------
	void detectEdge(const Mat &input, Mat &output);

	//---------------------------- PRIVATE: getContour -----------------------------
	// Get contours of input image and its number of polygon curves.
	// Preconditions:	- input must be a gray-level image.
	//					- output vector of Poitn must be declaired outside of this
	//					  function.
	// Postconditions:	- output stores vector of contours
	//					- number of polygon curves is returned
	//------------------------------------------------------------------------------
	int getContour(const Mat &input, vector<Point> &output);
};