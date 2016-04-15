#include "stdafx.h"
#include "SignumComparatorStrategy.h"
#include "FramesUtils.h"


void SignumComparatorStrategy::setRawData(IdealCycle dataArg)
{
	data = dataArg;
}

void SignumComparatorStrategy::compare()
{
	VideoCapture cap("Nagywanie_2016_03_10_13_25_29_948.mp4");
	namedWindow("myvideo", CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"
	bool starting = true; 
	int index = 0; 
	int cycleLength = data.periods[2] - data.periods[1]; // lepsza metoda wliczania dlugosci cyklu w strategy utils
	Mat frame;
	bool bsuccess = cap.read(frame); // read a new frame from video
	bsuccess = cap.read(frame); // read a new frame from video
	bsuccess = cap.read(frame); // read a new frame from video
	bsuccess = cap.read(frame); // read a new frame from video
	bsuccess = cap.read(frame); // read a new frame from video
	bsuccess = cap.read(frame); // read a new frame from video
	bsuccess = cap.read(frame); // read a new frame from video

	while (1)
		{
			bsuccess = cap.read(frame); // read a new frame from video
			if (!bsuccess)
			{
				cout << "cannot read the frame from video file" << endl;
				break;
			}

			
			if (starting) {
				cout << distanceBetweenFrames(frame, data.frames[0]) << " starting" << endl; 
				starting = distanceBetweenFrames(frame, data.frames[0]) > getEI();
			}
			else {
				// zakladamy ze sie idealnie naloza 
				// pewnie po jakims czasie sie rozejda 
				cout << distanceBetweenFrames(frame, data.frames[index]) << endl;
				index = (index + 1) % cycleLength;
			}
			imshow("myvideo", frame); 
		}
}

SignumComparatorStrategy::SignumComparatorStrategy()
{
}

SignumComparatorStrategy::SignumComparatorStrategy(IdealCycle dataArg)
{
	data = dataArg;
}


SignumComparatorStrategy::~SignumComparatorStrategy()
{
	//delete data; TODO obgarn¹æ destruktory  
}
