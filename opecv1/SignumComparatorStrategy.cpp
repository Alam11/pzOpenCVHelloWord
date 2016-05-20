#include "stdafx.h"
#include "SignumComparatorStrategy.h"
#include "FramesUtils.h"


void SignumComparatorStrategy::compare()
{
	// ta implementacja porównuje nowe klatki przy u¿yciu epsilona zdefiniowanego w frames utils
	// jeœli klatka jest nie dalej ni¿ jej odpowiednik w idealnym cyklu to siê nadaje.
	// wad¹ jest to ¿e cykle s¹ ci¹g³e a zapisy na naszej kamerze s¹ dyskretne wiêc ciê¿ko dobraæ
	// odpowiedni¹ d³ugoœæ cyklu w klatkach. wybieraj¹c po prostu œredni¹ ca³kowit¹ nara¿amy siê na 
	// zgubienie dok³adnoœæi po jakimœ czasie. Nale¿a³o by rozwa¿yæ d³ugoœæ cyklu w postaci liczby zmiennoprzecinkowej
	// i sprytniejsz¹ strategiê porównywania filmików, uwzglêdniaj¹c¹ ci¹g³y czas oraz funkcje wyg³adzaj¹ce
	// po przechwyceniu filmu fukncja czeka kilka klatek dla rozruchu,
	// funkcja ma dwa stany - startowy i "operacyjny" w stanie startowym po prostu czeka na wykrycie 
	// pierwszej klatki cyklu jeœli obraz od pocz¹tku bêdzie zniekszta³cony funkcja nic nie wykryje 
	// w stanie operacyjnym funkcja wypisuje odleg³oœci kolejnych klatek od wzorcowego cyklu. 
	// docelowo bêdzie zbieraæ informacje i wyœlietlaæ je dopiero gdy cykl siê zakoñczy 

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

SignumComparatorStrategy::SignumComparatorStrategy(ModelForIdealCycles dataArg)
{
	data = dataArg;
}


SignumComparatorStrategy::~SignumComparatorStrategy()
{
	//delete data; TODO obgarn¹æ destruktory 
}
