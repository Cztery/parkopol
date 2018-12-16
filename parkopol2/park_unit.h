#include <vector>
#include <iostream>

using namespace std;

class park_unit
{
private:
	///tree - specific elements:
	park_unit *m_parent;
	
	int m_depthLevel;
	static vector<string> PlaceNames, SectorNames, LevelNames, BuildingNames;
	string m_unitname;
	int m_childID;
	int takenPlacesCounter;
	int totalPlaces;
	bool isDisabled;
	bool isTaken;


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
	void getDataFromFiles();
	park_unit* accessData(int buildingID, int levelID, int SectorID, int PlaceID);//TBD
	park_unit* getChild(int i);
};
