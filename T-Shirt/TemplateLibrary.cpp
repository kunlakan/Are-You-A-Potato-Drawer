//------------------------------------------------------------------------------
// TemplateLibrary.cpp
// Created by Kulsoom Mansoor
// Created on 11/26/2016
//------------------------------------------------------------------------------
// NOTE:
//	-Keys of the map are int values representing the number of corners for the
//   shape
//	-The value for each key is a vector containing TemplateImage objects whose
//	 min and max strokes are the same as the key.
// IMPORTANT NOTE!!!!!
//	-images filenames should be in this format: shape_contours_id.jpg
//	-the id is optional, so without the id it would look like: shape_contours.jpg
//-------------------------------------------------------------------------------
#include "TemplateLibrary.h"

TemplateLibrary::TemplateLibrary() {}

/*
createLibrary()
automatically creates the library by getting all the images in a specified
folder. This method uses the folder path of the template images to get the 
images.

pre-conditions:
The folder path must have a glob at the end. 
Example: "template_images/cropped/*.jpg". The "/*.jpg" is a glob and this must
be present at the end of every folder path.
The template images MUST be names like: shape_contours_id.jpg or shape_contours.jpg.

post-conditions:
If the pre-conditions are not satisfied, then this method will not work. If the
pre-conditions are satisfied, then this method will create the library using
the template images found in the specified folder.
*/
void TemplateLibrary::createLibrary() {
	vector<cv::String> filenames; //will store the filenames
	glob(this->templateImageFolderPath, filenames, false); //will get the filenames

	string s = "";
	string newS = "";

	int count = static_cast<int>(filenames.size());
	//The glob method will return the filename like this: folder1/folder2\filename.jpg
	//So I am changing the the backslash into a forward slash to make it a proper
	//file path name
	for (int i = 0; i < count; i++) {
		s = filenames[i].substr(filenames[i].find("\\"));
		newS = filenames[i].substr(0, filenames[i].find("\\")) + "/" + s.substr(s.find("\\") + 1);

		filenames[i] = newS;
	}

	//the filenames are passed into a TemplateImage constructor and that
	//TemplateImage is added to the library
	for (int j = 0; j < count; j++) {
		TemplateImage newImage(filenames[j]);
		this->addTemplateImage(newImage);
	}
}

/*
addTemplateImage()
Adds a template object to the library.

Pre-condition:
The argument passed in should not be null and have proper number of corners

Post-condition:
The number of corners of the template image will be used as a key. If
the key already exists, then the template image added to the vector associated
with the key. If the key doesn't exist, then a new key is created along with
its associated vector. The template image is then added to the new vector.
*/
void TemplateLibrary::addTemplateImage(const TemplateImage& image) {

	int key = image.getNumOfContours();
	this->shapes.insert(image.getShape());

	if (this->library.count(key) == 0) {
		vector<TemplateImage> newShape;
		newShape.push_back(image);

		this->library[key] = newShape;
	}
	else {
		this->library.at(key).push_back(image);
	}
}

/*
removeTemplateImage()
removes a template object to the library.

Pre-condition:
The first argument is the number of corners of the template image. 
This key has to exist in the map
or the method will return false. The second argument is for the name of the
template image. There must be a template image with this name in the map or else 
the method will return false. The map must not be empty, or else the method will
return false

Post-condition:
If the key formed by the first argument exists and the image name also
exists, then that template image will be deleted from the map. This method
returns true. 
*/
bool TemplateLibrary::removeTemplateImage(const int corners, const string imageName) {
	int key = corners;

	if (this->library.empty()) {
		return false;
	}
	else if (this->library.count(key) != 0) {
		vector<TemplateImage> ref = this->library.at(key);

		for(int i = 0; i < ref.size(); i++){
			TemplateImage img = ref[i]; 
			if (img.getImageName().compare(imageName) == 0) {
				this->library.at(key).erase(this->library.at(key).begin() + i);
				return true;
			}
		}

		return false;
	}
	else {
		return false;
	}
}

