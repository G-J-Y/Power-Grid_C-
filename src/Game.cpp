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

void Game::phase4() {
	std::cout << "[INFO] PHASE4: Building" << std::endl;
	bool goToStep3 = false;
	for (int i = numOfPlayer - 1; i >= 0; i--)
	{
		std::cout << std::endl;
		printGraph(graph);
		std::cout << "[INFO]" << players[i].getName() << ", it's your turn!" << std::endl;
		while (true)
		{

			//check the step
			if (numOfPlayer == 2) {
				if (players[i].getNumOfCity() == 10) {
					if (step == 1) {
						step = 2;
						goToStep3 = adjustMarket(step, market, powerPlants);
					}
				}
			}
			if (numOfPlayer == 3 || numOfPlayer == 4 || numOfPlayer == 5) {
				if (players[i].getNumOfCity() == 7) {
					if (step == 1) {
						step = 2;
						goToStep3 = adjustMarket(step, market, powerPlants);
					}
				}
			}
			if (numOfPlayer == 6) {
				if (players[i].getNumOfCity() == 6) {
					if (step == 1) {
						step = 2;
						goToStep3 = adjustMarket(step, market, powerPlants);
					}
				}
			}

			std::cout << "[PROMPT]" << "Please enter the ID of the city that you want to build.(Enter -1 to skip)" << std::endl;
			std::cout << "[ENTER] ";
			int inputNum;
			std::cin >> inputNum;
			std::cout << std::endl;

			if (inputNum == -1) {
				break;
			}

			vector<string> owners = graph->getArr()[inputNum].getBase()->getOwners();
			size_t size = owners.size();


			//check if the city is on the map
			if (graph->getArr()[inputNum].getHead() == NULL) {
				cout << "[ERROR] This city is not on the map. Please try another city!!\n";
				continue;
			}

			//check if the player have already built one
			bool isBuilt = false;
			for (size_t j = 0; j < size; j++) {
				if (players[j].getName() == owners[j]) {
					cout << "[ERROR] You have owned this city. Please try another city!!\n";
					isBuilt = true;
					continue;
				}
			}
			if (isBuilt) { continue; }

			//check if there is enough space
			if (size >= (size_t)step) {
				std::cout << "[ERROR] You can not build plant in this city because there is no more space!" << std::endl;
				continue;
			}

			//check if player has enough money
			int price = graph->getArr()[inputNum].getBase()->getPrice(size);
			//add network price
			price += graph->lowestPathPrice(inputNum, players[i].getName());
			if (players[i].getMoney() < price) {
				std::cout << "[ERROR] You do not have enough money. Please try another city!" << std::endl;
				continue;
			}

			graph->getArr()[inputNum].getBase()->addOwner(players[i].getName());
			players[i].setMoney(players[i].getMoney() - price);
			players[i].setNumOfCity(players[i].getNumOfCity() + 1);
			std::cout << "[SUCCESS] You have built a house in " << graph->getArr()[inputNum].getBase()->getName() << " successfully." << std::endl;
			std::cout << "[SUCCESS] It cost you  " << price << " Elektro. Now you have " << players[i].getMoney() << " Elektro." << std::endl;

		}
		printGraph(graph);
	}
	if (goToStep3) {
		step = 3;
	}
}

