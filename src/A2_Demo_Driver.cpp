#include "mapLoader.h"
#include "House.h"
#include "Money.h"
#include "Player.h"
#include "PowerPlant.h"
#include "Resources.h"
#include "SummaryCard.h"
#include "Phase1_2.h"
#include "Phase5.h"
#include <iostream>
#include <time.h>
#include <vector>

using namespace std;


int main() {

	/*

	//Part 1: Game start

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





	/*





	//Part 2: Game play: main game loop Phase 1 and 2
	//Determine Player Order
	//Auction Power Plants.
	//Initialize how many players

	cout << "Please enter the number of the players: ";
	cin >> numberOfPlayers;
	cout << endl;
	Player *players = new Player[numberOfPlayers];

	//set a simple name for each player
	for (int i = 0; i < numberOfPlayers; i++) {
		string name = "Player" + to_string(i + 1);
		players[i].setName(name);
	}

	//Create power plant cards
	//int numberOfCards = 43;
	vector<PowerPlant> powerPlants(43);
	//PowerPlant *powerPlants = new PowerPlant[numberOfCards];

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
	powerPlants[42] = PowerPlant(99, 0, PowerPlant::step3, 0);

	//give a random order in the first turn
	if (turn == 1) {
		shufflePlayers(players, numberOfPlayers);
		for (int i = 0; i < numberOfPlayers; i++) {
			//players[i].setNumOfCity(i);
			cout << players[i].getName() << endl;
			cout << players[i].toString() << endl;
			cout << endl;
		}
	}

	////*************************test check resources*************************
	////coal: 3
	//players[0].setCoalNum(3);
	//players[0].setPowerPlant(powerPlants[12], 0);
	////oil: 3
	//players[0].setOilNum(3);
	//players[0].setPowerPlant(powerPlants[13], 1);
	////uranium: 2
	//players[0].setUraniumNum(2);
	//players[0].setPowerPlant(powerPlants[14], 2);
	//players[0].setNumOfPowerPlant(3);
	////change to garbage: 2
	//buyCard(players[0], powerPlants[16]);

	////coal: 5
	//players[1].setCoalNum(5);
	//players[1].setPowerPlant(powerPlants[12], 0);
	////oil: 5
	//players[1].setOilNum(5);
	//players[1].setPowerPlant(powerPlants[13], 1);
	////hybrid: 2 (1 coal + 1 oil)
	//players[1].setPowerPlant(powerPlants[9], 2);
	//players[1].setNumOfPowerPlant(3);
	////change to garbage: 2
	//buyCard(players[1], powerPlants[16]);
	////*************************test check resources*************************


	////***********************test set cards order in each players & test if a player have 4 cards*************************
	//for (int i = 0; i < numberOfPlayers; i++) {
	//	int numOfCards = players[i].getNumOfPowerPlant();
	//	while (numOfCards < 3) {
	//		players[i].setPowerPlant(powerPlants.front(), numOfCards);
	//		powerPlants.erase(powerPlants.begin());
	//		numOfCards++;
	//		players[i].setNumOfPowerPlant(numOfCards);
	//	}
	//	setCardOwnedByPlayer(players[i]);
	//}
	//for (int i = 0; i < numberOfPlayers; i++) {
	//	cout << players[i].getName() << endl;
	//	cout << players[i].toString() << endl;
	//	cout << endl;
	//}
	//cout << endl;
	//setPlayerOrder(players, numberOfPlayers);
	//cout << "New order of the players " << endl;
	//for (int i = 0; i < numberOfPlayers; i++) {
	//	cout << players[i].getName() << endl;
	//	cout << players[i].toString() << endl;
	//	cout << endl;
	//}
	//cout << endl;

	////test if a player have 4 cards
	//buyCard(players[0], powerPlants[20]);
	////***********************test set cards order in each players & test if a player have 4 cards*************************


	//Creat market area
	//create Market
	vector<PowerPlant> market(0);
	//put first 8 cards into market
	for (int i = 0; i < 8; i++) {
		market.push_back(powerPlants[0]);
		powerPlants.erase(powerPlants.begin());
	}


	//Print the cards in the market
	cout << "------------------------------Market------------------------------" << endl;
	for (int i = 0; i < market.size(); i++) {
		cout << market[i].toString() << endl;
	}
	cout << endl;

	//
	cout << "------------------------------After shuffle------------------------------" << endl;
	PowerPlant::shuffle(powerPlants);
	//for (int i = 0; i < powerPlants.size(); i++) {
	//   cout << powerPlants[i].toString() << endl;
    //}
	cout << endl;

	//Find cards: powerPlant 13 & step 3
	if (turn == 1) {
		for (int i = 0; i < powerPlants.size(); i++) {
			if (powerPlants[i].getNumber() == 13) {
				PowerPlant temp1;
				temp1 = powerPlants[i];
				powerPlants[i] = powerPlants[0];
				powerPlants[0] = temp1;
			}
			if (powerPlants[i].getTypeName() == "step3") {
				PowerPlant temp2;
				temp2 = powerPlants[i];
				powerPlants[i] = powerPlants[powerPlants.size() - 1];
				powerPlants[powerPlants.size() - 1] = temp2;
			}

		}
		cout << "--------------------After Setting Card Number13 & Card Step3--------------------" << endl;
		for (int i = 0; i < powerPlants.size(); i++) {
			cout << powerPlants[i].toString() << endl;
		}
		cout << endl;
	}


	//auction process
	auctionPhase(players, powerPlants, market, numberOfPlayers);


	cout << "Phase finish" << endl;
	cout << endl;

	//if no one buy card, delete the smallest one
	if (checkNoOneBuyCard(players)) {
		cout << "No one buy power plant card in this turn" << endl;
		cout << "------------------------------Market (Updated)------------------------------" << endl;
		market[0] = powerPlants.front();
		setMarketOrder(market);
		powerPlants.erase(powerPlants.begin());
		for (int i = 0; i < market.size(); i++) {
			cout << market[i].toString() << endl;
		}
		cout << endl;
	}


	// set the order of the players at the end of each turn
	setPlayerOrder(players, numberOfPlayers);
	cout << "New order of the players " << endl;
	for (int i = 0; i < numberOfPlayers; i++) {
		cout << players[i].getName() << endl;
		cout << players[i].toString() << endl;
		cout << endl;
	}

	cout << "Moving to the next phase" << endl;
	turn++;
	cout << endl;

	delete [] players;
	system("pause");
	return 0;






	/**/






	//Part 3: Game play: main game loop Phase 3 and 4
	//Buying Resources and building
	//create testing player
	const int numOfPlayer = 3;
	Player players[numOfPlayer];
	players[0].setName("Allen");
	players[1].setName("Bob");
	players[2].setName("Cara");
	//players[3].setName("David");

	//Initialize the map for demo
	Graph myGameMap(8);

	map<string, int> cityNameIDPair;
	cityNameIDPair.insert(pair<string, int>("Boston", 0));
	cityNameIDPair.insert(pair<string, int>("New York", 1));
	cityNameIDPair.insert(pair<string, int>("Philadelphia", 2));
	cityNameIDPair.insert(pair<string, int>("Washington DC", 3));
	cityNameIDPair.insert(pair<string, int>("Pittsburgh", 4));
	cityNameIDPair.insert(pair<string, int>("Detroit", 5));
	cityNameIDPair.insert(pair<string, int>("Buffalo", 6));
	cityNameIDPair.insert(pair<string, int>("Norfolk", 7));


	createBaseCity(&myGameMap, cityNameIDPair);

	addEdge(&myGameMap, "Boston", "New York", 3, cityNameIDPair);
	addEdge(&myGameMap, "New York", "Philadelphia", 0, cityNameIDPair);
	addEdge(&myGameMap, "Philadelphia", "Washington DC", 3, cityNameIDPair);
	addEdge(&myGameMap, "Washington DC", "Pittsburgh", 6, cityNameIDPair);
	addEdge(&myGameMap, "Pittsburgh", "Detroit", 6, cityNameIDPair);
	addEdge(&myGameMap, "Detroit", "Buffalo", 7, cityNameIDPair);
	addEdge(&myGameMap, "Buffalo", "Pittsburgh", 7, cityNameIDPair);
	addEdge(&myGameMap, "Buffalo", "New York", 8, cityNameIDPair);
	addEdge(&myGameMap, "Washington DC", "Norfolk", 5, cityNameIDPair);


	//Initialize resources on the map
	//Resources(int c, int o, int g, int u, int p);
	Resources *array_resource = new Resources[12];
	array_resource[0] = Resources(0, 0, 0, 0, 1);
	array_resource[1] = Resources(3, 0, 0, 0, 2);
	array_resource[2] = Resources(3, 1, 0, 0, 3);
	array_resource[3] = Resources(3, 3, 0, 0, 4);
	array_resource[4] = Resources(3, 3, 0, 0, 5);
	array_resource[5] = Resources(0, 3, 2, 0, 6);
	array_resource[6] = Resources(0, 3, 2, 0, 7);
	array_resource[7] = Resources(0, 3, 3, 0, 8);
	array_resource[8] = Resources(0, 0, 0, 0, 10);
	array_resource[9] = Resources(0, 0, 0, 1, 12);
	array_resource[10] = Resources(0, 0, 0, 1, 14);
	array_resource[11] = Resources(6, 0, 0, 1, 16);


	//create 43 powerPlants cards
	std::vector<PowerPlant> powerPlants(43);

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

	std::vector<PowerPlant> market(0);




	//Assume Player 1 has 150 Elektro PowerPlants 5,6,9

	players[0].setPowerPlant(powerPlants[5], 0);
	players[0].setPowerPlant(powerPlants[6], 1);
	players[0].setPowerPlant(powerPlants[9], 2);
	players[0].setNumOfPowerPlant(3);
	players[0].setMoney(500);

	//Assume Player 2 has 100 Elektro PowerPlants 20,21,26
	players[1].setPowerPlant(powerPlants[20], 0);
	players[1].setPowerPlant(powerPlants[21], 1);
	players[1].setPowerPlant(powerPlants[26], 2);
	players[1].setNumOfPowerPlant(3);
	players[1].setMoney(500);

	//Assume Player 3 has 100 Elektro PowerPlants 20,21,26
	players[2].setPowerPlant(powerPlants[31], 0);
	players[2].setPowerPlant(powerPlants[39], 1);
	players[2].setPowerPlant(powerPlants[16], 2);
	players[2].setNumOfPowerPlant(3);
	players[2].setMoney(500);

	//put first 8 cards into market
	for (int i = 0; i < 8; i++) {
		market.push_back(powerPlants[0]);
		powerPlants.erase(powerPlants.begin());
	}

	//Initialization finished!


	//======================================================================
	std::cout << "[INFO] PHASE3: Buying Resources" << std::endl;

	//buy resources
	for (int i = numOfPlayer-1; i >= 0; i--) {
		players[i].buyResources(array_resource);
	}

	//======================================================================
	std::cout << "[INFO] PHASE4: Building" << std::endl;
	int step = 1;
	/*
	bool goToStep3 = false;
	for (int i = numOfPlayer - 1; i >= 0; i--)
	{
		bool result = players[i].building(&myGameMap, step, 6, market, powerPlants);
		if (!goToStep3)
			goToStep3 = result;
	}


	//======================================================================
	//just for testing in step 3
	/*

	cout << "-----------------------------------------------" << endl;
	cout << "Test case for step 3" << endl;

	for (size_t i = 0; i < powerPlants.size(); i++) {
		if (powerPlants[i].getTypeName() == "step3") {
			PowerPlant temp2;
			temp2 = powerPlants[i];
			powerPlants[i] = powerPlants[0];
			powerPlants[0] = temp2;
		}
	}
	cout << powerPlants[0].toString() << endl;
	cout << "[INFO] Now the STEP 3 card is on the top of the remaining power plants!" << endl;
	bool goToStep3 = false;
	for (int i = numOfPlayer - 1; i >= 0; i--) {
		bool result = players[i].building(&myGameMap, step, 6, market, powerPlants);
		if (!goToStep3) {
			goToStep3 = result;
		}
	}

	/*
	if (step != 3) {
		if (goToStep3) {
			step = 3;
		}
	}


	//======================================================================
	std::cout << "[INFO] Print info of all the players:" << std::endl;
	for(int i = 0; i<numOfPlayer;i++){
		std::cout<< players[i].toString() <<std::endl;
	}
	delete[] array_resource;
	system("pause");
	return 0;




	/*






	//Part 4: Game play: main game loop Phase 5
	//test Phase 5 Bureaucracy
	//Initialize 4 players
	Player * players = new Player[4];
	players[0] = Player();
	players[1] = Player();
	players[2] = Player();
	players[3] = Player();

	//set player1:  owns 6 cities, 0 Elektro, 4 coal, 6 oil, 2 garbage, the power plants 06, 07 and 10
	players[0].setName("Allen");
	players[0].setMoney(0);
	players[0].setNumOfCity(6);
	players[0].setNumOfPowerPlant(3);
	players[0].setPowerPlant(PowerPlant(6, 1, PowerPlant::garbage, 1),0);
	players[0].setPowerPlant(PowerPlant(7, 3, PowerPlant::oil, 2),1);
	players[0].setPowerPlant(PowerPlant(10, 2, PowerPlant::coal, 2),2);
	players[0].setCoalNum(4);
	players[0].setOilNum(6);
	players[0].setGarbageNum(2);

	//set player2:  owns 3 cities, 2 Elektro, 2 coal, 2 oil, 2 uranium, the power plants 05 and 11
	players[1].setName("Bob");
	players[1].setMoney(2);
	players[1].setNumOfCity(3);
	players[1].setNumOfPowerPlant(2);
	players[1].setPowerPlant(PowerPlant(5, 2, PowerPlant::hybrid, 1),0);
	players[1].setPowerPlant(PowerPlant(11, 1, PowerPlant::uranium, 2),1);
	players[1].setCoalNum(2);
	players[1].setOilNum(2);
	players[1].setUraniumNum(2);

	//set player3:  owns 0 cities, 3 Elektro, 2 garbage, the power plants 06
	players[2].setName("Cara");
	players[2].setMoney(3);
	players[2].setNumOfCity(1);
	players[2].setNumOfPowerPlant(1);
	players[2].setPowerPlant(PowerPlant(16, 2, PowerPlant::oil, 3),0);
	players[2].setOilNum(2);

	//set player4:  owns 2 cities, 4 Elektro, 1 coal, the power plants 15
	players[3].setName("David");
	players[3].setMoney(4);
	players[3].setNumOfCity(2);
	players[3].setNumOfPowerPlant(1);
	players[3].setPowerPlant(PowerPlant(15, 2, PowerPlant::coal, 3),0);
	players[3].setCoalNum(1);


	//Initialize resources on the map
	//test for re-supply the resource market:  10 coal, 2 oil, and 1 garbage were brought by players
	Resources *array_resource = new Resources[12];
	array_resource[0] = Resources(0, 0, 0, 0, 1);
	array_resource[1] = Resources(0, 0, 0, 0, 2);
	array_resource[2] = Resources(0, 1, 0, 0, 3);
	array_resource[3] = Resources(2, 3, 0, 0, 4);
	array_resource[4] = Resources(3, 3, 0, 0, 5);
	array_resource[5] = Resources(3, 3, 0, 0, 6);
	array_resource[6] = Resources(3, 3, 2, 0, 7);
	array_resource[7] = Resources(3, 3, 3, 0, 8);
	array_resource[8] = Resources(0, 0, 0, 0, 10);
	array_resource[9] = Resources(0, 0, 0, 0, 12);
	array_resource[10] = Resources(0, 0, 0, 1, 14);
	array_resource[11] = Resources(0, 0, 0, 1, 16);


	//create 43 powerPlants cards
	std::vector<PowerPlant> powerPlants(43);
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

	//create Market
	std::vector<PowerPlant> market(0);

	//put first 8 cards into market
	for (int i = 0; i < 8; i++) {
		market.push_back(powerPlants[0]);
		powerPlants.erase(powerPlants.begin());
	}
	PowerPlant ecoCard = powerPlants[2];
	powerPlants.erase(powerPlants.begin()+2);
	PowerPlant step3Card = powerPlants.back();
	powerPlants.pop_back();
	PowerPlant::shuffle(powerPlants);
	powerPlants.insert(powerPlants.begin(),ecoCard);
	powerPlants.push_back(step3Card);



	//phase 5 begins
	cout << "[INFO] PHASE5: Bureaucracy" << endl;
	Phase5 phase5 = Phase5(players, 4);
	phase5.earnCash();




	//print the resources in the market before re-supply
	cout << "[INFO] Here is the Resource Market:" << endl;
	for (int i = 0; i < 12; i++) {
		cout << array_resource[i].toString() << endl;
	}
	cout << "-----------------------------------------------" << endl;

	//re-supply the resource market
	phase5.reSupplyResource(array_resource);

	//print the resources after re-supply
	cout << "-----------------------------------------------" << endl;
	std::cout << "[INFO] Here is the Resource Market:" << std::endl;
	for (int i = 0; i < 12; i++) {
		cout << array_resource[i].toString() << endl;
	}




	//update the power plant market

	phase5.updateMarket(powerPlants, market);


	//print the power plant market and the draw stack
	cout << "-----------------------------------------------" << endl;
	std::cout << "[INFO] Here is the Power Plant Market:" << std::endl;
	for(size_t i = 0; i < market.size(); i++){
		cout << market[i].toString() << endl;
	}
	cout << "-----------------------------------------------" << endl;
	std::cout << "[INFO] Here is the Power Plant Draw Stack:" << std::endl;
	for (size_t i = 0; i < powerPlants.size(); i++) {
		cout << powerPlants[i].toString() << endl;
	}


	//each player possession at the end of this phase
	cout << "-----------------------------------------------" << endl;
	cout << "Each player possession at the end of this phase 5:" << endl;
	Player::printPlayerPossession(players,4);






	//just for testing in step 3
	cout << "-----------------------------------------------" << endl;
	cout << "test for step 3" << endl;
	for (size_t i = 0; i < powerPlants.size(); i++) {
		if (powerPlants[i].getTypeName() == "step3") {
			PowerPlant temp2;
			temp2 = powerPlants[i];
			powerPlants[i] = powerPlants[0];
			powerPlants[0] = temp2;
		}
	}
	phase5.updateMarket(powerPlants, market);

	//print the power plant market and the draw stack
	std::cout << "[INFO] Here is the Power Plant Market:" << std::endl;
	for (size_t i = 0; i < market.size(); i++) {
		cout << market[i].toString() << endl;
	}
	cout << "-----------------------------------------------" << endl;
	std::cout << "[INFO] Here is the Power Plant Draw Stack:" << std::endl;
	for (size_t i = 0; i < powerPlants.size(); i++) {
		cout << powerPlants[i].toString() << endl;
	}





	//release memory
	delete[] array_resource;
	delete[] players;

	return 0;


	/**/




}