//------------------------------------------------------------------------------
// main.cpp
// Created by Kunlakan Cherdchusilp
// Edited by Jessica Oriondo
// Created on 11/16/2016
// Last edited 12/6/2016
//------------------------------------------------------------------------------
// This program enable users to draw on a 600 x 600 px canvas and the program
// will be able to detect what was drawn on the canvas. 
// The application starts by telling users what to draw. Then using the mouse,
// as a paint brush. By pressing enter, it will show user the result. 
//
// keyboard events that can be used are:
// esc			quit application
// enter		submit drawing
// backspace	clear canvas
// r			restart application / draw different shape
// h			display hint window(will display what user needs to draw)
//------------------------------------------------------------------------------
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

#include <stdlib.h>
#include <ctime>

#include "DrawingRecognition.h"
#include "TemplateLibrary.h"  

//constants
const int ESC = 27;
const int ENTER = 13;
const int BACKSPACE = 8;
const int R_KEY = 114;
const int H_KEY = 104;
const string canvasName = "Draw window";
const string canvasFileName = "canvas.jpg";
const string hintWindowName = "Hint window";


//variables for GUI
string theShape; //shape that needs to be drawn by user
Mat initImg;

//variables that will be used for mouse callback
bool buttonDown;	//LMB is being pressed
bool started;		//game has started(false if in instruction page)
bool firstClicked;  //detect first click to remove text("draw [shape]") on canvas
bool submitted;		//true if user has pressed enter when done drawing
Point prevPoint;	//keeps track of the mouse position(used for drawing line)

//------------------------- onMouse(Mouse event callback function) --------------------------
// Handles mouse events. Crrently clears canvas on first click and is responsible for
// enabling user to drw on canvas.
//
// Uses a callback function method with standard method signature/parameters based from openCV.
// Parameters: event	openCV's mouse event constant
//			   x/y		x and y coordinates of the mouse event
//			   flags	openCV's mouse event flag constant
//			   imgptr   pointer to the image being worked on
//			   
// Precondition:	- imgptr can't be NULL and must be in MAT format
//					  must use proper openCV call method using setMouse:
//					  setMouseCallback(string windowName, onMouse, MAT &img);
//
// Postcondition:	- Every mouse event will be handled in this function.
//-------------------------------------------------------------------------------------------
static void onMouse(int event, int x, int y, int flags, void* imgptr);


//------------------------- getRandomNumber -------------------------------------
// renturns a random interger from 0 to the set max
//
// Precondition:	- max value is provided.
// Postcondition:	- random int from the given range will be returned.
//------------------------------------------------------------------------------
int getRandomNumber(int max);


//------------------------- drawRandomShapes -------------------------------------
// renturns a random shape available in our template library  and stores it in 
// the variable called theShape.
//
// Precondition:	- DrawingRecognition is properly set up and Template Library is not empty.
// Postcondition:	- A shape in string is returned.
//------------------------------------------------------------------------------
string drawRandomShape();

//---------------------------- areEqual ------------------------------------------
// compares 2 Mat images are equal
//
// precondition: images have the same size.
// postcondition: return true if both images are equal
//--------------------------------------------------------------------------------
bool areEqual(Mat& imgA, Mat& imgB);


//---------------------------------- init -------------------------------------
// Initializes variables that will be used for GUI.
//
// Precondition:	- 
// Postcondition:	- initializes all the data in the application as a new state.
//------------------------------------------------------------------------------
void init();


//--------------------------------- runApp -------------------------------------
// Starts the application. Show appropriate windows and images. Sets up event handling
//	and organizes which code to execute based from the keys pressed by user.
//
// Precondition:	- DrawingRecognition is properly set up and Template Library is not empty.
//					- Environment is initialized;
// Postcondition:	- Application runs properly and user will be able to draw, clear canvas,
//						restart application and be able to get result of their drawing.
//------------------------------------------------------------------------------
void runApp();

