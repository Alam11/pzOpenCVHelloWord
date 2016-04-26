#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "FramesUtils.h"

/*
	plik w którym s¹ funkcje dza³aj¹ce na ramkach uniwersalne dla ka¿dej strategii porównania 
*/
using namespace cv;
using namespace std;

const int EI = 3830422;
const int ET = 10;
const int E_MAX_CYCLE_LENGTH = 150;

int getEI() {
	return EI; 
}

int distanceBetweenPoints(Vec3b a, Vec3b b) {
	// funkcja wyznaczaj¹ca odleg³oœæ. w przypadku zmiany danych 
	// np. na grayscale trzba j¹ nadpisaæ
	return abs(a[0] - b[0]) + abs(a[1] - b[1]) + abs(a[2] - b[2]);
}


long distanceBetweenFrames(Mat f1, Mat f2) {
	// jak wy¿ej tylko dla ramek. ramki musz¹ mieæ ten sam rozmiar 
	long sum = 0;
	for (int i = 0; i < f1.rows; i++) {
		for (int j = 0; j < f1.cols; j++) {
			sum += distanceBetweenPoints(f2.at<Vec3b>(i, j), f1.at<Vec3b>(i, j));
		}
	}
	return sum;
}

bool comparePeriods(int beg1, int end1, int beg2, int end2, vector<Mat> frames) {
	// funkcja która porónuje czy klatki w filmie pokrywaj¹ siê 
	// przyjmuje indeksy obu cykli i jeœli klatki pokrywaj¹siê w wystarczaj¹ceym stopniu zwraca True
	// a jeœli jest z nimi jakiœ probliem zwraca false. 

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