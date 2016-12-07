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

	//----------------------------- createLibrary() ----------------------------
	// automatically creates the library by getting all the images in a specified
	// folder. This method uses the folder path of the template images to get the 
	// images.
	//
	// pre-conditions:
	// The folder path must have a glob at the end. 
	// Example: "template_images/cropped/*.jpg". The "/*.jpg" is a glob and this 
	// must be present at the end of every folder path.
	// The template images MUST be names like: shape_contours_id.jpg or 
	// shape_contours.jpg.
	//
	// post-conditions:
	// If the pre-conditions are not satisfied, then this method will not work. 
	// if the pre-conditions are satisfied, then this method will create the 
	// library using the template images found in the specified folder.
	//--------------------------------------------------------------------------
	void createLibrary();

	//----------------------------- addTemplateImage() -------------------------
	// Adds a template object to the library.
	//
	// Pre-condition:
	// The argument passed in should not be null and have proper number of 
	// corners
	//
	// Post-condition:
	// The number of corners of the template image will be used as a key. If
	// the key already exists, then the template image added to the vector 
	// associated with the key. If the key doesn't exist, then a new key is 
	// created along with
	// its associated vector. The template image is then added to the new vector.
	//--------------------------------------------------------------------------
	void addTemplateImage(const TemplateImage&);

	//----------------------------- removeTemplateImage() ----------------------
	// removes a template object to the library.
	//
	// Pre-condition:
	// The first argument is the number of corners of the template image. 
	// This key has to exist in the map
	// or the method will return false. The second argument is for the name of the
	// template image. There must be a template image with this name in the map or 
	// else 
	// the method will return false. The map must not be empty, or else the method 
	// will return false
	//
	// Post-condition:
	// If the key formed by the first argument exists and the image name also
	// exists, then that template image will be deleted from the map. This method
	// returns true. 
	//--------------------------------------------------------------------------
	bool removeTemplateImage(const int&, const string &imageName); 

	//----------------------------- getContoursKey() ---------------------------
	// Returns the key of a TemplateImage by passing in the TemplateImage's name
	//
	// Pre-condition:
	// The argument passed in should be a name of an existing TemplateImage in the
	// map, or the method will return -1.
	//
	// Post-condition:
	// If the map has an TemplateImage with the name same as the argument passed 
	// in, then they key of that TemplateImage is passed in.
	//--------------------------------------------------------------------------
	int getContoursKey(const string&) const; 

	//----------------------------- getTemplateImage() -------------------------
	// Returns the TemplateImage whose key is formed by the first argument passed
	// in and whose name matches the second argument passed.
	//
	// Pre-condition:
	// The first argument passed is used as a key. This key
	// should exist in the map, or else an empty TemplateImage will be returned. 
	// The second argument
	// is the name of the TemplateImage you are searching for. This name must  
	// exist in the map or else an empty TemplateImage object will be returned.
	//
	// Post-condition:
	// If the key formed by the first argument exist and if the name of the 
	// TemplateImage exists, then the corresponding TemplateImage is returned.
	//--------------------------------------------------------------------------
	TemplateImage getTemplateImage(const int &corners, const string &imageName) 
		const;

	//----------------------------- getTemplateImageList() ---------------------
	// Returns a vector<TemplateImage> using the two arguments passed in.
	//
	// Pre-condition:
	// The argument passed in are using to form the key. This key must exist
	// in the map, or else an empty vector<TemplateImage> will be returned.
	//
	// Post-condition:
	// If the key formed by the argument passed in exists, then a vector 
	// containing all the TemplateImage objects will be returned.
	//--------------------------------------------------------------------------
	vector<TemplateImage> getTemplateImageList(const int&) const; 

	//----------------------------- getAllKeys() -------------------------------
	// Returns all the keys in the map.
	//
	// Pre-condition:
	// The map should not be empty, or else an empty vector<int> will be 
	// returned.
	//
	// Post-condition:
	// If the map is not empty, a vector containing all the keys is returned.
	//--------------------------------------------------------------------------
	vector<int> getAllKeys() const;

	//----------------------------- getAllTemplateImages() ---------------------
	// Returns all the TemplateImage objects in the map.
	//
	// Pre-condition:
	// The map should not be empty, or else an empty vector will be returned.
	//
	// Post-condition:
	// If the map is not empty, a vector containing all the TemplateImage 
	// objects is returned.
	//--------------------------------------------------------------------------
	vector<TemplateImage> getAllTemplateImages() const; 

	//----------------------------- removeTemplateImageList() ------------------
	// Removes the value of a key in the map. The value is a vector of 
	// TemplateImage objects.
	//
	// Pre-condition:
	// The argument passed in is used to create the key. This key must
	// exist in the map or else the method will return false.
	//
	// Post-condition:
	// If the the key formed using the argument passed in exists in the map, then
	// value of that key is deleted from the map. This value is a vector containing
	// all the TemplateImages of that key. This method returns the deleted vector.
	//--------------------------------------------------------------------------
	bool removeTemplateImageList(const int&); 

	//----------------------------- emptyLibrary() -----------------------------
	// Deletes all the elements in the map.
	//
	// Pre-condition:
	// The map should not be empty, or else the method will return false.
	//
	// Post-condition:
	// If the map is not empty, all the elements are deleted from the map.
	//--------------------------------------------------------------------------
	bool emptyLibrary(); 

	//----------------------------- isEmpty() ----------------------------------
	// Checks if the map is empty
	//
	// Pre-condition:
	// none
	//
	// Post-condition:
	// Will return true or false, depending if the map is empty or not.
	//--------------------------------------------------------------------------
	bool isEmpty() const; 

	//----------------------------- getNumberOfKeys() --------------------------
	// Returns the number of keys in the map.
	//
	// Pre-condition:
	// none.
	//
	// Post-condition:
	// If the map is not empty, the total number of keys in the map is returned.
	//--------------------------------------------------------------------------
	int getNumberOfKeys() const;

	//----------------------------- getNumberOfTemplateImages() ----------------
	// Returns the total number of TemplateImage objects in the map.
	//
	// Pre-condition:
	// none
	//
	// Post-condition:
	// If the map is not empty, the total number of TemplateObjects in the map 
	// is returned.
	//--------------------------------------------------------------------------
	int getNumberOfTemplateImages() const;

	//----------------------------- printLibrary() -----------------------------
	// prints the content of the map to screen.
	//
	// Pre-condition:
	// The map should not be empty, or else an error message will be printed out
	//
	// Post-condition:
	// If the map is not empty, each key with its corresponding value is printed to
	// screen. The value is a vector of TemplateImage objects, so the name of each
	// object is printed.
	//--------------------------------------------------------------------------
	void printLibrary() const;

	//----------------------------- getTemplateImageFolderPath() ---------------
	// returns the folder path of the template images.
	//
	// pre-conditions:
	// none
	//
	// post-conditions:
	// returns the folder path of the template images.
	//--------------------------------------------------------------------------
	string getTemplateImageFolderPath() const;

	//----------------------------- getAllShapes() -----------------------------
	//returns a vector of all types of shapes in the library
	//
	//pre-conditions:
	//The map must not be empty, or else an empty vector will be returned
	//
	//post-conditions:
	//If the map is not empty, then a vector of strings containing the type of
	//shapes will be returned.
	//--------------------------------------------------------------------------
	vector<string> getAllShapes() const;

private:
	std::map<int, vector<TemplateImage>> library; //stores the Template images
	set<string> shapes; //stores the shapes that are in the library

	//stores the path to the template images folder
	string templateImageFolderPath = "template_images/*.jpg"; 
};

#endif /* defined(__TemplateLibrary__) */