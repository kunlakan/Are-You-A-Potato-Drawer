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

#include "TemplateLibrary.h" 

int main(int argc, char* argv[]){
	Mat input = imread("template_images/square.jpg");

	/*
	TemplateImage square("template_images/square.jpg", 1, 4);
	TemplateImage rect("template_images/rectangle.jpg", 1, 4);
	TemplateImage triangle("template_images/triangle.jpg", 1, 3);
	TemplateImage hexagon("template_images/hexagon.jpg", 1, 6);
	TemplateImage hexagon2("template_images/hexagon_2.jpg", 1, 6);

	TemplateLibrary library;
	library.addTemplateImage(square);
	library.addTemplateImage(rect);
	library.addTemplateImage(triangle);
	library.addTemplateImage(hexagon);
	library.addTemplateImage(hexagon2);

	
	TemplateImage get = library.getTemplateImage(1, 6, "template_images/hexagon.jpg");
	
	vector<TemplateImage> getList = library.getTemplateImageList(1, 6);

	vector<string> allKeys = library.getAllKeys();

	vector<TemplateImage> allImages = library.getAllTemplateImages();

	string key = library.getMinMaxKey("template_images/triangle.jpg");

	
	//std::cout << "Before" << endl;
	//library.printLibrary();
	//std::cout << "" << endl;
	//std::cout << "After" << endl;

	//TemplateImage del = library.removeTemplateImage(1, 4, "template_images/rectangle.jpg");

	
	//std::cout << "Before" << endl;
	//library.printLibrary();
	//std::cout << "" << endl;
	//std::cout << "After" << endl;

	
	//vector<TemplateImage> delList = library.removeTemplateImageList(1, 6);

	//std::cout << "Before" << endl;
	//library.printLibrary();
	//std::cout << "" << endl;
	//std::cout << "After" << endl;

	//library.emptyLibrary();

	for (int i = 0; i < 500; i++) {

		//std::cout << key << endl;
		
		//for (int j = 0; j < allKeys.size(); j++) {
			//std::cout << allKeys[j] << endl;
		//}

		
		//for (int j = 0; j < allImages.size(); j++) {
			//std::cout << allImages[j].getImageName() << endl;
		//}

		
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

		//library.printLibrary();
		//std::cout << "" << endl; 
	} */
}