#ifndef IDEAL_CYCLE_H
#define IDEAL_CYCLE_H
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

class ModelForIdealCycles
{
public:       
	vector<Mat> frames;
	vector<long> difference;
	vector<int> periods;
	ModelForIdealCycles(vector<Mat> frames, vector<long> difference, vector<int> periods);
	~ModelForIdealCycles();
	ModelForIdealCycles();
	ModelForIdealCycles(const ModelForIdealCycles &cycle); 
};
#endif