//===============================================================================================
//
//										MAIN
//	
//===============================================================================================
int main(int argc, char* argv[]) {
	
	
	init();
	
	runApp();
}

static void onMouse(int event, int x, int y, int flags, void* imgptr) 
{
	if (event == EVENT_LBUTTONDOWN) //left mouse button is clicked
	{
		if (!buttonDown) 
		{
			buttonDown = true;
			//update mouse position
			prevPoint.x = x;
			prevPoint.y = y;

			
		}

		if (started && !firstClicked)
		{
			firstClicked = true;
			//clear canvas using empty image
			Mat & img = *((Mat*)imgptr);
			img = imread(canvasFileName);
			imshow(canvasName, img);
		}

	}
	else if (event == EVENT_LBUTTONUP) //left mouse button is released
	{
		buttonDown = false;
	}


	if (buttonDown && event == EVENT_MOUSEMOVE)  // mouse is moved while clicking down
	{
		Mat & img = *((Mat*)imgptr); // cast, then deref

		//initialize pen property
		Point pt1 = Point(x, y);
		Scalar color = Scalar(0, 0, 0);
		int thickness = 8;
		int lineStyle = 8;
		int shift = 0;


		line(img, prevPoint, pt1, color, thickness, lineStyle, shift); //draw line
		imshow(canvasName, img);	//update canvas
		//waitKey(1);
	}

	if (event == EVENT_MOUSEMOVE) //mouse is moved
	{
		//update mouse position
		prevPoint.x = x;
		prevPoint.y = y;
	}

}

int getRandomNumber(int max)
{
	srand((int)time(0));
	int randomNum = rand() % max;
	return randomNum;
}

string drawRandomShape()
{
	//create dummy object to get available shapes from library
	DrawingRecognition dummyDr = DrawingRecognition(canvasFileName);
	vector<string> availableShapes = dummyDr.getAllShapes();


	int shapeIndex = getRandomNumber((int)availableShapes.size()); //get random integer
	theShape = availableShapes.at(shapeIndex); //map random number to vector of shapes

	return theShape;
}

void init()
{
	started = false;
	buttonDown = false;
	firstClicked = false;
	submitted = false;
	prevPoint = Point(0, 0);
	drawRandomShape(); //get shape to be drawn by user
	initImg = imread(canvasFileName); //get empty canvas
}

