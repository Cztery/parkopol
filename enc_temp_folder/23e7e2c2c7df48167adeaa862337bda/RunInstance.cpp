#include "pch.h"
#include "RunInstance.h"


RunInstance::RunInstance()
{
}

void RunInstance::start()
{
	cout << "\t-----PARKOPOL(tm)-----"
		<< "\nSet parking price per minute:\n";
	cin >> m_pricePerMin;
	system("cls");

	parkingStructureRoot.menu();

	system("cls");

	while (1) clientMenu();
	
}

void RunInstance::clientMenu()
{
	cout << "\t-----PARKOPOL(tm)-----"
		<< "\n1. Get parking ticket & reserve parking place"
		<< "\n2. Find my car location by licence plates"
		<< "\n3. Get my current parking duration and price"
		<< "\n4. Pay and leave\n";
	int choice;
	string plates;
	float price = 0;
	park_unit* placeTemp=nullptr;
	car* carTemp = nullptr;
	cin >> choice;
	system("cls");
	cout << "\n\nEnter licence plates number:\n";
	cin >> plates;
	switch (choice)
	{
	case 1:
		getTicket(plates);
		break;
	case 2:
	case 3:
	case 4:
		
		placeTemp = parkingStructureRoot.findCarLocation(plates);
		if (placeTemp && choice == 2)
		{
			cout << "\n\n\tCar found:\n";
			placeTemp->printLocation();
		}
		else if (!placeTemp)
		{
			cout << "\n\n\tSorry, we couldn't find your car\n";
		}
		
		if(choice == 2) break;
	
		carTemp = placeTemp->getCar();
		carTemp->printParkingDuration(0);
		price = carTemp->checkParkingDuration() / 60 * m_pricePerMin;
		cout << endl <<"Parking charge:\t"<< price<<endl;
		if (choice == 3) break;
		placeTemp->placeFreed();
		cout << "Place freed, parking left\n\n";
		

	default:
		;
	}
}


RunInstance::~RunInstance()
{
}

car* RunInstance::getTicket(string plateID)
{
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
			placeProposition->printID();
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
	car* newcar = new car(plateID, entryTime);
	placeProposition->placeTaken(newcar);
	return newcar;
}
