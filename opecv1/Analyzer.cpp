#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "Analyzer.h"
#include <fstream>

using namespace cv;
using namespace std;

const int EI = 3230422;
const int ET = 10; 
const int E_MAX_CYCLE_LENGTH = 150; 


int distanceBetweenPoints(Vec3b a, Vec3b b) {
	return abs(a[0] - b[0]) + abs(a[1] - b[1]) + abs(a[2] - b[2]);
}

long distanceBetweenFrames(Mat f1, Mat f2) {
	long sum = 0;
	for (int i = 0; i < f1.rows; i++) {
		for (int j = 0; j < f1.cols; j++) {
			sum += distanceBetweenPoints(f2.at<Vec3b>(i, j), f1.at<Vec3b>(i, j));
		}
	}
	return sum; 
}

vector<long> Analyzer::generateDifferenceVector(vector<Mat> frames) {
	vector<long> res;
	//Mat firstFrame = frames[0];
	//for (auto & frame : frames) {
	//	res.push_back(distanceBetweenFrames(frame, firstFrame));
	//}

	string line;
	ifstream myfile("mydata.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			res.push_back(stol(line)); 
		}
		myfile.close();
	}

	else cout << "Unable to open file";
	return res;
}

int findMinimumInInterval(int beg, int end, std::vector<long> data) {
	int minIndex = beg; 
	for (int i = beg; i < end; i++) {
		if (data[i] < data[minIndex]) {
			minIndex = i; 
		}
	}
	return minIndex; 
}

vector<int> Analyzer::chooseCandidates(vector<long> framesDifference){
	bool isAbove = false; 
	int end = 0;
	int beg = 0; 
	vector<int> res;
	for (int i = 1; i < framesDifference.size(); i++) {
		if (isAbove) {
			if (framesDifference[i] > EI) {
				//pass
			}
			else {
				isAbove = false; 
				beg = i; 
			}
		}
		else {
			if (framesDifference[i] > EI) {
				isAbove = true; 
				end = i; 
				res.push_back(findMinimumInInterval(beg, end, framesDifference)); 
			}
			else {
				// pass
			}
		}
	}
	return res; 
}

void Analyzer::setData(vector<Mat> frames)
{
	data = frames;
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

bool comparePeriods(int beg1, int end1, int beg2, int end2, vector<Mat> frames) {
	int timeDistance = abs(end1 - beg1 - (end2 - beg2));
	if (timeDistance > ET) {
		return false; 
	}
	int shift = beg2 - beg1; 
	int intervalLength = min(end1 - beg1, end2 - beg2); 
	for (int i = beg1; i < beg1 + intervalLength; i++) {
		cout << distanceBetweenFrames(frames[i], frames[i + shift]); 
	}
	// TODO trzeba zdecydowaæ czy robimy sumê sprawdzamy czy jest tak 
	// ogólnie dobrze  czy œredni¹ i czy tak przez ca³y czas mo¿ê byæ 
	// trzeba zorobiæ odcienie szaroœci bo siê tego nie bêdzie wogle da³o debugowaæ 
	return false; 
}

vector<int> findCycles(vector<int> candidates, vector<Mat> frames) {
	int candidateEndIndex = 1; 
	int referencedPeriodStartIndex = 1;
	int referencedPeriodEndIndex = 2;
	int numberOfPeriodsConsidered = 1; 
	while ((candidates[candidateEndIndex] < E_MAX_CYCLE_LENGTH ) || (referencedPeriodEndIndex < candidates.size())){
		if (comparePeriods(0, candidates[candidateEndIndex], candidates[referencedPeriodStartIndex],
			candidates[referencedPeriodEndIndex], frames)) {
			referencedPeriodStartIndex += numberOfPeriodsConsidered;
			referencedPeriodEndIndex += numberOfPeriodsConsidered; 
		} {
			candidateEndIndex = referencedPeriodEndIndex; 
			referencedPeriodStartIndex = referencedPeriodEndIndex; // +1 ? zalezy jak chcemy sprawdzac periody 
			numberOfPeriodsConsidered = referencedPeriodEndIndex; 
			referencedPeriodEndIndex += referencedPeriodEndIndex; 
		}
	}
	return groupIndexes(candidates, numberOfPeriodsConsidered);
}

vector<int> groupIndexes(vector<int> indexes, int groupSize) {
	vector<int> res; 
	for (int i = 0; i < indexes.size(); i += groupSize) {
		res.push_back(indexes[i]); 
	}
	return res; 
}

void Analyzer::analyze(){
	vector<long> diff = generateDifferenceVector(data);
	vector<int> candidates = chooseCandidates(diff); 
}