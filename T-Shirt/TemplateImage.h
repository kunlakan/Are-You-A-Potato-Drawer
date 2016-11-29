//------------------------------------------------------------------------------
// TemplateImage.h
// Created by Kulsoom Mansoor
// Created on 11/23/2016
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

	TemplateImage(string, int);

	int getNumOfCorners() const;
	void setNumOfCorners(int);

	Mat getImage() const;
	void setImage(const Mat &newImage);

	string getImageName() const;
	void setImageName(const string newName);
	void setImageAndImageName(const Mat &newImage, const string newName);

private:
	int numOfCorners = 1;
	Mat image;
	string imageName;
};

#endif /* defined(__TemplateImage__) */