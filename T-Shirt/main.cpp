//-----------------------------------------------------------------------------
// main.cpp
// Created by Kunlakan Cherdchusilp
// Created on 11/16/2016
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv; 

int main(int argc, char* argv[]){
	Mat input = imread("square.jpg");

	//double sigmaX = 2.0, sigmaY = 2.0;
	//double threshold1 = 20, threshold2 = 60;

	//flip(input, input, 1);
	//cvtColor(input, input, COLOR_BGR2GRAY);
	//GaussianBlur(input, input, Size(7, 7), sigmaX, sigmaY);
	//Canny(input, input, threshold1, threshold2);
	//imshow("Edge Detected", input);
	//waitKey(0);
}