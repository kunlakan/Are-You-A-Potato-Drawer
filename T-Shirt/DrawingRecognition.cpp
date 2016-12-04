//------------------------------------------------------------------------------
// ObjectRecognition.cpp
// Created by Kunlakan Cherdchusilp
// Created on 11/16/2016
//------------------------------------------------------------------------------
// ASSUMPTION:
//		- All templates used must be in grayscale.
//------------------------------------------------------------------------------

#include "DrawingRecognition.h"
#include <iostream>

using namespace std;
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
// *** Region of Interest
// Precondition:	None
// Postcondition:	None
//------------------------------------------------------------------------------
string DrawingRecognition::findBestMatch()
{
	double bestMatchDistance = FLT_MAX;
	//Ptr<HausdorffDistanceExtractor> hd = createHausdorffDistanceExtractor();
	//hd->setRankProportion(0.6);

	Mat inputIMG(searchIMG);
	TemplateImage bestMatchTMPL;
	vector<Point> contours;

	// Get contours of the searchIMG
	int numContours = getContour(inputIMG, contours);
	//cout << numContours << endl;

	// Get list of all templates that have the same number of contours
	vector<TemplateImage> listTMPL = libraryTMPL.getTemplateImageList(numContours);
	
	if (listTMPL.size() == 1)
		return listTMPL[0].getShape();

	// Find best match
	float distance = 0;
	vector<Point> TMPLcontours;
	for (int i = 0; i < listTMPL.size(); i++)
	{		
		getContour(listTMPL[i].getImage(), TMPLcontours);

		while (inputIMG.rows >= listTMPL[i].getImage().rows || inputIMG.cols >= listTMPL[i].getImage().cols)
		{
			//distance = hd->computeDistance(contours, TMPLcontours);
			distance = matchShapes(contours, TMPLcontours, 1, 0.0);

			if (distance < bestMatchDistance)
			{
				if (distance == 0)
					return listTMPL[i].getShape();

				bestMatchDistance = distance;
				bestMatchTMPL = listTMPL[i];
			}

			resize(inputIMG, inputIMG, Size(), RESIZE_PERCENTAGE, RESIZE_PERCENTAGE, INTER_AREA);
			getContour(inputIMG, contours);

			//cout << distance << endl;
			//cout << listTMPL[i].getShape() << endl;
		}

		searchIMG.copyTo(inputIMG);
		getContour(inputIMG, contours);
	}

	//cout << "distance " << bestMatchDistance << endl;
	//cout << bestMatchTMPL.getShape() << endl;
	//cin.get();

	return bestMatchTMPL.getShape();
}


int DrawingRecognition::getContour(const Mat &input, vector<Point> &output)
{
	Mat edge;
	detectEdge(input, edge);

	//imshow("edge", edge);

	vector<vector<Point>> contours;
	findContours(edge, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	// RETR_EXTERNAL gives "outer" contours, so if you have one contour
	// enclosing another (like concentric circles), only the outermost is given.

	for (int i = 0; i < contours.size(); i++)
		output.insert(output.end(), contours[i].begin(), contours[i].end());

	Mat approx;
	approxPolyDP(Mat(output), approx, arcLength(Mat(contours[0]), true)*0.02, true);

	//Drawing Contours
	/*vector<Vec4i> hierarchy;
	RNG rng(12345);

	Mat drawing = Mat::zeros(searchIMG.size(), CV_8UC3);
	for (int i = 0; i< contours.size(); i++)
	{
	Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
	drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
	}

	imshow("d", drawing);
	waitKey();

	cout << contours.size() << endl;
	cout << approx.size() << endl;
	cin.get();*/
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
	// Threshold.
	// Set values equal to or above 220 to 0.
	// Set values below 220 to 255.
	//Mat im_th;
	//threshold(input, im_th, 220, 255, THRESH_BINARY_INV);

	//// Floodfill from point (0, 0)
	//Mat im_floodfill = im_th.clone();
	//floodFill(im_floodfill, cv::Point(0, 0), Scalar(255));

	//// Invert floodfilled image
	//Mat im_floodfill_inv;
	//bitwise_not(im_floodfill, im_floodfill_inv);

	//// Combine the two images to get the foreground.
	//output = (im_th | im_floodfill_inv);

	//bitwise_not(output, output);

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
void DrawingRecognition::rotate90(Mat &input)
{
	transpose(input, input);
	flip(input, input, 0);
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