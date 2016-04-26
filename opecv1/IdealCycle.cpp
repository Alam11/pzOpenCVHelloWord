#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "IdealCycle.h"

using namespace cv;
using namespace std;


IdealCycle::IdealCycle(vector<Mat> framesArg, vector<long> differenceArg, vector<int> periodsArg)
{
	// klasa odpowiedzialna za wzorcowy cykl 
	// tutaj trzymamy wszystkie dane ktre siê przydaj¹ 
	// przy porównywaniu cykli
	frames = framesArg;
	difference = differenceArg;
	periods = periodsArg;
}


IdealCycle::~IdealCycle()
{
}

IdealCycle::IdealCycle()
{
}


IdealCycle::IdealCycle(const IdealCycle & cycle)
{
	difference = cycle.difference;
	frames = cycle.frames;
	periods = cycle.periods;
}