void Game::phase5(){
    //phase 5 begins

	Resources recycle;
    cout << "[INFO] PHASE5: Bureaucracy" << endl;
    earnCash(recycle);


    //print the resources in the market before re-supply
    cout << "[INFO] Here is the Resource Market:" << endl;
    for (int i = 0; i < 12; i++) {
        cout << resources[i].toString() << endl;
    }
    cout << "-----------------------------------------------" << endl;

    //re-supply the resource market
    reSupplyResource(recycle);

    //print the resources after re-supply
    cout << "-----------------------------------------------" << endl;
    std::cout << "[INFO] Here is the Resource Market:" << std::endl;
    for (int i = 0; i < 12; i++) {
        cout << resources[i].toString() << endl;
    }


    //update the power plant market
    updateMarket();

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













//every player indicates how many cities in his network he wishes
//(and is able) to supply with electricity. He earns cash based on the number of cities
//he powers as shown on the payment table
void Game::earnCash(Resources recycle) {
	int payment[21] = {10, 22, 33, 44, 54, 64, 73, 82, 90, 98, 105, 112, 118, 124, 129, 134, 138, 142, 145, 148, 150};     //payment corresponding to the number of powered cities
    string yesInput;
    int earnedCash, money;
    for (int i = 0; i < numOfPlayer; i++) {
        int numOfPowerPlant = players[i].getNumOfPowerPlant();
        int totalNumInput=0;
        for (int j = 0; j < numOfPowerPlant; j++) {
            PowerPlant currentPlant = players[i].getPowerPlant(j);
            cout << "[PROMPT] Player " << (i + 1)
                 << ": Do you wish to supply cities with electricity by using power plant "
                 << currentPlant.getNumber() << " ?" << endl;
            do {
                cin >> yesInput;
                if (yesInput == "Y" || yesInput == "y") {
                    if (validUsingPowerPlant(i, currentPlant, recycle)) {
                        totalNumInput += currentPlant.getSupplyCity();
                        break;
                    }
                } else
                    break;
            } while (true);

            if (totalNumInput > players[i].getNumOfCity())
                totalNumInput = players[i].getNumOfCity();
        }

        players[i].addNumOfPoweredCities(totalNumInput);

        earnedCash = payment[totalNumInput];
        money = players[i].getMoney() + earnedCash;
        players[i].setMoney(money);
        cout << "[SUCCESS] You have supplied " << totalNumInput << " city/cities this round." << endl;
        cout << "[INFO] You have earned "<< earnedCash<< " this round."<< endl;
        cout << "[INFO] Now you have "<<players[i].getNumOfPoweredCities()<<" city/cities that have been powered.\n"<< endl;
    }
}

//return true if the input is valid for the number of cities the player wants to power
bool Game::validUsingPowerPlant(int i, PowerPlant currentPlant, Resources recycle) {
    PowerPlant::Type type = currentPlant.getType();
    int needNum = currentPlant.getNeed();
    if (type == PowerPlant::hybrid) {
        int numCoalHybrid, numOilHybrid;
        do {
            do{
                cout << "\n[PROMPT] Please enter the coal that you want to use to power the power plant:" << endl;
                cout << "-> ";
                if(!cin){
                    cout << "[ERROR] Invalid input";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }while(!(cin >> numCoalHybrid));

            do{
                cout << "\n[PROMPT] Please enter the oil that you want to use to power the power plant:" << endl;
                cout << "-> ";
                if(!cin){
                    cout << "[ERROR] Invalid input";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }while(!(cin >> numOilHybrid));
        } while (numCoalHybrid + numOilHybrid != currentPlant.getNeed());
        recycle.addCoal(numCoalHybrid);
        players[i].deCoalNum(numCoalHybrid);
        recycle.addOil(numOilHybrid);
        players[i].deOilNum(numOilHybrid);
    }
    switch (type) {
        case PowerPlant::coal:
            if (players[i].getCoalNum() >= needNum) {
                recycle.addCoal(needNum);
                players[i].deCoalNum(needNum);
                return true;
            } else
                cout << "[ERROR] You can not power cities by using power plant "<< currentPlant.getNumber()<<
                     " because you do not have enough coals." << endl;
            return false;
        case PowerPlant::oil:
            if (players[i].getOilNum() >= currentPlant.getNeed()) {
                recycle.addOil(needNum);
                players[i].deOilNum(needNum);
                return true;
            } else
                cout << "[ERROR] You can not power cities by using power plant "<< currentPlant.getNumber()<<
                     " because you do not have enough oil." << endl;
            return false;
        case PowerPlant::garbage:
            if (players[i].getGarbageNum() >= currentPlant.getNeed()) {
                recycle.addGarbage(needNum);
                players[i].deGarbageNum(needNum);
                return true;
            } else
                cout << "[ERROR] You can not power cities by using power plant "<< currentPlant.getNumber()<<
                     " because you do not have enough garbage." << endl;
            return false;
        case PowerPlant::uranium:
            if (players[i].getUraniumNum() >= currentPlant.getNeed()) {
                recycle.addUranium(needNum);
                players[i].deUraniumNum(needNum);
                return true;
            } else
                cout << "[ERROR] You can not power cities by using power plant "<< currentPlant.getNumber()<<
                     " because you do not have enough uranium." << endl;
            return false;
        default:
            return true;
    }
}


void Game::reSupplyResource(Resources recycle) {

    //Based on the number of players and the step of the game, the players re-supply the resource market (see table at the back of the rules) from the supply of resources
    Resources table;
    switch (numOfPlayer) {
        case 2:
            switch (step) {
                case 1:
                    table = Resources(3, 2, 1, 1, 0);
                    break;
                case 2:
                    table = Resources(4, 2, 2, 1, 0);
                    break;
                case 3:
                    table = Resources(3, 4, 3, 1, 0);
                    break;
            }
            break;
        case 3:
            switch (step) {
                case 1:
                    table = Resources(4, 2, 1, 1, 0);
                    break;
                case 2:
                    table = Resources(5, 3, 2, 1, 0);
                    break;
                case 3:
                    table = Resources(3, 4, 3, 1, 0);
                    break;
            }
            break;
        case 4:
            switch (step) {
                case 1:
                    table = Resources(5, 3, 2, 1, 0);
                    break;
                case 2:
                    table = Resources(6, 4, 3, 2, 0);
                    break;
                case 3:
                    table = Resources(4, 5, 4, 2, 0);
                    break;
            }
            break;
        case 5:
            switch (step) {
                case 1:
                    table = Resources(5, 4, 3, 2, 0);
                    break;
                case 2:
                    table = Resources(7, 5, 3, 3, 0);
                    break;
                case 3:
                    table = Resources(5, 6, 5, 2, 0);
                    break;
            }
            break;
        case 6:
            switch (step) {
                case 1:
                    table = Resources(7, 5, 3, 2, 0);
                    break;
                case 2:
                    table = Resources(9, 6, 5, 3, 0);
                    break;
                case 3:
                    table = Resources(6, 7, 6, 3, 0);
                    break;
            }
            break;
    }


    //change the number of resources that will be supplied according to the available in the game
    // (if the players store too many resources in their power plants, the resource is not fully re-supplied! The resource tokens in the game are limited.)
    Resources toSupply;
    if (recycle.getCoal() >= table.getCoal()) {
        recycle.setCoal(recycle.getCoal() - table.getCoal());
        toSupply.setCoal(table.getCoal());
    } else {
        toSupply.setCoal(recycle.getCoal());
        recycle.setCoal(0);
    }

    if (recycle.getOil() >= table.getOil()) {
        recycle.setOil(recycle.getOil() - table.getOil());
        toSupply.setOil(table.getOil());
    } else {
        toSupply.setOil(recycle.getOil());
        recycle.setOil(0);
    }

    if (recycle.getGarbage() >= table.getGarbage()) {
        recycle.setGarbage(recycle.getGarbage() - table.getGarbage());
        toSupply.setGarbage(table.getGarbage());
    } else {
        toSupply.setGarbage(recycle.getGarbage());
        recycle.setGarbage(0);
    }

    if (recycle.getUranium() >= table.getUranium()) {
        recycle.setUranium(recycle.getUranium() - table.getUranium());
        toSupply.setUranium(table.getUranium());
    } else {
        toSupply.setUranium(recycle.getUranium());
        recycle.setUranium(0);
    }

    //print the resources that will be supplied to the market
    int numOfCoalToSupply = toSupply.getCoal();
    int numOfOilToSupply = toSupply.getOil();
    int numOfGarbageToSupply = toSupply.getGarbage();
    int numOfUraniumToSupply = toSupply.getUranium();
    cout << "[INFO] To be re-supplied in step " << step << " for coal: " << numOfCoalToSupply << endl;
    cout << "[INFO] To be re-supplied in step " << step << " for oil: " << numOfOilToSupply << endl;
    cout << "[INFO] To be re-supplied in step " << step << " for garbage: " << numOfGarbageToSupply << endl;
    cout << "[INFO] To be re-supplied in step " << step << " for uranium: " << numOfUraniumToSupply << endl;

    //re-supply the uranium
    for (int i = 11; i >= 0; i--) {
        if (numOfUraniumToSupply > 0) {
            if (resources[i].getUranium() == 1)
                continue;
            else {
                if (resources[i].getUranium() == 0) {
                    resources[i].setUranium(1);
                    numOfUraniumToSupply--;
                }
            }
        }
    }


    for (int i = 7; i >= 0; i--) {
        //re-supply the coal
        if (numOfCoalToSupply > 0) {
            switch (resources[i].getCoal()) {
                case 3:
                    break;
                case 2: {
                    numOfCoalToSupply--;
                    resources[i].setCoal(3);
                    break;
                }
                case 1: {
                    int spaceCoalTemp = numOfCoalToSupply - 2;
                    if (spaceCoalTemp >= 0) {
                        resources[i].setCoal(3);
                        numOfCoalToSupply -= 2;
                    } else {
                        resources[i].setCoal(2);
                        numOfCoalToSupply--;
                    }
                    break;
                }
                case 0: {
                    int spaceCoalTemp = numOfCoalToSupply - 3;
                    if (spaceCoalTemp >= 0) {
                        resources[i].setCoal(3);
                        numOfCoalToSupply -= 3;
                    } else {
                        resources[i].setCoal(numOfCoalToSupply);
                        numOfCoalToSupply = 0;
                    }
                    break;
                }
            }
        }

        //re-supply the oil
        if (numOfOilToSupply > 0) {
            switch (resources[i].getOil()) {
                case 3:
                    break;
                case 2: {
                    numOfOilToSupply--;
                    resources[i].setOil(3);
                    break;
                }
                case 1: {
                    int spaceOilTemp = numOfOilToSupply - 2;
                    if (spaceOilTemp >= 0) {
                        resources[i].setOil(3);
                        numOfOilToSupply -= 2;
                    } else {
                        resources[i].setOil(2);
                        numOfOilToSupply--;
                    }
                    break;
                }
                case 0: {
                    int spaceOilTemp = numOfOilToSupply - 3;
                    if (spaceOilTemp >= 0) {
                        resources[i].setOil(3);
                        numOfOilToSupply -= 3;
                    } else {
                        resources[i].setOil(numOfOilToSupply);
                        numOfOilToSupply = 0;
                    }
                    break;
                }
            }
        }

        //re-supply the garbage
        if (numOfGarbageToSupply > 0) {
            switch (resources[i].getGarbage()) {
                case 3:
                    break;
                case 2: {
                    numOfGarbageToSupply--;
                    resources[i].setGarbage(3);
                    break;
                }
                case 1: {
                    int spaceGarbageTemp = numOfGarbageToSupply - 2;
                    if (spaceGarbageTemp >= 0) {
                        resources[i].setGarbage(3);
                        numOfGarbageToSupply -= 2;
                    } else {
                        resources[i].setGarbage(2);
                        numOfGarbageToSupply--;
                    }
                    break;
                }
                case 0: {
                    int spaceGarbageTemp = numOfGarbageToSupply - 3;
                    if (spaceGarbageTemp >= 0) {
                        resources[i].setGarbage(3);
                        numOfGarbageToSupply -= 3;
                    } else {
                        resources[i].setGarbage(numOfGarbageToSupply);
                        numOfGarbageToSupply = 0;
                    }
                    break;
                }
            }
        }


    }
}

//Place the highest numbered power plant from the future market face down under the draw stack and draw a new one to replace it
void Game::updateMarket() {
    //If the »Step 3« card is drawn in phase 5 (Bureaucracy),
    //remove this card and the lowest numbered power plant from the game and do not draw replacements
    PowerPlant theFirstInDrawStack = powerPlants.front();
    if (theFirstInDrawStack.getTypeName() == "step3") {
        cout <<"[INFO] It is STEP 3 Card !!" <<endl;
        market.erase(market.begin());
        PowerPlant::setMarketOrder(market);
        powerPlants.erase(powerPlants.begin());
        step = 3;
        PowerPlant::shuffle(powerPlants);
    }
    else {
        PowerPlant theHighest = market.back();
        market.pop_back();
        market.push_back(powerPlants.front());
        powerPlants.push_back(theHighest);
        powerPlants.erase(powerPlants.begin());
    }
}

