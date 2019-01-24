#pragma once
#include "pch.h"
#include "car.h"
#include "park_unit.h"

class RunInstance
{
private:
	park_unit parkingStructureRoot;
	map<string, car> carMap;

public:
	RunInstance();
	~RunInstance();
	car* getTicket();
	void start();
};

