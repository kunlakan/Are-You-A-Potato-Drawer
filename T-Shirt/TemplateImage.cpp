//------------------------------------------------------------------------------
// TemplateImage.cpp
// Created by Kulsoom Mansoor
// Created on 11/23/2016
//------------------------------------------------------------------------------
#include "TemplateImage.h"

TemplateImage::TemplateImage(string filename, int corners) {
	this->image = imread(filename, IMREAD_GRAYSCALE);

	this->imageName = filename;
	setNumOfCorners(corners);
}

int TemplateImage::getNumOfCorners() const{
	return this->numOfCorners;
}
void TemplateImage::setNumOfCorners(int newCorners) {
	if (newCorners <= 0) {
		this->numOfCorners = 1;
	}
	else {
		this->numOfCorners = newCorners;
	}
}

Mat TemplateImage::getImage() const {
	return this->image;
}
void TemplateImage::setImage(const Mat &newImage) {
	this->image = newImage;
}

string TemplateImage::getImageName() const {
	return this->imageName;
}
void TemplateImage::setImageName(const string newName){
	this->imageName = newName;
}

void TemplateImage::setImageAndImageName(const Mat &newImage, const string newName) {
	this->imageName = newName;
	this->image = newImage;
}