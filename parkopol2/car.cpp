#include "pch.h"
#include "car.h"


car::car()
{
}

car::car(string plates, time_t entry, park_unit * loc) :m_plateID(plates), m_entryTime(entry), m_location(loc)
{
}


car::~car()
{
}
