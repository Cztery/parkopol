#include "pch.h"
#ifndef PARK_UNIT_H
#define PARK_UNIT_H

using namespace std;

class park_unit
{
private:
	static park_unit* m_root;
	static vector<string> unitNames;
	static vector<unsigned int> unitDefaultAmounts;

	park_unit * m_parent;
	unsigned int m_depthLevel, m_childID, takenPlacesCounter, totalPlaces;
	bool isDisabled, isTaken;


public:
	vector <park_unit *> m_children;
	park_unit();
	park_unit(park_unit* parent);
	park_unit(park_unit* parent, vector<tuple<unsigned int, string>> nameAndAmount);
	~park_unit();
	void menu();
	void loadStructure();
	void logID();
	park_unit* findFreePlace(size_t iter);
	void declareParkStructure();
	void buildParkStructure();
	void addChildUnit();
	void addChildren(vector<tuple<unsigned int, string>> nameAndAmount);
	void removeChildren();
	void removeChildUnit(); ///TBD!!
	void removeChildUnit(unsigned int childID); ///TBD!!
	void placeTaken();//TBD!
	void placeFreed(); ///TBD!!
	void getDataFromFiles();
	unsigned getChildID();
	park_unit* accessData(int buildingID, int levelID, int SectorID, int PlaceID);//TBD
	park_unit* getChild(int i);
};

#endif