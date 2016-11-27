//------------------------------------------------------------------------------
// TemplateLibrary.h
// Created by Kulsoom Mansoor
// Created on 11/26/2016
//------------------------------------------------------------------------------
// NOTE:
//	-Keys of the map will be formed using the min and max stroke values: "min:max"
//	-The value for each key is a vector containing TemplateImage objects whose
//	 min and max strokes are the same as the key.
//------------------------------------------------------------------------------
#pragma once

#ifndef __TemplateLibrary__
#define __TemplateLibrary__

#include "TemplateImage.h"
#include <map>
#include <vector>

using namespace cv;
using namespace std;

class TemplateLibrary {

public:
	TemplateLibrary();

	void addTemplateImage(const TemplateImage&);

	TemplateImage removeTemplateImage(const int, const int, const string imageName); 

	string getMinMaxKey(const string) const; 
	TemplateImage getTemplateImage(const int, const int, const string imageName) const; 
	vector<TemplateImage> getTemplateImageList(const int, const int) const; 

	vector<string> getAllKeys() const; 
	vector<TemplateImage> getAllTemplateImages() const; 

	vector<TemplateImage> removeTemplateImageList(const int, const int); 

	void emptyLibrary(); 

	bool isEmpty() const; 

	int getNumberOfKeys() const;

	int getNumberOfTemplateImages() const;

	void printLibrary();

private:
	std::map<string, vector<TemplateImage>> library;

};

#endif /* defined(__TemplateLibrary__) */