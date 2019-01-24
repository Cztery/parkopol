#include "pch.h"
#include "park_unit.h"


park_unit* park_unit::m_root;
vector<string> park_unit::unitNames = { "root" };
vector<unsigned int> park_unit::unitDefaultAmounts = { 0 };
park_unit::park_unit()
{
	m_parent = NULL;		//if pointer to parent is not given (new parking system root)
	m_depthLevel = 0;
	m_root = this;
}

park_unit::park_unit(park_unit *parent)
{
	if (parent) m_depthLevel = parent->m_depthLevel + 1;
	else m_depthLevel = 0;	//default: 0 is parking tree root, max num is parking tree leaf/parking place
	m_parent = parent;		//if pointer to parent is given (overload)
}

park_unit::park_unit(park_unit * parent, vector<tuple<unsigned int, string>> nameAndAmount)
{
	vector<tuple<unsigned int, string>> newNameAndAmount(nameAndAmount.begin()+1,nameAndAmount.end());
	for (unsigned int i = 0; i < std::get<0>(nameAndAmount[0]); i++)
	{
		if (nameAndAmount.begin() != nameAndAmount.end())
			addChildren(newNameAndAmount);
		
	}
}

park_unit::~park_unit()
{
	if (m_children.empty())
	{
		logID();
		clog << "\t\t-> m_children vector is empty\n";
	}
	else
	{
		for (auto &i : m_children)
		{
			logID();
			cout << endl << "\t\t-> deleting child no. ";
			i->logID();
			cout << endl;
			delete i;
		}
	}
	m_children.clear();
}

void park_unit::menu()
{
	cout << "\tPARKOPOL 1.0 " << "\nParking scheme initialization:"
		<< "\n1. Load from file"
		<< "\n2. Build parking structure manually";
	int choice;
	cin >> choice;
	switch (choice)
	{
	case 1:
		loadStructure();
		break;
	case 2:
		declareParkStructure();
		break;
	case 0:
		return;
	default:
		cout << "\n Incorrect choice, try again";
		break;
	}

}

void park_unit::loadStructure()
{
}

void park_unit::logID()
{
	if (m_parent) m_parent->logID();
	clog << m_childID << ".";
}
//park_unit* park_unit::findFreePlace(size_t iter)
//{
//	park_unit* freePlace = NULL;
//	if (m_depthLevel == unitNames.size() - 1 && iter == m_childID)
//	{
//		freePlace = m_parent->findFreePlace(m_childID + 1);
//	}
//	else if (m_depthLevel == unitNames.size() - 1)
//	{
//		if (isTaken)
//			return NULL;
//		else
//			return this;
//	}
//	else if (m_depthLevel < unitNames.size() - 1)
//	{
//		for (size_t i = iter; i < m_children.size(); i++)
//		{
//			freePlace = m_children[i]->findFreePlace();
//			if (freePlace) return freePlace;
//		}
//		
//	}
//	else
//		freePlace = m_parent->findFreePlace(m_childID);
//		
//		return nullptr;
//}
park_unit* park_unit::findFreePlace(size_t iter = 0)
{
	logID();
	cout << "\t\t-> running find function\n";
	park_unit* freePlace = NULL;
	if (m_depthLevel == unitNames.size() - 2)
	{
		for (size_t i = iter; i < m_children.size(); i++)
		{
			freePlace = m_children[i];
			if (freePlace) return freePlace;
		}
		return NULL;
	}
	else if (m_depthLevel < unitNames.size() - 2)
	{
		for (size_t i = iter; i < m_children.size(); i++)
		{
			freePlace = m_children[i]->findFreePlace();
			if (freePlace) 
				return freePlace;
		}
		if (m_parent)
			freePlace = m_parent->findFreePlace(m_childID);
		else 
			return NULL;
		
	}
	else if (m_depthLevel == unitNames.size() - 1)
		freePlace = m_parent->findFreePlace(m_childID);
		
	return freePlace;
}

