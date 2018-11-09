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
	int m_childId;


public:
	vector <park_unit *> m_children;

	park_unit();
	park_unit(park_unit* parent);
	~park_unit();

	void printID();
	void addChildUnit();
	void removeChildUnit(int childID);
	park_unit* getChild(int i);
};

