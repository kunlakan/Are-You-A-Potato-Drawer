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

int main(int argc, char* argv[]) {
	Mat input = imread("template_images/square.jpg");

	imshow("D", input);
	waitKey();
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