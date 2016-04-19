#ifndef IDEAL_CYCLE_H
#define IDEAL_CYCLE_H
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

class IdealCycle
{
public:       
	vector<Mat> frames;
	vector<long> difference;
	vector<int> periods;
	IdealCycle(vector<Mat> frames, vector<long> difference, vector<int> periods);
	~IdealCycle();
	IdealCycle();
	IdealCycle(const IdealCycle &cycle); 
};
#endif