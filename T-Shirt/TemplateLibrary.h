//------------------------------------------------------------------------------
// TemplateLibrary.h
// Created by Kulsoom Mansoor
// Created on 11/26/2016
//------------------------------------------------------------------------------
// NOTE:
//	-Keys of the map are int values representing the number of contours for the
//   shape
//	-The value for each key is a vector containing TemplateImage objects whose
//	 min and max strokes are the same as the key.
// IMPORTANT NOTE!!!!!
//	-images filenames should be in this format: shape_contours_id.jpg
//	-the id is optional, so without the id it would look like: shape_contours.jpg
// TODO:
//	-make sure code works with Jeen and Jessica
//	-create method to delete shape when that shape in not in library?
//	-make method to prevent duplicates?
//-------------------------------------------------------------------------------
#pragma once

#ifndef __TemplateLibrary__
#define __TemplateLibrary__

#include "TemplateImage.h"
#include <map>
#include <vector>
#include <set>

using namespace cv;
using namespace std;

class TemplateLibrary {

public:
	TemplateLibrary();
	void createLibrary();

	void addTemplateImage(const TemplateImage&);

	bool removeTemplateImage(const int&, const string &imageName); 

	int getContoursKey(const string&) const; 
	TemplateImage getTemplateImage(const int &corners, const string &imageName) const;
	vector<TemplateImage> getTemplateImageList(const int&) const; 

	vector<int> getAllKeys() const; 
	vector<TemplateImage> getAllTemplateImages() const; 

	bool removeTemplateImageList(const int&); 

	bool emptyLibrary(); 

	bool isEmpty() const; 

	int getNumberOfKeys() const;

	int getNumberOfTemplateImages() const;

	void printLibrary() const;

	string getTemplateImageFolderPath() const;

	vector<string> getAllShapes() const;

private:
	std::map<int, vector<TemplateImage>> library;
	set<string> shapes; 
	string templateImageFolderPath = "template_images/*.jpg";
};

#endif /* defined(__TemplateLibrary__) */