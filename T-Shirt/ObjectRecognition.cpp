//------------------------------------------------------------------------------
// ObjectRecognition.cpp
// Created by Kunlakan Cherdchusilp
// Created on 11/16/2016
//------------------------------------------------------------------------------
//
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
    input = cvtColor(input, input, COLOR_BGR2GRAY);
}

//------------------------------------------------------------------------------
ObjectRecognition::~ObjectRecognition()
{
}

//------------------------------ edgeDetection() -------------------------------
ObjectRecognition::edgeDetection(){
    double sigmaX = 2.0, sigmaY = 2.0;
	double threshold1 = 20, threshold2 = 60;

	flip(input, input, 1);
	cvtColor(input, input, COLOR_BGR2GRAY);
	GaussianBlur(input, input, Size(7, 7), sigmaX, sigmaY);
	Canny(input, input, threshold1, threshold2);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int ObjectRecognition::hausdorffDistance(const vector<Point> &a, const vector<Point> &b){
    return max(getDistance(a, b), getDistance(b, a));
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int ObjectRecognition::getDistance(const vector<Point> &a, const vector<Point> &b){
    int maxDistance = 0;
    int minB = 0;
    
    for()
}