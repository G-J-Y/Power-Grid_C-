#include "Game.h"

//default constructor
Game::Game() {};

Game::Game(int numOfPlayer) {
	players = new Player[numOfPlayer];
	this->numOfPlayer = numOfPlayer;
	step = 1;
	turn = 1;
	powerPlants = vector<PowerPlant> (43);
	//graph = new Graph(42); //if not initialize here, there's no address for graph
					   // myLoader.Load(graph, numOfPlayer) calls graph by reference, but graph has no address
}

void Game::loader() {
	//mapLoader myLoader;
	//myLoader.Load(graph, numOfPlayer);	


	//create game map
	cout << "Please input the name of the map file: \n";
	string fileName;
	cin >> fileName;
	ifstream inputStream;
	inputStream.open(fileName);

	if (inputStream.fail())
	{
		if (inputStream.fail())
		{
			cout << "Wrong format of map file!";
			exit(1);
		}
	}

	map<string, int> cityNameIDPair;
	int cityID = 0;
	string next;

	inputStream >> next; //read the first string in the file
	if (next != "[City]") //a map file should start with "[City]"
	{
		cout << "This is not a valid map file text!";
		exit(1);
	}

	//read the first part of the file (city name list)
	//stores them into map<string, int>
	while (!inputStream.eof()) {
		inputStream >> next;
		if (next == "[Edge]")
			break;
		//cout << next << endl;
		cityNameIDPair.insert(pair<string, int>(next, cityID));
		cityID++;  //after storing the last city, the city size still increment once
	}

	//read the second part of the text
	string firstCity;
	string secondCity;
	string distance;
	int intDistance;
	int size = cityID; //if there is 10 city, the cityID will be 10 now
	Graph gameMap(size);
	//gameMap = Graph(size);	
	createBaseCity(&gameMap, cityNameIDPair);
	printGraph(&gameMap);
	cout << "2222\n";
	/**/
	while (!inputStream.eof()) {
		inputStream >> firstCity >> secondCity >> distance;
		//cout << firstCity << " " << secondCity << " " << distance << endl;
		intDistance = std::stoi(distance); //cast string to int
		addEdge(&gameMap, firstCity, secondCity, intDistance, cityNameIDPair);
	}


	printGraph(&gameMap);

	if (isConnected(&gameMap))
		cout << "The original map is a connected graph.\n";
	else
		cout << "The original map is not a connected graph.\n";

	//Now will create a map for certain number of players
	//2 players -- 3 regions
	//3 players -- 3 regions
	//4 players -- 4 regions
	//5 players -- 5 regions
	//6 players -- 6 regions //in game rule it's 6 players -- 5 regions	
	//int numOfplayer;
	int numToRemove; //how many areas to be removed
	int areaToRemove; // which area to be removed
	//cout << "\nEnter the number of players (2-6): ";
	//cin >> numOfplayer;
	while (numOfPlayer < 2 || numOfPlayer > 6) {
		cout << "Must be a number from 2-6. Enter again: ";
		cin >> numOfPlayer;
	}

	switch (numOfPlayer) {
	case 2:
	case 3:
		numToRemove = 3;
		break;
	case 4:
		numToRemove = 2;
		break;
	case 5:
		numToRemove = 1;
		break;
	case 6:
		numToRemove = 0;
		break;
	}
	cout << "In this game, there will be " << numOfPlayer << " players.\n"
		<< "You need to choose " << numToRemove << " area(s) you don't want (1 - 6).\n";

	//Graph* copy;

	while (true) {
		graph = new Graph(gameMap);
		for (int i = 0; i < numToRemove; i++) {
			cout << "\nEnter the " << i << "th area you don't want: ";
			cin >> areaToRemove;
			removeArea(graph, areaToRemove);
		}

		cout << "\n----------------Map After Choosing Areas--------------------\n";
		printGraph(graph);

		int test = 0;
		for (int i = 0; i < graph->getSize(); i++) {
			if (graph->getArr()[i].getHead() == NULL)
				test++;
			else break;
		}



		cout << "The number of cities left in the map: " << graph->numOfCities() << endl;
		if (isConnected2(graph, test)) {
			cout << "\nAll areas in the map is connected. Game starts. Good Luck!!\n\n";
			break;
		}

		else {
			cout << "\nNot all areas in the map is connected!! \nPlease choose the area you don't want again. \n";
			delete graph;
		}
	}

	//tests whether the game map is created well. If yes, it should print the map
	cout << "\n----------------Printing game map in Game::loader--------------- \n";
	printGraph(graph);
	cout << "----------------Finish printing in Game::loader---------------- \n\n";


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
	for (size_t i = 0; i < market.size(); i++) {
		cout << market[i].toString() << endl;
	}
	cout << endl;



	//Initialize resources Market
	resources[0] = Resources(3, 0, 0, 0, 1);
	resources[1] = Resources(3, 0, 0, 0, 2);
	resources[2] = Resources(3, 3, 0, 0, 3);
	resources[3] = Resources(3, 3, 0, 0, 4);
	resources[4] = Resources(3, 3, 0, 0, 5);
	resources[5] = Resources(3, 3, 0, 0, 6);
	resources[6] = Resources(3, 3, 3, 0, 7);
	resources[7] = Resources(3, 3, 3, 0, 8);
	resources[8] = Resources(0, 0, 0, 0, 10);
	resources[9] = Resources(0, 0, 0, 0, 12);
	resources[10] = Resources(0, 0, 0, 1, 14);
	resources[11] = Resources(0, 0, 0, 1, 16);


}

