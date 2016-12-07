//------------------------------------------------------------------------------
// TemplateImage.h
// Created by Kulsoom Mansoor
// Created on 11/23/2016
// IMPORTANT NOTE!!!!!
//	-images filenames should be in this format: shape_contours_id.jpg
//	-the id is optional, so without the id it would look like: shape_contours.jpg
//------------------------------------------------------------------------------
#pragma once

#ifndef __TemplateImage__
#define __TemplateImage__

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include <iostream>
using namespace cv;
using namespace std;

class TemplateImage {

public:

	//----------------------------- default constructor ------------------------
	// Creates an empty TemplateImage
	//
	// Pre-conditions: none
	// Post-conditions:
	// An empty TemplateImage is created
	//--------------------------------------------------------------------------
	TemplateImage();

	//----------------------------- One Parameter Constructor ------------------
	// Creates TemplateImage based on the image filename passed. The name, shape
	// and number of contours is also saved all based on the filename passed in.
	//
	// Pre-conditions: 
	// The filename must be the path of the file. The filename must also be 
	// formatted like this: shapeName_numberOfContours or 
	// shapeName_numberOfContours_id. The id is only used when there are multiple 
	// images with the same shape and same number of contours.
	// 
	// Post-conditions:
	// Based on the filename, the Mat of the image, image name, shape of image, 
	// and number of contours in the image are stored. If the filename doesn't
	// follow the pre-conditions, then it will cause an error.
	//--------------------------------------------------------------------------
	TemplateImage(const string&);

	//----------------------------- getNumOfContours() -------------------------
	// returns the number of contours of the image
	//
	// Pre-conditions: none
	// Post-conditions:
	// returns the number of contours of the image
	//--------------------------------------------------------------------------
	int getNumOfContours() const;

	//----------------------------- setNumOfContours() -------------------------
	// Sets the number of contours of an image to the value passed in.
	//
	// Pre-conditions: 
	// The argument passed in has to be greater than zero
	// 
	// Post-conditions:
	// If the pre-condition is not fullfilled, then the number of contours for 
	// image is set to one. If the pre-condition is fulfilled then, the number of
	// contours of the image is set to the argument.
	//--------------------------------------------------------------------------
	void setNumOfContours(const int&);

	//----------------------------- getImage() ---------------------------------
	// returns the image as a Mat
	//
	// Pre-conditions: none
	// Post-conditions:
	// returns the image as a Mat
	//--------------------------------------------------------------------------
	Mat getImage() const;

	//----------------------------- setImage() ---------------------------------
	// sets the image to the Mat argument passed in
	//
	// Pre-conditions:
	// The Mat argument passed in should be a proper Mat for a TemplateImage
	//
	// Post-conditions:
	// Sets the image to the Mat argument passed in
	//--------------------------------------------------------------------------
	void setImage(const Mat &newImage);

	//----------------------------- getImageName() -----------------------------
	// returns the full path and name of the image
	//
	// Pre-conditions: none
	// Post-conditions:
	// returns the full path and name of the image
	//--------------------------------------------------------------------------
	string getImageName() const;

	//----------------------------- setImageName() -----------------------------
	// sets the image name to the string passed in
	//
	// Pre-conditions: 
	// The string passed in should not be an empty string.
	//
	// Post-conditions:
	// sets the image name to the string passed in
	//--------------------------------------------------------------------------
	void setImageName(const string &newName);

	//----------------------------- setImageAndImageName() ---------------------
	// sets the image and image name to the first and second arguments 
	// respectively.
	//
	// Pre-conditions: 
	// Post-conditions:
	// An empty TemplateImage is created
	//--------------------------------------------------------------------------
	void setImageAndImageName(const Mat &newImage, const string &newName);

	//----------------------------- getShape() ---------------------------------
	// returns the shape of the image.
	//
	// Pre-conditions: none
	// Post-conditions:
	// returns the shape of the image.
	//--------------------------------------------------------------------------
	string getShape() const;

private:
	int numOfContours = 1; //stores number of contours of image
	Mat image; //will store the image 
	string imageName; //store the imageName
	string shape = ""; //will store the shape of the image

	//----------------------------- parseFilename() ----------------------------
	// This is a private method, that parses the filename string passed in.
	//
	// Pre-conditions: 
	// The filename must be the path of the file. The filename must also be 
	// formatted like this: shapeName_numberOfContours or 
	// shapeName_numberOfContours_id. The id is only used when there are multiple 
	// images with the same shape and same number of contours.
	// 
	// Post-conditions:
	// If the pre-conditions are not followed, then an empty string vector will 
	// return. If the pre-conditions are followed, then this method will parse
	// out the filename from the file path passed in. It will then parse filename
	// using an underscore as the delimiter and saving the results into a string
	// vector. The string vector will then be returned
	//--------------------------------------------------------------------------
	vector<string> parseFilename(const string&) const;
};

#endif /* defined(__TemplateImage__) */