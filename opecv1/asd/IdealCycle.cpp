#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "IdealCycle.h"


using namespace cv;
using namespace std;

IdealCycle::IdealCycle(vector<Mat> frames, vector<long> difference, vector<int> periods)
{
	frames = frames;
	difference = difference;
	periods = periods;
}


IdealCycle::~IdealCycle()
{
}