void Game::phase1() {
	cout << "\n----------------Printing game map in Game::phase1--------------- \n";
	printGraph(graph);
	cout << "----------------Finish printing in Game::phase1---------------- \n\n";
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
		for (size_t i = 0; i < powerPlants.size(); i++) {
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
		for (size_t i = 0; i < powerPlants.size(); i++) {
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
			for (size_t i = 0; i < market.size(); i++) {
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

void Game::phase3() {


	std::cout << "[INFO] PHASE3: Buying Resources" << std::endl;
	for (int i = numOfPlayer - 1; i >= 0; i--) {
		std::cout << "[INFO] " << players[i].getName() << ", it's your turn now!" << std::endl;
		std::cout << players[i].toString();
		std::cout << std::endl;

		std::cout << "[INFO] Here is the Resource Market:" << std::endl;


		for (int i = 0; i < 12; i++) {
			std::cout << resources[i].toString() << std::endl;
		}

		buyResources(i, players, resources);

	}
}


bool goToStep3 = false;
void Game::phase4() {
	std::cout << "[INFO] PHASE4: Building" << std::endl;

	for (int i = numOfPlayer - 1; i >= 0; i--)
	{
		std::cout << std::endl;
		printGraph(graph);

		building(step, numOfPlayer, players, i, graph, powerPlants, market);

		printGraph(graph);
	}
	if (goToStep3) {
		step = 3;
	}
}

void Game::phase5(){
    //phase 5 begins
    cout << "[INFO] PHASE5: Bureaucracy" << endl;
    earnCash(players, numOfPlayer);


    //print the resources in the market before re-supply
    cout << "[INFO] Here is the Resource Market:" << endl;
    for (int i = 0; i < 12; i++) {
        cout << resources[i].toString() << endl;
    }
    cout << "-----------------------------------------------" << endl;

    //re-supply the resource market
    reSupplyResource(step, numOfPlayer, resources);

    //print the resources after re-supply
    cout << "-----------------------------------------------" << endl;
    std::cout << "[INFO] Here is the Resource Market:" << std::endl;
    for (int i = 0; i < 12; i++) {
        cout << resources[i].toString() << endl;
    }


    //update the power plant market
    updateMarket(step, powerPlants, market);

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
    Player::printPlayerPossession(players, numOfPlayer);
}
