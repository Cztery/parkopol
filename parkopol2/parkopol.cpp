// parkopol2.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include "park_unit.h"
#include <iostream>
#include "parkopol.h"
//#include <cstring>
//#include <vector>
using namespace std;






int main()
{
    cout << "Hello World!\n";
	park_unit parking_balice;

	cout << endl << sizeof(parking_balice) << endl;
	parking_balice.addChildUnit();
	parking_balice.addChildUnit();
	parking_balice.addChildUnit();

	parking_balice.m_children.back()->addChildUnit();

	parking_balice.removeChildren();


	return 0;
}
