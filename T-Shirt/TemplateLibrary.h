//------------------------------------------------------------------------------
// TemplateLibrary.h
// Created by Kulsoom Mansoor
// Created on 11/26/2016
//------------------------------------------------------------------------------
// NOTE:
//	-Keys of the map are int values representing the number of corners for the
//   shape
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

	TemplateImage removeTemplateImage(const int, const string imageName); 

	int getMinMaxKey(const string) const; 
	TemplateImage getTemplateImage(const int, const string imageName) const; 
	vector<TemplateImage> getTemplateImageList(const int) const; 

	vector<int> getAllKeys() const; 
	vector<TemplateImage> getAllTemplateImages() const; 

	vector<TemplateImage> removeTemplateImageList(const int); 

	void emptyLibrary(); 

	bool isEmpty() const; 

	int getNumberOfKeys() const;

	int getNumberOfTemplateImages() const;

	void printLibrary();

private:
	std::map<int, vector<TemplateImage>> library;

};

#endif /* defined(__TemplateLibrary__) */