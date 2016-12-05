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

#include "DrawingRecognition.h"
#include "TemplateLibrary.h"  


bool buttonDown;
Point prevPoint;

static void onMouse(int event, int x, int y, int, void* imgptr) {
	if (event == EVENT_LBUTTONDOWN)
	{
		if (!buttonDown)
		{
			buttonDown = true;
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
		imshow("Display window", img);
		waitKey(1);
	}

	if (event == EVENT_MOUSEMOVE)
	{
		prevPoint.x = x;
		prevPoint.y = y;
	}

}



int main(int argc, char* argv[]) {
	//DrawingRecognition dr("input.jpg");
	//dr.findBestMatch();

	buttonDown = false;
	prevPoint = Point(-1, -1);
	Mat initImg = imread("canvas.jpg");
	Mat img = initImg;

	//createButton("button3", callbackButton, &img);


	namedWindow("Display window");

	while (waitKey(1) != 27) {

		setMouseCallback("Display window", onMouse, &img); // pass ptr to mat here
		imshow("Display window", img);

		if (waitKey(1) == 13)
		{
			imwrite("output.jpg", img);
			DrawingRecognition dr("output.jpg");
			//cout << dr.findBestMatch();

			string out = "that's a " + dr.findBestMatch();

			putText(img, out, cvPoint(30, 30),
				FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200, 200, 250), 1, CV_AA);
			

			
		}
	}

	

	imwrite("output.jpg", img);

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