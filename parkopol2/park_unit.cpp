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
	if (m_depthLevel == unitNames.size() - 1)
	{
		countFree(1);
		countTotal(1);
	}
}


park_unit::~park_unit()
{
	if (m_depthLevel == unitNames.size() - 1)
	{
		countTotal(-1);
		if (!m_isTaken) countFree(-1);
	}
	if (m_children.empty())
	{
		printID();
		cout << "\t\t-> m_children vector is empty\n";
	}
	else
	{
		for (auto &i : m_children)
		{
			printID();
			cout << endl << "\t\t-> deleting child no. ";
			i->printID();
			cout << endl;
			delete i;
		}
	}
	m_children.clear();
}

void park_unit::countFree(int change = 1)
{
	m_freePlacesCounter += change;
	if (m_parent) m_parent->countFree(change);
}


void park_unit::countTotal(int change=1)
{
	totalPlaces += change;
	if (m_parent) m_parent->countTotal(change);
}

void park_unit::menu()
{

	cout << "\n\tPARKOPOL 1.0 " << "\nParking scheme initialization:"
		<< "\n1. Load from file"
		<< "\n2. Build parking structure manually\n";
	int choice;
	cin >> choice;
	switch (choice)
	{
	case 1:
		loadStructure();
		break;
	case 2:
		system("cls");
		declareParkStructure();
		break;
	case 0:
		return;
	default:
		cout << "\n Incorrect choice, try again\n";
		break;
	}

}

void park_unit::loadStructure()
{
}

void park_unit::printID()
{
	if (m_parent) m_parent->printID();
	cout << m_childID << ".";
}

void park_unit::printLocation()
{
	if (m_parent) m_parent->printLocation();
	cout << unitNames[m_depthLevel]<< ":\t"<< m_childID << endl;
}

park_unit* park_unit::findFreePlace(size_t iter = 0)
{
	printID();
	cout << "\t\t-> running find function\n";
	park_unit* freePlace = NULL;
	if (m_depthLevel == unitNames.size() - 2)
	{
		for (size_t i = iter; i < m_children.size(); i++)
		{
			freePlace = m_children[i];
			if (freePlace && !(freePlace->isTaken())) return freePlace;
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

park_unit * park_unit::findCarLocation(string plates)
{
	
	park_unit * location = nullptr;
	if (m_parkedCar && m_parkedCar->getPlates() == plates)
	{
		return this;
	}
	else if (totalPlaces - m_freePlacesCounter > 0)
	{
		for (size_t i = 0; i < m_children.size(); i++)
		{
			location = m_children[i]->findCarLocation(plates);
			if (location) return location;
		}
	}
	else return nullptr;
	
}

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
			 << "\n0. Cancel and discard changes\n";
		cin >> choice;
		system("cls");
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

			cin.get(); cin.get();
			system("cls");
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
	printID();
	cout << " \t\t-> Adding new child "<< unitNames[m_depthLevel+1]<<" no.  ";
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
}

void park_unit::removeChildUnit()
{
	printID();
	cout << "\t\t-> deleting LAST child no.  ";
	m_children.back()->printID();
	cout << endl;
	
	delete &(m_children.back());
	m_children.pop_back();
}

void park_unit::removeChildUnit(unsigned childID)
{
	printID();
	assert(childID >= 0 && childID < static_cast<unsigned>(m_children.size()));
	cout << "\t\t-> deleting CHOSEN child no.  ";
	m_children[childID]->printID();
	cout << endl;

	delete &(m_children.back());
	m_children.pop_back();
}


void park_unit::placeTaken(car* newcar)
{
	m_isTaken = true;
	m_parkedCar = newcar;
	countFree(-1);
}

void park_unit::placeFreed()
{
	m_isTaken = false;
	delete m_parkedCar;
	m_parkedCar = nullptr;
	countFree();
}


void park_unit::getDataFromFiles() {
			string str;
		ifstream file0("TreeStructure.txt");
		while (getline(file0, str)) {
			unitNames.push_back(str);
		}
		
}

car * park_unit::getCar()
{
	return m_parkedCar;
}

unsigned park_unit::getChildID()
{
	return m_childID;
}

bool park_unit::isTaken()
{
	return m_isTaken;
}

park_unit * park_unit::getChild(int i)
{
	return m_children[i];
}

park_unit* accessData(int buildingID, int levelID, int SectorID, int PlaceID)//TBD
{
	return 0;
};
