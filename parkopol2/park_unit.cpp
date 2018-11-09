#include "pch.h"
#include "park_unit.h"
//#include <cstring>
//#include <vector>



park_unit::park_unit()
{
	m_parent = NULL;
}

park_unit::park_unit(park_unit* parent)
{
	if (parent) m_depthLevel = parent->m_depthLevel + 1;
}

park_unit::~park_unit()
{
	for (auto &i : m_children) delete i;
	m_children.clear();
}

void park_unit::printID()
{
	if (m_parent) m_parent->printID();
	cout << m_childId << ".";
}

void park_unit::addChildUnit()
{
		m_children.push_back(new park_unit(this));
		m_children.back()->m_childId = m_children.size();
		printID();
		cout << " ->\t Adding new child no" << m_children.size() << endl;;
}

void park_unit::removeChildUnit(int childID)
{
}

park_unit * park_unit::getChild(int i)
{
	return m_children[i];
}



//class park_unit
//{
//	//private:
//public:
//	park_unit *m_parent;
//	std::vector <park_unit *> m_children;
//	int m_depthLevel;
//	string m_unitname;
//	int m_childId;
//	//public:
//	park_unit(park_unit *parent = NULL)
//	{
//		m_parent = parent;
//		if (parent) m_depthLevel = parent->m_depthLevel + 1;
//	}
//	void printId()
//	{
//		if (m_parent) m_parent->printId();
//		cout << m_childId << ".";
//	}
//	void add_child_unit()
//	{
//		m_children.push_back(new park_unit(this));
//		m_children.back()->m_childId = m_children.size();
//		printId();
//		cout << " ->\t Adding new child no" << m_children.size() << endl;
//	}
//	void remove_child_unit(int childID)
//	{
//		m_children.erase(m_children.begin() + childID);
//	}
//	~park_unit()
//	{
//		for (auto &i : m_children) delete i;
//		m_children.clear();
//	}
//
//
//};