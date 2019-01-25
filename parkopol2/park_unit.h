#include "pch.h"
#ifndef PARK_UNIT_H
#define PARK_UNIT_H
#include "car.h"
using namespace std;

class park_unit
{
private:
	static park_unit* m_root;
	static vector<string> unitNames;
	static vector<unsigned int> unitDefaultAmounts;

	park_unit * m_parent;
	unsigned int m_depthLevel, m_childID, m_freePlacesCounter, totalPlaces;
	bool m_isDisabled, m_isTaken;
	car* m_parkedCar;


public:
	vector <park_unit *> m_children;
	park_unit();
	park_unit(park_unit* parent);
	~park_unit();
	void countFree(int change);
	void countTotal(int change);
	void menu();
	void loadStructure();
	void printID();
	void printLocation();
	park_unit* findFreePlace(size_t iter);
	park_unit* findCarLocation(string plates);
	void declareParkStructure();
	void buildParkStructure();
	void addChildUnit();
	void removeChildren();
	void removeChildUnit();
	void removeChildUnit(unsigned childID);
	void placeTaken(car* newcar);
	void placeFreed(); 
	void getDataFromFiles();
	car* getCar();
	unsigned getChildID();
	bool isTaken();
	park_unit* getChild(int i);
};

#endif