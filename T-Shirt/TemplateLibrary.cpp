//------------------------------------------------------------------------------
// TemplateLibrary.cpp
// Created by Kulsoom Mansoor
// Created on 11/26/2016
//------------------------------------------------------------------------------
// NOTE:
//	-Keys of the map will be formed using the min and max stroke values: "min:max"
//	-The value for each key is a vector containing TemplateImage objects whose
//	 min and max strokes are the same as the key.
//------------------------------------------------------------------------------
#include "TemplateLibrary.h"

TemplateLibrary::TemplateLibrary() {}

/*
addTemplateImage()
Adds a template object to the library.

Pre-condition:
The argument passed in should not be null and have proper min and max strokes

Post-condition:
The min and max stokes of the template image will be used as a key: "min:max". If
the key already exists, then the template image added to the vector associated
with the key. If the key doesn't exist, then a new key is created along with
its associated vector. The template image is then added to the new vector.
*/
void TemplateLibrary::addTemplateImage(const TemplateImage& image) {
	string min = to_string(image.getMinStrokes());
	string max = to_string(image.getMaxStrokes());
	string key = min + ":" + max;

	
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
The first two arguments are the min and max strokes of the template image, 
respectively. They make the key "min:max". This key has to exist in the map
or else an error will be thrown. The third argument is for the name of the
template image. There must be a template image with this name or else an exception
will be thrown. The map must not be empty, or else an exception will be thrown

Post-condition:
If the key formed by the first two arguments exists and the image name also
exists, then that template image will be deleted from the map. This method
returns the deleted TemplateImage object. 
*/
TemplateImage TemplateLibrary::removeTemplateImage(const int min, const int max, const string imageName) {
	string minS = to_string(min);
	string maxS = to_string(max);
	string key = minS + ":" + maxS;

	if (this->library.empty()) {
		throw "Library is empty"; 
	}
	else if (this->library.count(key) != 0) {
		vector<TemplateImage> ref = this->library.at(key);

		for(int i = 0; i < ref.size(); i++){
			TemplateImage img = ref[i]; 
			if (img.getImageName().compare(imageName) == 0) {
				this->library.at(key).erase(this->library.at(key).begin() + i);
				return img;
			}
		}

		throw "No such element";  
	}
	else {
		throw "No such element"; 
	}
}

/*
getMinMaxKey()
Returns the key of a TemplateImage by passing in the TemplateImage's name

Pre-condition:
The argument passed in should be a name of an existing TemplateImage in the
map, or else an exception will be thrown.

Post-condition:
If the map has an TemplateImage with the name same as the argument passed in,
then they key of that TemplateImage is passed in.
*/
string TemplateLibrary::getMinMaxKey(const string imageName) const {

	if (this->library.empty()) {
		throw "Library is empty"; 
	}
	else {
		map<string, vector<TemplateImage>>::const_iterator elm;
		for (elm = this->library.begin(); elm != this->library.end(); ++elm) {
			string key = elm->first;
			vector<TemplateImage> val = this->library.at(key);

			for (int i = 0; i < val.size(); i++) {
				if (val[i].getImageName().compare(imageName) == 0) {
					return key;
				}
			}
		}

		throw "No such element";
	}
}

/*
getTemplateImage()
Returns the TemplateImage whose key is formed by the first two arguments passed
in and whose name matches the third argument passed.

Pre-condition:
The first two arguments passed are formed into a key: "min:max". This key
should exist in the map, or else an exception is thrown. The third argument
is the name of the TemplateImage you are searching for. This name must exist in
the map or else an exception is thrown.

Post-condition:
If the key formed by the first two arguments exist and if the name of the 
TemplateImage exists, then the corresponding TemplateImage is returned.
*/
TemplateImage TemplateLibrary::getTemplateImage(int min, int max, string imageName) const {
	string minS = to_string(min);
	string maxS = to_string(max);
	string key = minS + ":" + maxS;

	if (this->library.empty()) {
		throw "Library is empty"; 
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

		throw "No such element";  
	}
	else {
		throw "No such element"; 
	}
}

/*
getTemplateImageList()
Returns a vector<TemplateImage> using the two arguments passed in.

Pre-condition:
The arguments passed in are using to form the key: "min:max". This key must exist
in the map, or else an exception is thrown.

Post-condition:
If the key formed by the arguments passed in exists, then a vector containing all
the TemplateImage objects will be returned.
*/
vector<TemplateImage> TemplateLibrary::getTemplateImageList(const int min, const int max) const {
	string minS = to_string(min);
	string maxS = to_string(max);
	string key = minS + ":" + maxS;

	if (this->library.empty()) {
		throw "Library is empty"; 
	}
	else if (this->library.count(key) != 0) {
		return this->library.at(key);
	}
	else {
		throw "No such key"; 
	}
}

/*
getAllKey()
Returns all the keys in the map.

Pre-condition:
The map should not be empty, or else an exception is thrown.

Post-condition:
If the map is not empty, a vector containing all the keys is returned.
*/
vector<string> TemplateLibrary::getAllKeys() const {
	if (this->library.empty()) {
		throw "Library is empty";
	}
	else {
		vector<string> keys;

		map<string, vector<TemplateImage>>::const_iterator key;
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
The map should not be empty, or else an exception is thrown.

Post-condition:
If the map is not empty, a vector containing all the TemplateImage objects is 
returned.
*/
vector<TemplateImage> TemplateLibrary::getAllTemplateImages() const {
	if (this->library.empty()) {
		throw "Library is empty";
	}
	else {
		vector<TemplateImage> images;

		map<string, vector<TemplateImage>>::const_iterator elm;
		for (elm = this->library.begin(); elm != this->library.end(); ++elm) {
			string key = elm->first;
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
The arguments passed in are used to create the key: "min:max". This key must
exist in the map or else an exception will be thrown.

Post-condition:
The the key formed using the arguments passed in exists in the map, then
value of that key is deleted from the map. This value is a vector containing
all the TemplateImages of that key. This method returns the deleted vector.
*/
vector<TemplateImage> TemplateLibrary::removeTemplateImageList(const int min, const int max) {
	if (this->library.empty()) {
		throw "Library is empty";
	}
	else {
		string minS = to_string(min);
		string maxS = to_string(max);
		string key = minS + ":" + maxS;

		if (this->library.count(key) != 0) {
			vector<TemplateImage> ref = this->library.at(key);
			this->library.at(key).clear();
			this->library.erase(key);
			return ref;
		}
		else {
			throw "Key doesn't exist";
		}
	}
}

/*
emptyLibrary()
Deletes all the elements in the map.

Pre-condition:
The map should not be empty, or else an exception is thrown.

Post-condition:
If the map is not empty, all the elements are deleted from the map.
*/
void TemplateLibrary::emptyLibrary() {
	if (this->library.empty()) {
		throw "Library is empty";
	}
	else {

		map<string, vector<TemplateImage>>::const_iterator elm;
		for (elm = this->library.begin(); elm != this->library.end(); ++elm) {
			string key = elm->first;
			this->library.at(key).clear();
		}

		this->library.clear();
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
The map should not be empty, or else an exception is thrown.

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
The map should not be empty, or else an exception is thrown.

Post-condition:
If the map is not empty, the total number of TemplateObjects in the map is
returned.
*/
int TemplateLibrary::getNumberOfTemplateImages() const {
	int count = 0;

	if (this->library.empty()) {
		throw "Library is empty";
	}
	else {

		map<string, vector<TemplateImage>>::const_iterator elm;
		for (elm = this->library.begin(); elm != this->library.end(); ++elm) {
			string key = elm->first;
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
The map should not be empty, or else an exception is thrown.

Post-condition:
If the map is not empty, each key with its corresponding value is printed to
screen. The value is a vector of TemplateImage objects, so the name of each
object is printed.
*/
void TemplateLibrary::printLibrary() {
	if (this->library.empty()) {
		throw "Library is empty";
	}
	else {
		map<string, vector<TemplateImage>>::const_iterator elm;
		for (elm = this->library.begin(); elm != this->library.end(); ++elm) {
			string key = elm->first;

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