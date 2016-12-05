//------------------------------------------------------------------------------
// TemplateImage.cpp
// Created by Kulsoom Mansoor
// Created on 11/23/2016
// IMPORTANT NOTE!!!!!
//	-images filenames should be in this format: shape_contours_id.jpg
//	-the id is optional, so without the id it would look like: shape_contours.jpg
//------------------------------------------------------------------------------
#include "TemplateImage.h"

TemplateImage::TemplateImage() {
	this->image = NULL;
	this->imageName = "";
	this->shape = "";
	this->numOfContours = 0;
}

TemplateImage::TemplateImage(const string& filename) {
	this->image = imread(filename, IMREAD_GRAYSCALE);

	vector<string> parsed = this->parseFilename(filename);
	this->imageName = filename;
	setNumOfContours(stoi(parsed[1]));
	this->shape = parsed[0];
}

vector<string> TemplateImage::parseFilename(const string &str) const{
	string fn = str;

	while (fn.find("/") != string::npos) {
		fn = fn.substr(fn.find("/") + 1);
	}
	vector<string> strings;
	istringstream f(fn);
	string s;
	while (getline(f, s, '_')) {
		strings.push_back(s);
	}

	return strings;
}

int TemplateImage::getNumOfContours() const{
	return this->numOfContours;
}
void TemplateImage::setNumOfContours(const int &newContours) {
	if (newContours <= 0) {
		this->numOfContours = 1;
	}
	else {
		this->numOfContours = newContours;
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
void TemplateImage::setImageName(const string &newName){
	this->imageName = newName;
}

void TemplateImage::setImageAndImageName(const Mat &newImage, const string &newName) {
	this->imageName = newName;
	this->image = newImage;
}

string TemplateImage::getShape() const {
	return this->shape;
}

void TemplateImage::setShape(const string &shape) {
	this->shape = shape;
}