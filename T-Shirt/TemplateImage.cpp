//------------------------------------------------------------------------------
// TemplateImage.cpp
// Created by Kulsoom Mansoor
// Created on 11/23/2016
// IMPORTANT NOTE!!!!!
//	-images filenames should be in this format: shape_contours_id.jpg
//	-the id is optional, so without the id it would look like: shape_contours.jpg
//------------------------------------------------------------------------------
#include "TemplateImage.h"

//----------------------------- default constructor ----------------------------
// Creates an empty TemplateImage
//
// Pre-conditions: none
// Post-conditions:
// An empty TemplateImage is created
//------------------------------------------------------------------------------
TemplateImage::TemplateImage() 
{
	this->image = NULL;
	this->imageName = "";
	this->shape = "";
	this->numOfContours = 0;
}

//----------------------------- One Parameter Constructor ----------------------
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
// Based on the filename, the Mat of the image, image name, shape of image, and
// number of contours in the image are stored. If the filename doesn't
// follow the pre-conditions, then it will cause an error.
//------------------------------------------------------------------------------
TemplateImage::TemplateImage(const string& filename) 
{
	//reads image as gray scale
	this->image = imread(filename, IMREAD_GRAYSCALE);

	//parses the file name
	vector<string> parsed = this->parseFilename(filename);
	this->imageName = filename; //stores file name/path
	setNumOfContours(stoi(parsed[1])); //saves the number of contours
	this->shape = parsed[0]; //saves the shape of the image
}

//----------------------------- parseFilename() --------------------------------
// This is a private method, that parses the filename string passed in.
//
// Pre-conditions: 
// The filename must be the path of the file. The filename must also be 
// formatted like this: shapeName_numberOfContours or 
// shapeName_numberOfContours_id. The id is only used when there are multiple 
// images with the same shape and same number of contours.
// 
// Post-conditions:
// If the pre-conditions are not followed, then an empty string vector will be
// returned. If the pre-conditions are followed, then this method will parse
// out the filename from the file path passed in. It will then parse filename
// using an underscore as the delimiter and saving the results into a string
// vector. The string vector will then be returned
//------------------------------------------------------------------------------
vector<string> TemplateImage::parseFilename(const string &str) const
{
	string fn = str;

	//if there is a forward slash in the string, the the substring of everything
	//after the forward slash. Repeat until there are no more forward slashes
	//this will get the file name from the file path
	while (fn.find("/") != string::npos) 
	{
		fn = fn.substr(fn.find("/") + 1);
	}
	vector<string> strings;
	istringstream f(fn);
	string s;
	//parses the filename using an underscore as a delimiter and saves the
	//parsed values in a string vector
	while (getline(f, s, '_')) 
	{
		strings.push_back(s);
	}

	return strings;
}

//----------------------------- getNumOfContours() -----------------------------
// returns the number of contours of the image
//
// Pre-conditions: none
// Post-conditions:
// returns the number of contours of the image
//------------------------------------------------------------------------------
int TemplateImage::getNumOfContours() const
{
	return this->numOfContours;
}

//----------------------------- setNumOfContours() -----------------------------
// Sets the number of contours of an image to the value passed in.
//
// Pre-conditions: 
// The argument passed in has to be greater than zero
// 
// Post-conditions:
// If the pre-condition is not fullfilled, then the number of contours for the
// image is set to one. If the pre-condition is fulfilled then, the number of
// contours of the image is set to the argument.
//------------------------------------------------------------------------------
void TemplateImage::setNumOfContours(const int &newContours) 
{
	if (newContours <= 0) 
	{
		this->numOfContours = 1;
	}
	else 
	{
		this->numOfContours = newContours;
	}
}

//----------------------------- getImage() -------------------------------------
// returns the image as a Mat
//
// Pre-conditions: none
// Post-conditions:
// returns the image as a Mat
//------------------------------------------------------------------------------
Mat TemplateImage::getImage() const 
{
	return this->image;
}

//----------------------------- setImage() -------------------------------------
// sets the image to the Mat argument passed in
//
// Pre-conditions:
// The Mat argument passed in should be a proper Mat for a TemplateImage
//
// Post-conditions:
// Sets the image to the Mat argument passed in
//------------------------------------------------------------------------------
void TemplateImage::setImage(const Mat &newImage) 
{
	this->image = newImage;
}

//----------------------------- getImageName() ---------------------------------
// returns the full path and name of the image
//
// Pre-conditions: none
// Post-conditions:
// returns the full path and name of the image
//------------------------------------------------------------------------------
string TemplateImage::getImageName() const 
{
	return this->imageName;
}

//----------------------------- setImageName() ---------------------------------
// sets the image name to the string passed in
//
// Pre-conditions: 
// The string passed in should not be an empty string.
//
// Post-conditions:
// sets the image name to the string passed in
//------------------------------------------------------------------------------
void TemplateImage::setImageName(const string &newName)
{
	//if argument is an empty string, return
	if (newName.compare("") == 0) {
		return;
	}
	this->imageName = newName;
}

//----------------------------- setImageAndImageName() -------------------------
// sets the image and image name to the first and second arguments respectively.
//
// Pre-conditions: 
// Post-conditions:
// An empty TemplateImage is created
//------------------------------------------------------------------------------
void TemplateImage::setImageAndImageName(const Mat &newImage, 
	const string &newName)
{
	this->imageName = newName;
	//if newName is empty string, don't use it and return
	if (newName.compare("") == 0) {
		return;
	}
	this->image = newImage;
}

//----------------------------- getShape() -------------------------------------
// returns the shape of the image.
//
// Pre-conditions: none
// Post-conditions:
// returns the shape of the image.
//------------------------------------------------------------------------------
string TemplateImage::getShape() const 
{
	return this->shape;
}