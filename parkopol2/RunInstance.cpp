#include "pch.h"
#include "RunInstance.h"


RunInstance::RunInstance()
{
}

void RunInstance::start()
{
	parkingStructureRoot.menu();
	getTicket();
	
}


RunInstance::~RunInstance()
{
}

car* RunInstance::getTicket()
{
	string plateID;
	cout << "\nEnter your car's licence plate ID:\n";
	cin >> plateID;
	
	time_t entryTime = time(NULL); //get current time
	struct tm timestruct;
	localtime_s(&timestruct, &entryTime);
	char entryTimeText[26];
	asctime_s(&entryTimeText[0], 26, &timestruct);

	cout << "\nEntry time: "<<entryTimeText <<endl;
	char agree = 's';
	park_unit* placeProposition = NULL;
	while (agree=='n' || agree == 's')
	{
		if (agree == 's')//run in root 
			placeProposition = parkingStructureRoot.findFreePlace(0);
		if (agree == 'n')
			placeProposition = placeProposition->findFreePlace(placeProposition->getChildID());
		if (placeProposition && (agree == 'n' || agree == 's'))
		{
			cout << "\nFree place found, place id: ";
			placeProposition->logID();
			cout << "\ndo you accept to park here? (y - accept / n - next proposition / 0 - resign)\n";
			cin >> agree;
		}
		else
		{
			cout << "\nNo place found, try another time!\n";
			agree = '0';
		}
	}
	if (agree == '0') return NULL;
	car* newcar = new car(plateID, entryTime, placeProposition);
	placeProposition->placeTaken();
	return newcar;
}
