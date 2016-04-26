#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "FramesUtils.h"

/*
	plik w kt�rym s� funkcje dza�aj�ce na ramkach uniwersalne dla ka�dej strategii por�wnania 
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
	// funkcja wyznaczaj�ca odleg�o��. w przypadku zmiany danych 
	// np. na grayscale trzba j� nadpisa�
	return abs(a[0] - b[0]) + abs(a[1] - b[1]) + abs(a[2] - b[2]);
}


long distanceBetweenFrames(Mat f1, Mat f2) {
	// jak wy�ej tylko dla ramek. ramki musz� mie� ten sam rozmiar 
	long sum = 0;
	for (int i = 0; i < f1.rows; i++) {
		for (int j = 0; j < f1.cols; j++) {
			sum += distanceBetweenPoints(f2.at<Vec3b>(i, j), f1.at<Vec3b>(i, j));
		}
	}
	return sum;
}

bool comparePeriods(int beg1, int end1, int beg2, int end2, vector<Mat> frames) {
	// funkcja kt�ra por�nuje czy klatki w filmie pokrywaj� si� 
	// przyjmuje indeksy obu cykli i je�li klatki pokrywaj�si� w wystarczaj�ceym stopniu zwraca True
	// a je�li jest z nimi jaki� probliem zwraca false. 

	int timeDistance = abs(end1 - beg1 - (end2 - beg2));
	if (timeDistance > ET) {
		return false;
	}
	int shift = beg2 - beg1;
	int intervalLength = min(end1 - beg1, end2 - beg2);
	for (int i = beg1; i < beg1 + intervalLength; i++) {
		cout << distanceBetweenFrames(frames[i], frames[i + shift]);
	}
	// TODO trzeba zdecydowa� czy robimy sum� sprawdzamy czy jest tak 
	// og�lnie dobrze  czy �redni� i czy tak przez ca�y czas mo�� by� 
	// trzeba zorobi� odcienie szaro�ci bo si� tego nie b�dzie wogle da�o debugowa� 
	return false;

}