#pragma once

#ifndef __TemplateImage__
#define __TemplateImage__

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
using namespace cv;
using namespace std;

class TemplateImage {

public:

	TemplateImage(string, int, int);

	int getMaxStrokes() const;
	void setMaxStrokes(const int);

	int getMinStrokes() const;
	void setMinStrokes(const int);

	Mat getImage() const;
	void setImage(const Mat &newImage);

	string getImageName() const;
	void setImageName(const string newName);
	void setImageAndImageName(const Mat &newImage, const string newName);

private:
	int minStrokes = 1;
	int maxStrokes = 1;
	Mat image;
	string imageName;
};

#endif /* defined(__TemplateImage__) */