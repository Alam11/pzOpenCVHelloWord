#include "opencv2/highgui/highgui.hpp"
#include <iostream>


class Analyzer {
private:
	std::vector<cv::Mat> data;
public: 
	std::vector<int> chooseCandidates(std::vector<long> framesDifference);
	std::vector<long> Analyzer::generateDifferenceVector(std::vector<cv::Mat> frames);
	void setData(std::vector<cv::Mat> data);
	int computeFitness(int beg, int end);
	void analyze(); 
	
};

bool comparePeriods(int beg1, int end1, int beg2, int end2, std::vector<cv::Mat> frames);

vector<int> findCycles(vector<int> candidates, vector<Mat> frames);
