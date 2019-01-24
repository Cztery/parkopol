


#ifndef CAR_H
#define CAR_H
#include "pch.h"
#include "park_unit.h"
using namespace std;

class car
{
private:
	string m_plateID;
	time_t m_entryTime;
	park_unit * m_location;

public:
	car();
	car(string plates, time_t entry, park_unit * loc);
	~car();
};


#endif // !CAR_H


