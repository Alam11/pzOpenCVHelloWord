#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "ModelForIdealCycles.h"

using namespace cv;
using namespace std;


ModelForIdealCycles::ModelForIdealCycles(vector<Mat> framesArg, vector<long> differenceArg, vector<int> periodsArg)
{
	// klasa odpowiedzialna za wzorcowy cykl 
	// tutaj trzymamy wszystkie dane ktre siê przydaj¹ 
	// przy porównywaniu cykli
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