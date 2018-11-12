#pragma once
using namespace std;
#include <vector>
#include <iostream>



class park_unit
{
private:
	///tree - specific elements:
	park_unit *m_parent;
	
	int m_depthLevel;

	string m_unitname;
	unsigned long long m_childID;
	int takenPlacesCounter;
	int totalPlaces;


public:
	vector <park_unit *> m_children;

	park_unit();
	park_unit(park_unit* parent);
	~park_unit();

	void printID();
	void addChildUnit();
	void removeChildren();
	void removeChildUnit(); ///TBD!!

	void removeChildUnit(int childID); ///TBD!!
	void placeTaken(); ///TBD!!
	void placeFreed(); ///TBD!!
	park_unit* getChild(int i);
};
