#include "pch.h"
#include "car.h"


car::car()
{
}

car::car(string plates, time_t entry) :m_plateID(plates), m_entryTime(entry)
{
}


car::~car()
{
}

string car::getPlates()
{
	return m_plateID;
}

time_t car::checkParkingDuration()
{
	time_t duration = time(NULL) - m_entryTime;
	
	return duration;
}

void car::printParkingDuration(time_t duration)
{
	if (!duration) duration = checkParkingDuration();
	struct tm timestruct;
	localtime_s(&timestruct, &m_entryTime);
	char durationText[26];
	asctime_s(&durationText[0], 26, &timestruct);
	cout << durationText;
}
