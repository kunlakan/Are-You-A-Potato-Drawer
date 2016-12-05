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
	TemplateImage();
	TemplateImage(const string&);

	int getNumOfContours() const;
	void setNumOfContours(const int&);

	Mat getImage() const;
	void setImage(const Mat &newImage);

	string getImageName() const;
	void setImageName(const string &newName);
	void setImageAndImageName(const Mat &newImage, const string &newName);

	string getShape() const;
	void setShape(const string&);

private:
	int numOfContours = 1;
	Mat image;
	string imageName;
	string shape = "";

	vector<string> parseFilename(const string&) const;
};

#endif /* defined(__TemplateImage__) */