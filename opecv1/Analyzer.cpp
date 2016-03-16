#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "Analyzer.h"

using namespace cv;
using namespace std;



int distanceBetweenPoints(Vec3b a, Vec3b b) {
	return abs(a[0] - b[0]) + abs(a[1] - b[1]) + abs(a[2] - b[2]);
}

vector<int> computeBlocks(vector<Vec3b> data) {
	vector<int> res;
	res.push_back(0);
	for (int i = 1; i < data.size(); i++) {
		if (distanceBetweenPoints(data[i], data[i - 1]) > 40) {
			res.push_back(i);
		}
	}
	return res;
}

void Analyzer::chooseCandidate(int& beg, int& end, double actFitness) {
	if (end == data.size()) {
		beg++; 
		end = beg; 
	}
	else {
		end++; 
	}

}

Analyzer::Analyzer(vector<cv::Vec3b> res)
{
	data = res; 
}

int Analyzer::computeFitness(int beg, int end) {
	int res = 0; 
	int range = end - beg; 
	for (int i = end + 1; i < data.size(); i++ ) {
		res += distanceBetweenPoints(data[i], data[i%range + beg]); 
	}
	for (int i = beg - 1; i < 0; i--) {
		res += distanceBetweenPoints(data[i], data[end - (end-i)%range]);
	}
	return res; 
}

void Analyzer::analyze(){
	vector<int> blocks = computeBlocks(data);
	double fitnessRatio = 0;
	int actFitnessRatio = 0; 
	int bestBeg, bestEnd = 0; 
	int beg, end = 0;
	while (end != data.size()) {
		chooseCandidate(beg, end, fitnessRatio);
		actFitnessRatio = computeFitness(beg, end); 
		if (fitnessRatio < actFitnessRatio) {
			fitnessRatio = actFitnessRatio; 
			bestBeg = beg; 
			bestEnd = end;
			cout << fitnessRatio; 
		}
	}
	cout << "Best fitness is " << fitnessRatio << endl; 
	cout << "begining at" << beg << "ending at" << end << endl; 
}