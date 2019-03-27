#include "mapLoader.h"
#include "House.h"
#include "Money.h"
#include "Player.h"
#include "PowerPlant.h"
#include "Resources.h"
#include "SummaryCard.h"
#include <iostream>
using namespace std;


int main() {
	//Load the map, choose number of player and areas.
	mapLoader myLoader;
	int numOfPlayers = myLoader.Load();

	//Load Summary Cards
	cout << "Loading summary Card...\n";
	SummaryCard summaryCard[6];
	summaryCard[0].printInfo();

	cout << endl;


	//Load power plants cards and the step3 card
	cout << "Start loading power plant Cards:\n";
	PowerPlant *powerPlants = new PowerPlant[43];	
	powerPlants[0] = PowerPlant(3, 2, PowerPlant::oil, 1);
	powerPlants[1] = PowerPlant(4, 2, PowerPlant::coal, 1);
	powerPlants[2] = PowerPlant(5, 2, PowerPlant::hybrid, 1);
	powerPlants[3] = PowerPlant(6, 1, PowerPlant::garbage, 1);
	powerPlants[4] = PowerPlant(7, 3, PowerPlant::oil, 2);
	powerPlants[5] = PowerPlant(8, 3, PowerPlant::coal, 2);
	powerPlants[6] = PowerPlant(9, 1, PowerPlant::oil, 1);
	powerPlants[7] = PowerPlant(10, 2, PowerPlant::coal, 2);
	powerPlants[8] = PowerPlant(11, 1, PowerPlant::uranium, 2);
	powerPlants[9] = PowerPlant(12, 2, PowerPlant::hybrid, 2);
	powerPlants[10] = PowerPlant(13, 0, PowerPlant::eco, 1);
	powerPlants[11] = PowerPlant(14, 2, PowerPlant::garbage, 2);
	powerPlants[12] = PowerPlant(15, 2, PowerPlant::coal, 3);
	powerPlants[13] = PowerPlant(16, 2, PowerPlant::oil, 3);
	powerPlants[14] = PowerPlant(17, 1, PowerPlant::uranium, 2);
	powerPlants[15] = PowerPlant(18, 0, PowerPlant::eco, 2);
	powerPlants[16] = PowerPlant(19, 2, PowerPlant::garbage, 3);
	powerPlants[17] = PowerPlant(20, 3, PowerPlant::coal, 5);
	powerPlants[18] = PowerPlant(21, 2, PowerPlant::hybrid, 4);
	powerPlants[19] = PowerPlant(22, 0, PowerPlant::eco, 2);
	powerPlants[20] = PowerPlant(23, 1, PowerPlant::uranium, 3);
	powerPlants[21] = PowerPlant(24, 2, PowerPlant::garbage, 4);
	powerPlants[22] = PowerPlant(25, 2, PowerPlant::coal, 5);
	powerPlants[23] = PowerPlant(26, 2, PowerPlant::oil, 5);
	powerPlants[24] = PowerPlant(27, 0, PowerPlant::eco, 3);
	powerPlants[25] = PowerPlant(28, 1, PowerPlant::uranium, 4);
	powerPlants[26] = PowerPlant(29, 1, PowerPlant::hybrid, 4);
	powerPlants[27] = PowerPlant(30, 3, PowerPlant::garbage, 6);
	powerPlants[28] = PowerPlant(31, 3, PowerPlant::coal, 6);
	powerPlants[29] = PowerPlant(32, 3, PowerPlant::oil, 6);
	powerPlants[30] = PowerPlant(33, 0, PowerPlant::eco, 4);
	powerPlants[31] = PowerPlant(34, 1, PowerPlant::uranium, 5);
	powerPlants[32] = PowerPlant(35, 1, PowerPlant::oil, 5);
	powerPlants[33] = PowerPlant(36, 3, PowerPlant::coal, 7);
	powerPlants[34] = PowerPlant(37, 0, PowerPlant::eco, 4);
	powerPlants[35] = PowerPlant(38, 3, PowerPlant::garbage, 7);
	powerPlants[36] = PowerPlant(39, 1, PowerPlant::uranium, 6);
	powerPlants[37] = PowerPlant(40, 2, PowerPlant::oil, 6);
	powerPlants[38] = PowerPlant(42, 2, PowerPlant::coal, 6);
	powerPlants[39] = PowerPlant(44, 0, PowerPlant::eco, 5);
	powerPlants[40] = PowerPlant(46, 3, PowerPlant::hybrid, 7);
	powerPlants[41] = PowerPlant(50, 0, PowerPlant::hybrid, 6);
	powerPlants[42] = PowerPlant(0, 0, PowerPlant::step3, 0);

	for (int i = 0; i < 43; i++) {
		cout << powerPlants[i].toString() << endl;	}

	
	//cout << "-----------------------------------------------------------------------" << endl;
	//cout << "Shuffling power plant cards..." << endl;
	//powerPlants->shuffle(powerPlants, 43);
	//cout << "Shuffling completed:" << endl;

	//for (int i = 0; i < 43; i++) {
	//	cout << powerPlants[i].toString() << endl;
	//}
	



	//Load Houses objects
	cout << "\nStart loading color houses:\n";
	House houses[132];
	std::string Red = "Red";
	std::string Green = "Green";
	std::string Blue = "Blue";
	std::string Yellow = "Yellow";
	std::string Gold = "Gold";
	std::string Pink = "Pink";

	for (int i = 0; i < 22; i++) {
		houses[i] = House(Red);
	}
	for (int i = 22; i < 44; i++) {
		houses[i] = House(Green);
	}
	for (int i = 44; i < 66; i++) {
		houses[i] = House(Blue);
	}
	for (int i = 66; i < 88; i++) {
		houses[i] = House(Gold);
	}
	for (int i = 88; i < 110; i++) {
		houses[i] = House(Pink);
	}
	for (int i = 110; i < 132; i++) {
		houses[i] = House(Yellow);
	}

	houses[21].printInfo();
	houses[43].printInfo();
	houses[65].printInfo();
	houses[87].printInfo();
	houses[109].printInfo();
	houses[131].printInfo();
	


	//Load resources Tokens
	cout << "\nStart loading resources tokens:\n";
	Resources *array_resource = new Resources[84];
	
	//24 coal	
	for (int i = 0; i < 24; i++) {
		array_resource[i] = Resources(1, 0, 0, 0, 0);
	}

	//24 oil	
	for (int i = 22; i < 48; i++) {
		array_resource[i] = Resources(0, 1, 0, 0, 0);
	}

	//24 garbage	
	for (int i = 44; i < 72; i++) {
		array_resource[i] = Resources(0, 0, 1, 0, 0);
	}

	//12 uranium	
	for (int i = 66; i < 84; i++) {
		array_resource[i] = Resources(0, 0, 0, 1, 0);
	}

	for (int i = 0; i < 84; i++)
		cout << array_resource[i].toString() << endl;


	//Load Money
	cout << "\nStart loading money(elektro):\n";
	Money money1(1);
	Money money5(5);
	Money money10(10);
	Money money50(50);

	money1.printInfo();
	money5.printInfo();
	money10.printInfo();
	money50.printInfo();

	cout << endl;
	
	//Create Players
	cout << "\nStart Creating players:\n";	
	
	vector<Player> players(numOfPlayers, Player());
	cout << numOfPlayers << " players are created successfully.\n\n";

	//assign overview card, houses of a color and money to a player
	vector<House> vHouses;
	vHouses.push_back(houses[21]);
	vHouses.push_back(houses[43]);
	vHouses.push_back(houses[65]);
	vHouses.push_back(houses[87]);
	vHouses.push_back(houses[109]);
	vHouses.push_back(houses[131]);

	vector<House> pHouses;
	for (int i = 0; i < numOfPlayers; i++)
		pHouses.push_back(vHouses[i]);


	for (int i = 0; i < players.size(); i++) {		
		//assign a summary card
		cout << "Player " << i << " is given a overview card.\n";
		//assign wooden hourse of one color
		
		players[i].setHouse(pHouses[i]);
		cout << "Player " << i << " is given wooden houses of " << pHouses[i].getColor() << endl;
		cout << "Player " << i << " is given 50 elektros.\n";
		players[i].setMoney(50);
		cout << endl;
	}

	//display the player possession
	cout << "\nPrinting player possession:\n";
	for (int i = 0; i < players.size(); i++) {
		cout << "Player " << i << ": \n" << players[i].toString() << "\n";
	}


	cout << endl;
	
	
	delete[] powerPlants;
	delete[] array_resource;

	return 0;
}