#include "Game.h"

//default constructor
Game::Game() {};

Game::Game(int numOfPlayer) {
	players = new Player[numOfPlayer];
	this->numOfPlayer = numOfPlayer;
	step = 1;
	turn = 1;
	powerPlants = vector<PowerPlant> (43);
}

void Game::loader() {
	mapLoader myLoader;
	myLoader.Load(graph, numOfPlayer);
	//set Player's name

	for (int i = 0; i < numOfPlayer; i++) {
		cout << "Please enter the name of Player " << (i + 1) << " :" << endl;
		string name;
		cin >> name;
		players[i].setName(name);
	}

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



	//Initialize resources Market
	Resources *array_resource = new Resources[12];
	array_resource[0] = Resources(3, 0, 0, 0, 1);
	array_resource[1] = Resources(3, 0, 0, 0, 2);
	array_resource[2] = Resources(3, 3, 0, 0, 3);
	array_resource[3] = Resources(3, 3, 0, 0, 4);
	array_resource[4] = Resources(3, 3, 0, 0, 5);
	array_resource[5] = Resources(3, 3, 0, 0, 6);
	array_resource[6] = Resources(3, 3, 3, 0, 7);
	array_resource[7] = Resources(3, 3, 3, 0, 8);
	array_resource[8] = Resources(0, 0, 0, 0, 10);
	array_resource[9] = Resources(0, 0, 0, 0, 12);
	array_resource[10] = Resources(0, 0, 0, 1, 14);
	array_resource[11] = Resources(0, 0, 0, 1, 16);


}

void Game::phase1() {
	//give a random order in the first turn
	if (turn == 1) {
		shufflePlayers(players, numOfPlayer);
		for (int i = 0; i < numOfPlayer; i++) {
			//players[i].setNumOfCity(i);
			cout << players[i].getName() << endl;
			cout << players[i].toString() << endl;
			cout << endl;
		}
	}

	//
	cout << "------------------------------After shuffle------------------------------" << endl;
	PowerPlant::shuffle(powerPlants);
	/*for (int i = 0; i < powerPlants.size(); i++) {
		cout << powerPlants[i].toString() << endl;
	}*/
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


		//auction process
		auctionPhase(players, powerPlants, market, numOfPlayer,step,turn);


		cout << "Phase finish" << endl;
		cout << endl;

		//if no one buy card, delete the smallest one
		if (checkNoOneBuyCard(players, numOfPlayer)) {
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
		setPlayerOrder(players, numOfPlayer);
		cout << "New order of the players " << endl;
		for (int i = 0; i < numOfPlayer; i++) {
			cout << players[i].getName() << endl;
			cout << players[i].toString() << endl;
			cout << endl;
		}

		cout << "Moving to the next phase" << endl;
		//turn++;
		cout << endl;
	}
}
//
//void Game::phase3() {
//	for (int i = 0; i < numOfPlayer; i++) {
//	
//	
//	}
//}