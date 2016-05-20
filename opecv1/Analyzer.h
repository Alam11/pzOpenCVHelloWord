#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "SignumComparatorStrategy.h"
#include "CompareWithCuttingStrategy.h"
#include <array>

using namespace cv;
using namespace std;

class Analyzer {
private:
	std::vector<cv::Mat> data;
public: 
	std::vector<int> chooseCandidates(std::vector<long> framesDifference);
	std::vector<long> Analyzer::generateDifferenceVector(std::vector<cv::Mat> frames);
	void setData(std::vector<cv::Mat> data);
	ModelForIdealCycles createModelForIdealCycles();
	vector<array<long, 2>> createIdealCycle(ModelForIdealCycles model);
	//int computeFitness(int beg, int end);
	
};


vector<int> findCycles(vector<int> candidates, vector<Mat> frames);
