#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "Analyzer.h"
#include "FramesUtils.h"
#include <fstream>

using namespace cv;
using namespace std;

// w tym pliku znajduj¹ siê funkcje które wstêpnie analizuj¹ wzorcowy filmik oraz 
// tworz¹ idealny cykl klasa analyzer odpowiada uczeniu siê danego wzorca. 

const int EI = 3830422; 
// maksymalna odleg³oœæ do której uznajemy ¿e klatki z¹ równe, dla filmów kolorowych wiêcej 
// a dla szarych trochê mniej 
const int ET = 10;
const int E_MAX_CYCLE_LENGTH = 150;
// zale¿y od rodzaju cykli z którymi mamy oczynienia najlepiej przekazywana jako parametr z listy komend 

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
	// metoda wybiera kandydatów na cykle.
	// metoda ma dwa stany w stanie "powy¿ej" ró¿nica miêdzy pierwsz¹ klatk¹ i obecn¹ 
	// jest wiêksza ni¿ epsilon a poni¿ej - mniejsza. funjcja wyszukuje indeksy
	// w któreych stan siê zmienia nastêpnie wybierany jest punkt najmniej odleg³y od 
	// klatki pocz¹tkowej i to on jest wyierany jako pocz¹tek nowego kandydata. 
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
	// funkcja przyjmuje kandydatów tzn, miejsca w których ffunkcja ró¿nic odi¹ga lokalne minima
	// nastêpnnie  sprawdza ilu kandydatów trzba wzi¹œæ aby otrzymaæ c¹³y filmik 
	// porównuje to przez funkcjê comparePeriods jeœli trzeba wzi¹œæ wiêcej ni¿ jednego kandydatea np.
	// w przypadku wachade³ka funkcja group indexes robi co trzba 
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



IdealCycle Analyzer::createIdealCycle(){
	// to glówna metoda tej klasy, która wywo³uje pozosta³e metody
	// generuje wykres ró¿nic i szuka kandydatów. nastêpnie sprawdza jaki wzór tworz¹ 
	// kandydaci i potencjalnie ich grupuje i tworzy  nich idealny cykl. jeœli jakaœ strategia bêdzie potrzbowa³a 
	// wiêcej danych o wzorcowym cyklu tutaj w³aœnie trzebs go nadpisaæ. 
	vector<long> diff = generateDifferenceVector(data);
	vector<int> candidates = chooseCandidates(diff);
	// tutaj powinna byæ wywo³ana metoda find cycles 
	IdealCycle model = IdealCycle(data, diff, candidates); 
	return model;
}