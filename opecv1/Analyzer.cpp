#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "Analyzer.h"
#include "FramesUtils.h"
#include <fstream>

using namespace cv;
using namespace std;

// w tym pliku znajduj� si� funkcje kt�re wst�pnie analizuj� wzorcowy filmik oraz 
// tworz� idealny cykl klasa analyzer odpowiada uczeniu si� danego wzorca. 

const int EI = 3830422; 
// maksymalna odleg�o�� do kt�rej uznajemy �e klatki z� r�wne, dla film�w kolorowych wi�cej 
// a dla szarych troch� mniej 
const int ET = 10;
const int E_MAX_CYCLE_LENGTH = 150;
// zale�y od rodzaju cykli z kt�rymi mamy oczynienia najlepiej przekazywana jako parametr z listy komend 

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
	// metoda wybiera kandydat�w na cykle.
	// metoda ma dwa stany w stanie "powy�ej" r�nica mi�dzy pierwsz� klatk� i obecn� 
	// jest wi�ksza ni� epsilon a poni�ej - mniejsza. funjcja wyszukuje indeksy
	// w kt�reych stan si� zmienia nast�pnie wybierany jest punkt najmniej odleg�y od 
	// klatki pocz�tkowej i to on jest wyierany jako pocz�tek nowego kandydata. 
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


vector<int> groupIndexes(vector<int> indexes, int groupSize) {
	vector<int> res;
	for (int i = 0; i < indexes.size(); i += groupSize) {
		res.push_back(indexes[i]);
	}
	return res;
}

vector<int> findCycles(vector<int> candidates, vector<Mat> frames) {
	// funkcja przyjmuje kandydat�w tzn, miejsca w kt�rych ffunkcja r�nic odi�ga lokalne minima
	// nast�pnnie  sprawdza ilu kandydat�w trzba wzi��� aby otrzyma� c��y filmik 
	// por�wnuje to przez funkcj� comparePeriods je�li trzeba wzi��� wi�cej ni� jednego kandydatea np.
	// w przypadku wachade�ka funkcja group indexes robi co trzba 
	int candidateEndIndex = 1; 
	int referencedPeriodStartIndex = 1;
	int referencedPeriodEndIndex = 2;
	int numberOfPeriodsConsidered = 1; 
	while ((candidates[candidateEndIndex] < E_MAX_CYCLE_LENGTH ) && (referencedPeriodEndIndex < candidates.size())){
		if (comparePeriods(0, candidates[candidateEndIndex], candidates[referencedPeriodStartIndex],
			candidates[referencedPeriodEndIndex], frames)) {
			referencedPeriodStartIndex += numberOfPeriodsConsidered;
			referencedPeriodEndIndex += numberOfPeriodsConsidered; 
		} 
		else {
			candidateEndIndex = referencedPeriodEndIndex; 
			referencedPeriodStartIndex = referencedPeriodEndIndex; // +1 ? zalezy jak chcemy sprawdzac periody 
			numberOfPeriodsConsidered = referencedPeriodEndIndex; 
			referencedPeriodEndIndex += referencedPeriodEndIndex; 
		}
	}
	return groupIndexes(candidates, numberOfPeriodsConsidered);
}

void getMaxMat(Mat &mat1, Mat &mat2) {

}

void getMinMat(Mat &mat1, Mat &mat2) {

}


ModelForIdealCycles Analyzer::createModelForIdealCycles() {
	// to gl�wna metoda tej klasy, kt�ra wywo�uje pozosta�e metody
	// generuje wykres r�nic i szuka kandydat�w. nast�pnie sprawdza jaki wz�r tworz� 
	// kandydaci i potencjalnie ich grupuje i tworzy  nich idealny cykl. je�li jaka� strategia b�dzie potrzbowa�a 
	// wi�cej danych o wzorcowym cyklu tutaj w�a�nie trzebs go nadpisa�.
	vector<long> diff = generateDifferenceVector(data);
	vector<int> candidates = chooseCandidates(diff);
	vector<int> cycles = findCycles(candidates, data);
	return ModelForIdealCycles(data, diff, cycles); 
}


vector<array<long, 2>> Analyzer::createIdealCycle(ModelForIdealCycles model) {
	// tworzenie idealnego cyklu polega na znalezieniu najd�u�szego, utworzenia wst�pnego vectora,
	// kt�ry zawiera wst�pne dozwolone warto�ci min/max, dzi�ki kt�rym mo�na uzna�, czy cykl pasuje do idealnego,
	// p�niej przechodz�c przez wszystkie cykle wybieramy dla ka�dej klatki minimaln� i maksymaln� warto��,
	// uzupe�niaj�c kr�tsze cykle z lewej i z prawej strony warto�ciami odpowiednio z pocz�tku i ko�ca cyklu.
	vector<long> diff = model.difference; 
	vector<int> cycles = model.periods; 

	int maxLength = 0;
	int maxLengthCycleStart = 0;
	for (int i = 0; i < cycles.size() - 1; i++) {
		int length = cycles[i + 1] - cycles[i];
		if (maxLength < length) {
			maxLength = length;
			maxLengthCycleStart = cycles[i];
		}
	}

	vector<array<long, 2>> idealCycle;
	for (int i = cycles[maxLengthCycleStart]; i < maxLength; i++) {
		array<long, 2> aux = {diff[i], diff[i]};
		idealCycle.push_back(aux);
	}

	for (int i = 0; i < cycles.size() - 1; i++) {

		if (i != maxLengthCycleStart) {

			int shift = (maxLength - (cycles[i + 1] - cycles[i])) / 2;
			for (int j = 0; j < maxLength; j++) {

				long currentDiff;
				if (j < shift) {
					currentDiff = diff[cycles[i]];
				}
				else if (j >(cycles[i + 1] - cycles[i] + shift)) {
					currentDiff = diff[cycles[i + 1]];
				}
				else {
					currentDiff = diff[cycles[i] + j - shift];
				}

				if (currentDiff < idealCycle[j][0]) {
					idealCycle[j][0] = currentDiff;
				}
				if (currentDiff > idealCycle[j][1]) {
					idealCycle[j][1] = currentDiff;
				}
			}
		}
	}

	/*ofstream minFile;
	ofstream maxFile;
	minFile.open("min.txt");
	maxFile.open("max.txt");
	for (int i = 0; i < idealCycle.size(); i++) {
		minFile << idealCycle[i][0] << endl;
		maxFile << idealCycle[i][1] << endl;
	}
	minFile.close();
	maxFile.close();*/

	//IdealCycle model = IdealCycle(data, diff, candidates); 
	//return model;
	return idealCycle;
}