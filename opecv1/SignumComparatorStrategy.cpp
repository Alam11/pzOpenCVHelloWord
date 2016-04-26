#include "stdafx.h"
#include "SignumComparatorStrategy.h"
#include "FramesUtils.h"


void SignumComparatorStrategy::compare()
{
	// ta implementacja por�wnuje nowe klatki przy u�yciu epsilona zdefiniowanego w frames utils
	// je�li klatka jest nie dalej ni� jej odpowiednik w idealnym cyklu to si� nadaje.
	// wad� jest to �e cykle s� ci�g�e a zapisy na naszej kamerze s� dyskretne wi�c ci�ko dobra�
	// odpowiedni� d�ugo�� cyklu w klatkach. wybieraj�c po prostu �redni� ca�kowit� nara�amy si� na 
	// zgubienie dok�adno��i po jakim� czasie. Nale�a�o by rozwa�y� d�ugo�� cyklu w postaci liczby zmiennoprzecinkowej
	// i sprytniejsz� strategi� por�wnywania filmik�w, uwzgl�dniaj�c� ci�g�y czas oraz funkcje wyg�adzaj�ce
	// po przechwyceniu filmu fukncja czeka kilka klatek dla rozruchu,
	// funkcja ma dwa stany - startowy i "operacyjny" w stanie startowym po prostu czeka na wykrycie 
	// pierwszej klatki cyklu je�li obraz od pocz�tku b�dzie zniekszta�cony funkcja nic nie wykryje 
	// w stanie operacyjnym funkcja wypisuje odleg�o�ci kolejnych klatek od wzorcowego cyklu. 
	// docelowo b�dzie zbiera� informacje i wy�lietla� je dopiero gdy cykl si� zako�czy 

	VideoCapture cap("Nagywanie_2016_03_10_13_25_29_948.mp4");
	namedWindow("myvideo", CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"
	bool starting = true; 
	int index = 0; 
	int cycleLength = data.periods[2] - data.periods[1]; // lepsza metoda wliczania dlugosci cyklu w strategy utils
	Mat frame;
	bool bsuccess = cap.read(frame); // read a new frame from video
	bsuccess = cap.read(frame); // read a new frame from video
	bsuccess = cap.read(frame); // read a new frame from video
	bsuccess = cap.read(frame); // read a new frame from video
	bsuccess = cap.read(frame); // read a new frame from video
	bsuccess = cap.read(frame); // read a new frame from video
	bsuccess = cap.read(frame); // read a new frame from video

	while (1)
		{
			bsuccess = cap.read(frame); // read a new frame from video
			if (!bsuccess)
			{
				cout << "cannot read the frame from video file" << endl;
				break;
			}

			
			if (starting) {
				cout << distanceBetweenFrames(frame, data.frames[0]) << " starting" << endl; 
				starting = distanceBetweenFrames(frame, data.frames[0]) > getEI();
			}
			else {
				// zakladamy ze sie idealnie naloza 
				// pewnie po jakims czasie sie rozejda 
				cout << distanceBetweenFrames(frame, data.frames[index]) << endl;
				index = (index + 1) % cycleLength;
			}
			imshow("myvideo", frame); 
		}
}

SignumComparatorStrategy::SignumComparatorStrategy()
{
}

SignumComparatorStrategy::SignumComparatorStrategy(IdealCycle dataArg)
{
	data = dataArg;
}


SignumComparatorStrategy::~SignumComparatorStrategy()
{
	//delete data; TODO obgarn�� destruktory 
}