/*
getMinMaxKey()
Returns the key of a TemplateImage by passing in the TemplateImage's name

Pre-condition:
The argument passed in should be a name of an existing TemplateImage in the
map, or the method will return -1.

Post-condition:
If the map has an TemplateImage with the name same as the argument passed in,
then they key of that TemplateImage is passed in.
*/
int TemplateLibrary::getContoursKey(const string imageName) const {

	if (this->library.empty()) {
		return -1;
	}
	else {
		map<int, vector<TemplateImage>>::const_iterator elm;
		for (elm = this->library.begin(); elm != this->library.end(); ++elm) {
			int key = elm->first;
			vector<TemplateImage> val = this->library.at(key);

			for (int i = 0; i < val.size(); i++) {
				if (val[i].getImageName().compare(imageName) == 0) {
					return key;
				}
			}
		}

		return -1;
	}
}

/*
getTemplateImage()
Returns the TemplateImage whose key is formed by the first argument passed
in and whose name matches the second argument passed.

Pre-condition:
The first argument passed is used as a key. This key
should exist in the map, or else an empty TemplateImage will be returned. The second argument
is the name of the TemplateImage you are searching for. This name must exist in
the map or else an empty TemplateImage object will be returned.

Post-condition:
If the key formed by the first argument exist and if the name of the 
TemplateImage exists, then the corresponding TemplateImage is returned.
*/
TemplateImage TemplateLibrary::getTemplateImage(int corners, string imageName) const {
	int key = corners;

	if (this->library.empty()) {
		TemplateImage empty;
		return empty; 
	}
	else if (this->library.count(key) != 0) {
		vector<TemplateImage> ref = this->library.at(key);

		vector<TemplateImage>::const_iterator elm;
		for (elm = ref.begin(); elm != ref.end(); ++elm) {
			TemplateImage img = *elm; 
			if (img.getImageName().compare(imageName) == 0) {
				return img;
			}
		}

		TemplateImage empty;
		return empty;
	}
	else {
		TemplateImage empty;
		return empty;
	}
}

/*
getTemplateImageList()
Returns a vector<TemplateImage> using the two arguments passed in.

Pre-condition:
The argument passed in are using to form the key. This key must exist
in the map, or else an empty vector<TemplateImage> will be returned.

Post-condition:
If the key formed by the argument passed in exists, then a vector containing all
the TemplateImage objects will be returned.
*/
vector<TemplateImage> TemplateLibrary::getTemplateImageList(const int corners) const {
	int key = corners;

	if (this->library.empty()) {
		vector<TemplateImage> empty;
		return empty;
	}
	else if (this->library.count(key) != 0) {
		return this->library.at(key);
	}
	else {
		return this->getAllTemplateImages();
	}
}

/*
getAllKey()
Returns all the keys in the map.

Pre-condition:
The map should not be empty, or else an empty vector<int> will be returned.

Post-condition:
If the map is not empty, a vector containing all the keys is returned.
*/
vector<int> TemplateLibrary::getAllKeys() const {
	if (this->library.empty()) {
		vector<int> empty;
		return empty;
	}
	else {
		vector<int> keys;

		map<int, vector<TemplateImage>>::const_iterator key;
		for (key = this->library.begin(); key != this->library.end(); ++key) {
			keys.push_back(key->first);
		}

		return keys;
	}

}

/*
getAllTemplateImages()
Returns all the TemplateImage objects in the map.

Pre-condition:
The map should not be empty, or else an empty vector will be returned.

Post-condition:
If the map is not empty, a vector containing all the TemplateImage objects is 
returned.
*/
vector<TemplateImage> TemplateLibrary::getAllTemplateImages() const {
	if (this->library.empty()) {

		vector<TemplateImage> empty;
		return empty;
	}
	else {
		vector<TemplateImage> images;

		map<int, vector<TemplateImage>>::const_iterator elm;
		for (elm = this->library.begin(); elm != this->library.end(); ++elm) {
			int key = elm->first;
			vector<TemplateImage> val = this->library.at(key);

			vector<TemplateImage>::const_iterator elm;
			for (elm = val.begin(); elm != val.end(); ++elm) {
				images.push_back(*elm);
			}
		}

		return images;
	}
}

