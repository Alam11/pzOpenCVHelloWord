#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "ModelForIdealCycles.h"

using namespace cv;
using namespace std;


ModelForIdealCycles::ModelForIdealCycles(vector<Mat> framesArg, vector<long> differenceArg, vector<int> periodsArg)
{
	// klasa odpowiedzialna za wzorcowy cykl 
	// tutaj trzymamy wszystkie dane ktre si� przydaj� 
	// przy por�wnywaniu cykli
	frames = framesArg;
	difference = differenceArg;
	periods = periodsArg;
}


ModelForIdealCycles::~ModelForIdealCycles()
{
}

ModelForIdealCycles::ModelForIdealCycles()
{
}


ModelForIdealCycles::ModelForIdealCycles(const ModelForIdealCycles & cycle)
{
	difference = cycle.difference;
	frames = cycle.frames;
	periods = cycle.periods;
}