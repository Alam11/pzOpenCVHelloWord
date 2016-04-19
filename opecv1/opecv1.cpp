#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "opecv1.h"
#include "Analyzer.h"

using namespace cv;
using namespace std;

int ox = 305; 
int oy = 248; 
 

//void CallBackFunc(int event, int x, int y, int flags, void* userdata)
//{
//	if (flags == (EVENT_FLAG_CTRLKEY + EVENT_FLAG_LBUTTON))
//	{
//		cout << "Left mouse button is clicked while pressing CTRL key - position (" << x << ", " << y << ")" << endl;
//		ox = x; 
//		oy = y; 
//	}
//}


int main(int argc, char* argv[])
{
	VideoCapture cap("Nagywanie_2016_03_10_13_23_47_243.mp4"); // open the video file for reading

	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the video file" << endl;
		return -1;
	}


	double fps = cap.get(CV_CAP_PROP_FPS); //get the frames per seconds of the video

	namedWindow("MyVideo", CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

	//setMouseCallback("MyVideo", CallBackFunc, NULL);

	vector<Mat> frames;

	while (1)
	{
		Mat frame;
		bool bSuccess = cap.read(frame); // read a new frame from video
		if (!bSuccess) //if not success, break loop
		{
			cout << "Cannot read the frame from video file" << endl;
			break;
		}

		//Vec3b color = frame.at<Vec3b>(ox, oy);
		frames.push_back(frame); 

		imshow("MyVideo", frame); //show the frame in "MyVideo" window

		if (waitKey(30) == 27) //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	//	// klatki to frames
	//	// max_t - d³ugoœæ cyklu to ok 3500 ms  czyli ok 105 klatek
	//	// Ei - empirycznie ale jak dla mnie trzeba daæ co najmniej 3033493, jeszcze zale¿y czy bêdziemy to 
	//	// rzucaæ do szaroœci i wycinaæ pod³ogê czy nie .  teraz dalem 36 .. ale docelowo powinno byc mniej 
	//	// 

	}
	Analyzer analyzer;
	analyzer.setData(frames);
	IdealCycle model = analyzer.createIdealCycle(); 
	//SignumComparatorStrategy strategy = SignumComparatorStrategy(model);
	CompareWithCuttingStrategy strategy = CompareWithCuttingStrategy(model);
	strategy.compare(); 
	return 0;
}

