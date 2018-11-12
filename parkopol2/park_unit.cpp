#include "pch.h"
#include "park_unit.h"
//#include <cstring>
//#include <vector>



park_unit::park_unit()
{
	m_parent = NULL;		//if pointer to parent is not given (new parking system root)
	m_depthLevel = 4;
}

park_unit::park_unit(park_unit* parent)
{
	if (parent) m_depthLevel = parent->m_depthLevel -= 1;
	else m_depthLevel = 4;	//default: 0 is parking place, 1- sector, 2- floor, 3 - building, 4 - system
	m_parent = parent;		//if pointer to parent is given (overload)
}

park_unit::~park_unit()
{
	if (!m_children.empty())
	{
		for (auto &i : m_children) delete i;
	}
	else
	{
		cout << endl << "m_children bylo puste\n";
	}
	m_children.clear();
}

void park_unit::printID()
{
	if (m_parent) m_parent->printID();
	cout << m_childID << ".";
}

void park_unit::addChildUnit()
{
		m_children.push_back(new park_unit(this)); 
		m_children.back()->m_childID = m_children.size();
		printID();
		
		cout << " \t\t-> Adding new child no.  ";
		m_children.back()->printID();
		cout << endl;
}

void park_unit::removeChildren()
{
	printID();
	cout << "\t\t-> deleting all children:" << endl;
	
	if (!m_children.empty())
	{
		for (auto &i : m_children) i->removeChildren();
	}
	else
	{
		//delete this;
	}
}

void park_unit::removeChildUnit()
{
	printID();
	cout << "\t\t-> deleting child no.  ";
	m_children.back()->printID();
	cout << endl;
	
	delete &(m_children.back());
	m_children.pop_back();

}

void park_unit::placeTaken()
{
}

void park_unit::placeFreed()
{
}

void park_unit::removeChildUnit(int childID)
{
}

park_unit * park_unit::getChild(int i)
{
	return m_children[i];
}

