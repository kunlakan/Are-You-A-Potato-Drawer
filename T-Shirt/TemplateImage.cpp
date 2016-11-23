#include "TemplateImage.h"

//Do the images need to be converted to binary?
TemplateImage::TemplateImage(string filename, int min, int max) {
	this->image = imread(filename);
	setMinStrokes(min);
	setMaxStrokes(max);
}

int TemplateImage::getMaxStrokes() const {
	return this->maxStrokes;
}

void TemplateImage::setMaxStrokes(const int max) {
	if (max < 0) {
		this->maxStrokes = 1;
	}
	else {
		this->maxStrokes = max;
	}
}

int TemplateImage::getMinStrokes() const {
	return this->minStrokes;
}
void TemplateImage::setMinStrokes(const int min) {
	if (min < 0) {
		this->minStrokes = 1;
	}
	else {
		this->minStrokes = min;
	}
}

Mat TemplateImage::getImage() const {
	return this->image;
}
void TemplateImage::setImage(const Mat &newImage) {
	this->image = newImage;
}