void runApp()
{

	
	Mat img = initImg.clone(); 

	//get instruction image
	const string instructionFileName = "instructions.jpeg";
	Mat instructionImg = imread(instructionFileName);

	namedWindow(canvasName); //setup window
	imshow(canvasName, instructionImg); //display instructions



	//====================================================================
	//					KEYBOARD EVENT HANDLING
	//====================================================================
	int key = waitKey(1);
	while (key != ESC) //exit when 'Esc' is pressed
	{

		if (started) //game is ongoing
		{
			setMouseCallback(canvasName, onMouse, &img); // pass ptr to mat here
			imshow(canvasName, img);
		}

		key = waitKey(1);

		if (key == ENTER) //enter key is pressed
		{
			if (submitted)
			{
				drawRandomShape();
				img = initImg.clone();


				//initialize properties of text 
				string toDrawEcho = "Draw a " + theShape + "."; //text to display
				Point textPos = cvPoint(100, 300);
				int textScale = 1;
				Scalar textColor = cvScalar(0, 0, 0);
				int textThickness = 1;

				putText(img, toDrawEcho, textPos, FONT_HERSHEY_COMPLEX, textScale, textColor, textThickness, CV_AA);//draw text

				init();
			}
			else if (started) //game is on going -> show result of drawing
			{
				//initialize text properties
				Point penPos = cvPoint(10, 60);
				Scalar penColor = cvScalar(250, 250, 250);
				int penScale = 1; // negative value to fill in
				int penThickness = 1;

				//initialize rectangle properties
				Point p1 = Point(10, 10);
				Point p2 = Point(590, 70);
				Scalar recColor = cvScalar(0, 0, 0);
				int recThickness = -1; // negative value to fill in
				int recLineType = 8;
				int recShift = 0;
				string out = "";

				if (firstClicked)
				{
					//save final result
					string outputFileName = "output.jpg";
					imwrite(outputFileName, img);


					if (areEqual(img, initImg.clone())) //user hasn't drawn anything
					{
						out = "You haven't drawn anything";
						//print out a warning
						rectangle(img, p1, p2, recColor, recThickness, recLineType, recShift); // draw rectangle
						putText(img, out, penPos, FONT_HERSHEY_COMPLEX, penScale, penColor, penThickness, CV_AA); //drawText
						firstClicked = false;
					}
					else 
					{

						DrawingRecognition dr(outputFileName); //create draw recognition for the final drawing

						string result = dr.findBestMatch(); //get best match

						
						if (result == theShape) //drawing matched the target shape
						{
							out = "Nice " + result + " drawing";

							//initialize text properties
							string toDrawEcho = "Press 'enter' 2x to continue"; //text to display
							Point textPos = cvPoint(50, 590);
							int textScale = 1;
							Scalar textColor = cvScalar(0, 0, 0);
							int textThickness = 1;

							putText(img, toDrawEcho, textPos, FONT_HERSHEY_COMPLEX, textScale, textColor, textThickness, CV_AA);//draw text

							submitted = true;
						}
						else //drawing didn't match
						{
							out = "Sorry, it looks like a potato";
						}


						rectangle(img, p1, p2, recColor, recThickness, recLineType, recShift); // draw rectangle
						putText(img, out, penPos, FONT_HERSHEY_COMPLEX, penScale, penColor, penThickness, CV_AA); //drawText

						
					}
				}

				
			}

			else if (!started) //game just launched/just about to start
			{
				if (!firstClicked) //from instruction page -> tell user what to draw page
				{
					//initialize properties of text 
					string toDrawEcho = "Draw a " + theShape + "."; //text to display
					Point textPos = cvPoint(100,300);
					int textScale = 1;
					Scalar textColor = cvScalar(0, 0, 0);
					int textThickness = 1;

					putText(img, toDrawEcho, textPos, FONT_HERSHEY_COMPLEX, textScale,textColor , textThickness, CV_AA);//draw text
				}

				started = true;
				imshow(canvasName, initImg); //clear canvas
			}

		}

		else if (key == BACKSPACE) // backspace is pressed
		{
			if (started && firstClicked) //game is on going 
			{
				//clear canvas
				img = initImg.clone();
				imshow(canvasName, img);
			}
		}

		else if (key == R_KEY) //'r' is pressed
		{
			destroyWindow(hintWindowName); //destroy hint window
			//clear canvas
			img = initImg.clone();
			imshow(canvasName, img);


			init();		//restart data

			//tell user what to draw
			string toDrawEcho = "Draw a " + theShape + ".";
			putText(img, toDrawEcho, cvPoint(100, 300),
				FONT_HERSHEY_COMPLEX, 1, cvScalar(0, 0, 0), 1, CV_AA);

			started = true;
		}

		else if (key == H_KEY) // 'h' key is pressed
		{
			
			if (started && firstClicked)
			{
				//create new window
				namedWindow(hintWindowName);
				Mat hintImg = initImg.clone();
				

				//tell user what to draw
				string toDrawEcho = "Draw a " + theShape + ".";
				putText(hintImg, toDrawEcho, cvPoint(100, 300),
					FONT_HERSHEY_COMPLEX, 1, cvScalar(0, 0, 0), 1, CV_AA);

				imshow(hintWindowName, hintImg); //display hint
			}
		}

	}//end of while statement
}

bool areEqual(Mat& imgA, Mat& imgB)
{
	Mat temp;
	Mat outA;
	Mat outB;

	//convert images to grayscale
	cvtColor(imgA, outA, CV_BGR2GRAY);
	cvtColor(imgB, outB, CV_BGR2GRAY);
	
	compare(outA, outB, temp, CMP_NE); 
	return (countNonZero(temp) == 0);
}