//park_unit* park_unit::findFreePlace(size_t iter = 0)
//
//{
//	park_unit* freePlace = NULL;
//	//search can be started at any place in the structure, default is first child
//
//	if (m_depthLevel == unitNames.size() - 1)
//	{
//		if (isTaken)
//			return NULL;
//		else
//			return this;
//	}
//	else if (m_depthLevel < unitNames.size() - 1)
//	{
//		for (size_t i = iter + 1; i < m_children.size(); i++)
//		{
//			freePlace = m_children[i]->findFreePlace();
//			if (freePlace) return freePlace;
//		}
//		if (!freePlace)
//		{
//			if (m_parent == NULL)
//				return NULL;
//			else
//				m_parent->findFreePlace(m_childID);
//		}
//	}
//	else
//		return NULL;
//
//		if (m_depthLevel == unitNames.size() - 1 && iter)
//		{
//			if (isTaken)
//				return NULL;
//			else
//				return this;
//		}
//		else if (m_depthLevel < unitNames.size() - 1)
//		{
//			for (auto i = iter + 1; i < m_children.size(); i++)
//			{
//				freePlace = m_children[iter]->findFreePlace();
//				if (freePlace) return freePlace;
//			}
//		}
//		else
//			m_parent->findFreePlace();
//	return nullptr;
//}
void park_unit::declareParkStructure()
{
	
	int choice = 1;
	string tmpLevelName;
	unsigned int tmpLevelAmount;
	while (choice == 1)
	{
		cout << "\tPARKOPOL 1.0 " << "\nParking scheme building:";
		cout << "\n1. Add new level"
			 << "\n2. Finish creating structure"
			 << "\n0. Cancel and discard changes";
		cin >> choice;
	
		switch (choice)
		{
		case 1:
			cout << "\nEnter name of parking tree level:\n";
			cin >> tmpLevelName;
			cout << "\nEnter default number of " << tmpLevelName << " units:\n";
			cin >> tmpLevelAmount;
			park_unit::unitNames.push_back(tmpLevelName);
			park_unit::unitDefaultAmounts.push_back(tmpLevelAmount);
			break;
		case 2:
			cout << "\n Finished declararation of tree structure, run buildParkStructure():\n";
			buildParkStructure();
			break;
		case 0:
			return;
		default:
			break;
		}
	}
}
void park_unit::buildParkStructure()
{
	if (m_depthLevel < unitDefaultAmounts.size()-1)
	{
		for (int i = 1; i <= unitDefaultAmounts[m_depthLevel+1]; i++)
		{
			addChildUnit();
			m_children.back()->buildParkStructure();
			
		}
	}
		
}
void park_unit::addChildUnit()
{
	m_children.push_back(new park_unit(this)); 
	m_children.back()->m_childID = static_cast<unsigned int>(m_children.size());
	logID();
	clog << " \t\t-> Adding new child "<< unitNames[m_depthLevel+1]<<" no.  ";
	m_children.back()->logID();
	clog << endl;
}

void park_unit::addChildren(vector<tuple<unsigned int, string>> nameAndAmount)
{
	vector<tuple<unsigned int, string>> newNameAndAmount(nameAndAmount.begin(), nameAndAmount.end()); //creating subvector of names and numbers for organizational subunits of parking system
	for (auto a : nameAndAmount)
	{
		m_children.push_back(new park_unit(this, newNameAndAmount));
		m_children.back()->m_childID = static_cast<unsigned int>(m_children.size());
		logID();
		clog << " \t\t-> Adding new child no.  ";
		m_children.back()->logID();
		clog << endl;
	}
}

void park_unit::removeChildren()
{
	logID();
	cout << "\t\t-> deleting all children:" << endl;
	
	if (!m_children.empty())
	{
		for (auto &i : m_children) i->removeChildren();
	}
}

void park_unit::removeChildUnit()
{
	logID();
	cout << "\t\t-> deleting child no.  ";
	m_children.back()->logID();
	cout << endl;
	
	delete &(m_children.back());
	m_children.pop_back();
}

void park_unit::removeChildUnit(unsigned int childID)
{
	logID();
	assert(childID >= 0 && childID < static_cast<unsigned int>(m_children.size()));
	cout << "\t\t-> deleting child no.  ";
	m_children[childID]->logID();
	cout << endl;

	delete &(m_children.back());
	m_children.pop_back();
}


void park_unit::placeTaken()
{
	isTaken = true;
}

void park_unit::placeFreed()
{
	isTaken = false;
	//if (m_parent) m_parent->takenPlacesCounter--;
}

//void park_unit::removeChildUnit(int childID)
//{
//	delete &(m_children[childID]);
//}
void park_unit::getDataFromFiles() {
			string str;
		ifstream file0("TreeStructure.txt");
		while (getline(file0, str)) {
			unitNames.push_back(str);
		}
		
}

unsigned park_unit::getChildID()
{
	return m_childID;
}

park_unit * park_unit::getChild(int i)
{
	return m_children[i];
}

park_unit* accessData(int buildingID, int levelID, int SectorID, int PlaceID)//TBD
{
	return 0;
};
