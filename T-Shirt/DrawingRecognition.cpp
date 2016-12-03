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
void DrawingRecognition::findBestMatch()
{
	Ptr<HausdorffDistanceExtractor> hd = createHausdorffDistanceExtractor();

	float bestMatchDistance = FLT_MAX;
	TemplateImage bestMatchTMPL;

	imshow("D", searchIMG);
	// Get contours of the searchIMG
	//vector<vector<Point>> contours = getContour(searchIMG);

	//// Get list of all templates that have the same number of contours
	//vector<TemplateImage> listTMPL = libraryTMPL.getTemplateImageList(contours.size());

	//// Find best match using Hausdorff distance
	//float distance = 0;
	//for (int i = 0; i < listTMPL.size(); i++)
	//{
	//	vector<vector<Point>> TMPLcontours = getContour(listTMPL[i].getImage());
	//	distance = hd->computeDistance(contours, TMPLcontours);

	//	if (distance < bestMatchDistance)
	//	{
	//		bestMatchDistance = distance;
	//		bestMatchTMPL = listTMPL[i];
	//	}
	//}

	delete(hd);
}


vector<vector<Point>> DrawingRecognition::getContour(const Mat &input)
{
	Mat edge;
	vector<vector<Point>> contours;
	//vector<Point> allContours;

	detectEdge(input, edge);
	findContours(edge, contours, RETR_LIST, CHAIN_APPROX_NONE);
	// RETR_LIST gives all the contours and doesn't even bother calculating the
	// hierarchy -- good if you only want the contours and don't care whether
	// one is nested inside another.

	/*for (int i = 0; i < contours.size(); i++)
	{
		for (int j = 0; j < contours[i].size(); j++)
		{
			allContours.push_back(contours[i][j]);
		}
	}*/

	//Drawing Contours
	//vector<Vec4i> hierarchy;
	//RNG rng(12345);

	//Mat drawing = Mat::zeros(searchIMG.size(), CV_8UC3);
	//for (int i = 0; i< contours.size(); i++)
	//{
	//Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
	//drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
	//}

	/*	imshow("d", drawing);
	waitKey()*/;

	return contours;
}

//Size DrawingRecognition::getConers(vector<vector<Point>> contours)
//{
//	Mat polygon;
//	approxPolyDP(Mat(contours[0]), polygon, arcLength(Mat(contours[0]), true)*0.02, true);
//
//	imshow("polygon", polygon);
//	waitKey();
//	//cout << polygon.size() << endl;
//
//	//cin.get();
//	// return height x width
//	return polygon.size();
//}

void DrawingRecognition::matchTMPL(const Mat &search, const Mat &tmpl)
{
	double minVal;
	double maxVal;
	Point minLoc;
	Point maxLoc;

	Mat match;
	Mat display(search);

	matchTemplate(search, tmpl, match, TM_CCOEFF);
	minMaxLoc(match, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
	cout << "maxVal: " << maxVal << " minVal: " << minVal << endl;

	rectangle(display, maxLoc, Point(maxLoc.x + tmpl.cols, maxLoc.y + tmpl.rows), Scalar::all(0), 2, 8, 0);

	imshow("1", display);
	waitKey();
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