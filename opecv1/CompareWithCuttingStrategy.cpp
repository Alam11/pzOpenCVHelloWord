#include "stdafx.h"
#include "CompareWithCuttingStrategy.h"
#include "FramesUtils.h"



void CompareWithCuttingStrategy::compare()
{
	// ta impolementacja dodatkowo tnie podany filmik na osobne cykle i zapisuje je w folderze projaktowym 
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

	VideoWriter outputVideo;
	Size frameSize = Size((int)cap.get(CV_CAP_PROP_FRAME_WIDTH), (int)cap.get(CV_CAP_PROP_FRAME_HEIGHT));
	double fourcc = cap.get(CV_CAP_PROP_FOURCC);
	double fps = cap.get(CV_CAP_PROP_FPS);
	int videoCounter = 0;
	outputVideo.open("cycle0.mp4", fourcc, fps, frameSize, true);

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

			if (outputVideo.isOpened()) {
				outputVideo << frame;
			}

			index = (index + 1) % cycleLength;

			if (index == 0) {
				outputVideo.open("cycle" + to_string(++videoCounter) + ".mp4", fourcc, fps, frameSize, true);
			}
		}
		imshow("myvideo", frame);
	}
}

CompareWithCuttingStrategy::CompareWithCuttingStrategy()
{
}

CompareWithCuttingStrategy::CompareWithCuttingStrategy(IdealCycle dataArg)
{
	data = dataArg;
}


CompareWithCuttingStrategy::~CompareWithCuttingStrategy()
{
	//delete data; TODO obgarn¹æ destruktory  
}
