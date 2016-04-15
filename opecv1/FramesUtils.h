#ifndef FRAMES_UTILS    // To make sure you don't declare the function more than once by including the header multiple times.
#define FRAMES_UTILS
#include "stdafx.h"

using namespace cv;
using namespace std;

int distanceBetweenPoints(Vec3b a, Vec3b b);
int getEI(); 
long distanceBetweenFrames(Mat f1, Mat f2);
bool comparePeriods(int beg1, int end1, int beg2, int end2, std::vector<cv::Mat> frames);


#endif