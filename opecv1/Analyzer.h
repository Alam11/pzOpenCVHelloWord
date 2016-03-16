#include "opencv2/highgui/highgui.hpp"
#include <iostream>

class Analyzer {
private:
	std::vector<cv::Vec3b> data;
public: 
	void chooseCandidate(int & beg, int & end, double actFitness);
	Analyzer(std::vector<cv::Vec3b> data);
	int computeFitness(int beg, int end);
	void analyze(); 
	
};