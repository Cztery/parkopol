// parkopol2.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include "park_unit.h"
#include "parkopol.h"
#include "RunInstance.h"
using namespace std;


int main()
{

	//park_unit parking_balice;
	RunInstance parking_balice;
	parking_balice.start();
	// RunInstance
	time_t tajm = time(NULL);
	struct tm timestruct;
	localtime_s(&timestruct, &tajm);
	char timetext[26];
	asctime_s(&timetext[0], 26, &timestruct);
	cout << timetext;
	//parking_balice.getDataFromFiles();
	
	//cout << endl << sizeof(parking_balice) << endl;
	//parking_balice.addChildUnit();
	//parking_balice.addChildUnit();
	//parking_balice.m_children[0]->addChildUnit();
	//parking_balice.m_children[0]->m_children[0]->addChildUnit();


	//cout << endl << sizeof(parking_balice) << endl;
	//parking_balice.removeChildren(); 

	//cout << endl << sizeof(parking_balice) << endl;
	int x;
	cin >> x;
	return 0; 
}