/*
removeTemplateImageList()
Removes the value of a key in the map. The value is a vector of TemplateImage
objects.

Pre-condition:
The argument passed in is used to create the key. This key must
exist in the map or else the method will return false.

Post-condition:
If the the key formed using the argument passed in exists in the map, then
value of that key is deleted from the map. This value is a vector containing
all the TemplateImages of that key. This method returns the deleted vector.
*/
bool TemplateLibrary::removeTemplateImageList(const int corners) {
	if (this->library.empty()) {
		return false;
	}
	else {
		int key = corners;

		if (this->library.count(key) != 0) {
			vector<TemplateImage> ref = this->library.at(key);
			this->library.at(key).clear();
			this->library.erase(key);
			return true;
		}
		else {
			return false;
		}
	}
}

/*
emptyLibrary()
Deletes all the elements in the map.

Pre-condition:
The map should not be empty, or else the method will return false.

Post-condition:
If the map is not empty, all the elements are deleted from the map.
*/
bool TemplateLibrary::emptyLibrary() {
	if (this->library.empty()) {
		cout << "Library empty" << endl;
		return false;
	}
	else {

		map<int, vector<TemplateImage>>::const_iterator elm;
		for (elm = this->library.begin(); elm != this->library.end(); ++elm) {
			int key = elm->first;
			this->library.at(key).clear();
		}

		this->library.clear();

		this->shapes.clear();

		return true;
	}
}

/*
isEmpty()
Checks if the map is empty

Pre-condition:
none

Post-condition:
Will return true or false, depending if the map is empty or not.
*/
bool TemplateLibrary::isEmpty() const {
	return this->library.empty();
}

/*
getNumberOfKeys()
Returns the number of keys in the map.

Pre-condition:
none.

Post-condition:
If the map is not empty, the total number of keys in the map is returned.
*/
int TemplateLibrary::getNumberOfKeys() const {
	return static_cast<int>(this->library.size());
}

/*
getAllTemplateImages()
Returns the total number of TemplateImage objects in the map.

Pre-condition:
none

Post-condition:
If the map is not empty, the total number of TemplateObjects in the map is
returned.
*/
int TemplateLibrary::getNumberOfTemplateImages() const {
	int count = 0;

	if (this->library.empty()) {
		return 0;
	}
	else {

		map<int, vector<TemplateImage>>::const_iterator elm;
		for (elm = this->library.begin(); elm != this->library.end(); ++elm) {
			int key = elm->first;
			vector<TemplateImage> val = this->library.at(key);

			for (int i = 0; i < val.size(); i++) {
				count++;
			}
		}

		return count;
	}
}

/*
printLibrary()
prints the content of the map to screen.

Pre-condition:
The map should not be empty, or else an error message will be printed out

Post-condition:
If the map is not empty, each key with its corresponding value is printed to
screen. The value is a vector of TemplateImage objects, so the name of each
object is printed.
*/
void TemplateLibrary::printLibrary() const{
	if (this->library.empty()) {
		cout << "Library empty" << endl;
	}
	else {
		map<int, vector<TemplateImage>>::const_iterator elm;
		for (elm = this->library.begin(); elm != this->library.end(); ++elm) {
			int key = elm->first;

			std::cout << "Key: " << elm->first << endl;
			vector<TemplateImage> val = this->library.at(key);

			std::cout << "	Value: ";
			for (int i = 0; i < val.size(); i++) {
				std::cout << val[i].getImageName() << ", ";
			}
			std::cout << "" << endl;
		}
	}
}

/*
getTemplateImageFolderPath()
returns the folder path of the template images.

pre-conditions:
none

post-conditions:
returns the folder path of the template images.
*/
string TemplateLibrary::getTemplateImageFolderPath() const {
	return this->templateImageFolderPath;
}

/*
getAllShapes()
returns a vector of all types of shapes in the library

pre-conditions:
The map must not be empty, or else an empty vector will be returned

post-conditions:
If the map is not empty, then a vector of strings containing the type of
shapes will be returned.
*/
vector<string> TemplateLibrary::getAllShapes() const {
	if (this->library.empty()) {
		vector<string> empty;
		return empty;
	}
	else {
		set<string>::const_iterator elm;
		vector<string> shapes;
		for (elm = this->shapes.begin(); elm != this->shapes.end(); ++elm) {
			shapes.push_back(*elm);
		}
		return shapes;
	}
}