//------------------------------------------------------------------------------
// ObjectRecognition.cpp
// Created by Kunlakan Cherdchusilp
// Created on 11/16/2016
//------------------------------------------------------------------------------
// ASSUMPTION:
//		- All templates used must be in grayscale.
//		- input must be in grayscale.
//------------------------------------------------------------------------------

#include "ObjectRecognition.h"

//----------------------------- Default Constructor ----------------------------
ObjectRecognition::ObjectRecognition()
{
}

//------------------------------------------------------------------------------
ObjectRecognition::ObjectRecognition(Mat input)
{
    this->input = input;
}

//------------------------------------------------------------------------------
ObjectRecognition::~ObjectRecognition()
{
}

//------------------------------ edgeDetection() -------------------------------
void ObjectRecognition::edgeDetection()
{
	double sigmaX = 2.0;
	double sigmaY = 2.0;
	double threshold1 = 20;
	double threshold2 = 60;

	flip(input, input, 1);
	GaussianBlur(input, input, Size(7, 7), sigmaX, sigmaY);
	Canny(input, input, threshold1, threshold2);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
float ObjectRecognition::hausdorffDistance(const vector<Point> &a, const vector<Point> &b)
{
	//findContours of inputs and template image.

	HausdorffDistanceExtractor* hd = createHausdorffDistanceExtractor();

	float distanceAB = hd->computeDistance(a, b);
	float distanceBA = hd->computeDistance(b, a);

	delete(hd);

	return max(distanceAB, distanceBA);
}