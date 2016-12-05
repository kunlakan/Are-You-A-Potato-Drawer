//------------------------------------------------------------------------------
// main.cpp
// Created by Kunlakan Cherdchusilp
// Created on 11/16/2016
//------------------------------------------------------------------------------
// ASSUMPTION:
//		- Input image must be drawn with a black ink on a white background only.
//
// NOTE:
//		- Considering using Decision Tree when determining image.
//------------------------------------------------------------------------------
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

#include <stdlib.h>
#include <ctime>

#include "DrawingRecognition.h"
#include "TemplateLibrary.h"  

const int ESC = 27;
const int ENTER = 13;
const int BACKSPACE = 8;
const int R_KEY = 114;
const string canvasName = "Draw window";

string matchedShape;
string theShape;
bool buttonDown, started, firstClicked;
Point prevPoint;

static void onMouse(int event, int x, int y, int, void* imgptr) {
	if (event == EVENT_LBUTTONDOWN)
	{
		if (!buttonDown)
		{
			buttonDown = true;
		}

		if (started && !firstClicked)
		{
			//clear canvas using empty image
			firstClicked = true;
			Mat & img = *((Mat*)imgptr);
			img = imread("canvas.jpg");
			imshow(canvasName, img);
		}

	}
	else if (event == EVENT_LBUTTONUP)
	{
		buttonDown = false;
	}


	if (buttonDown && event == EVENT_MOUSEMOVE) {
		Mat & img = *((Mat*)imgptr); // first cast, then deref
		Point pt1 = Point(x, y);

		//circle(img, pt1, 1, Scalar(0, 0, 0), 100, 8, 0);
		line(img, prevPoint, Point(x, y), Scalar(0, 0, 0), 5, 8, 0);
		imshow(canvasName, img);
		waitKey(1);
	}

	if (event == EVENT_MOUSEMOVE)
	{
		prevPoint.x = x;
		prevPoint.y = y;
	}

}

int getRandomNumber(int max)
{
	srand(time(0));
	int randomNum = rand() % max;
	return randomNum;
}

string drawRandomShape()
{
	DrawingRecognition dummyDr = DrawingRecognition("canvas.jpg");
	vector<string> availableShapes = dummyDr.getAllShapes();

	int shapeIndex = getRandomNumber(availableShapes.size() - 1);
	theShape = availableShapes.at(shapeIndex);

	return theShape;
}

void init()
{
	matchedShape = "potato";
	started = false;
	buttonDown = false;
	firstClicked = false;
	prevPoint = Point(0, 0);
	drawRandomShape();
}

void runApp()
{
	
	Mat initImg = imread("canvas.jpg");
	Mat img = initImg.clone();
	Mat instructionImg = imread("instructions.jpeg");

	namedWindow(canvasName);
	imshow(canvasName, instructionImg);



	//************************** EVENT HANDLING *********************************************
	int key = waitKey(1);
	while (key != ESC) {

		if (started)
		{
			setMouseCallback(canvasName, onMouse, &img); // pass ptr to mat here
			imshow(canvasName, img);
		}

		key = waitKey(1);

		if (key == ENTER)
		{
			if (started)
			{
				imwrite("output.jpg", img);
				DrawingRecognition dr("output.jpg");

				string result = dr.findBestMatch();
				string out = "";
				if (result == theShape)
				{
					matchedShape = result;
					out = "Nice " + matchedShape + " drawing";
				}
				else
				{
					out = "Sorry, it looks like a potato";
				}

				rectangle(img, Point(10, 10), Point(590, 70), cvScalar(0, 0, 0), -1, 8, 0);
				putText(img, out, cvPoint(10, 60),
					FONT_HERSHEY_COMPLEX, 1, cvScalar(250, 250, 250), 1, CV_AA);
			}
			else
			{
				if (!firstClicked) {
					string toDrawEcho = "Draw a " + theShape + ".";
					putText(img, toDrawEcho, cvPoint(100, 300),
						FONT_HERSHEY_COMPLEX, 1, cvScalar(0, 0, 0), 1, CV_AA);
				}

				started = true;
				imshow(canvasName, initImg);
			}

		}

		else if (key == BACKSPACE)
		{
			if (started && firstClicked)
			{
				img = initImg.clone();
				imshow(canvasName, img);
			}
		}

		else if (key == R_KEY)
		{
			img = initImg.clone();
			imshow(canvasName, img);
			init();

			string toDrawEcho = "Draw a " + theShape + ".";
			putText(img, toDrawEcho, cvPoint(100, 300),
				FONT_HERSHEY_COMPLEX, 1, cvScalar(0, 0, 0), 1, CV_AA);

			started = true;
		}
	}
}


int main(int argc, char* argv[]) {
	
	
	init();
	
	runApp();
	

	

	//imwrite("output.jpg", img);

	//DrawingRecognition dr(input);
	
	/*
	TemplateLibrary library;
	library.createLibrary();
	vector<string> shapes = library.getAllShapes();
	
	
	TemplateImage get = library.getTemplateImage(6, "template_images/hexagon_6.jpg");
	
	vector<TemplateImage> getList = library.getTemplateImageList(4);

	vector<int> allKeys = library.getAllKeys();

	vector<TemplateImage> allImages = library.getAllTemplateImages();

	int key = library.getContoursKey("template_images/triangle_3.jpg");

	//std::cout << "Before" << endl;
	//library.printLibrary();
	//std::cout << "" << endl;
	//std::cout << "After" << endl;

	//bool del = library.removeTemplateImage(5, "template_images/rectangle_4.jpg");
	//if (del) {
	//	cout << "deleted" << endl;
	//}
	//else {
	//	cout << "NOT deleted" << endl;
	//}
	
	//bool delList = library.removeTemplateImageList(6);

	//library.emptyLibrary();
	//shapes = library.getAllShapes();
	
	for (int i = 0; i < 500; i++) {

		//std::cout << key << endl;
		
		//for (int j = 0; j < allKeys.size(); j++) {
			//std::cout << allKeys[j] << endl;
		//}
		//std::cout << "" << endl;
		
		//for (int j = 0; j < allImages.size(); j++) {
			//std::cout << allImages[j].getImageName() << endl;
		//}
		//std::cout << "" << endl;
		
		//if (library.isEmpty()) {
			//std::cout << "empty" << endl;
		//}
		//else {
			//std::cout << "not empty" << endl;
		//}

		//std::cout << get.getImageName() << endl;

		
		//for (int j = 0; j < getList.size(); j++) {
			//std::cout << getList[j].getImageName() << endl;
		//}
		//std::cout << "" << endl; 

		//for (int j = 0; j < shapes.size(); j++) {
			//std::cout << shapes[j] << endl;
		//}
		//std::cout << "" << endl;

		library.printLibrary();
		std::cout << "" << endl; 
	} */
}