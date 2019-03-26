#include <iostream>
#include <vector>
#include "player.h"
#include "Resources.h"
#include "mapLoader.h"


int main1() {
	//create testing player
	int numOfPlayer = 2;
	Player players[2];
	players[0].setName("Allen");
	players[1].setName("Bob");
	//players[2].setName("Cara");
	//players[3].setName("David");

	//Initialize the map for demo
	Graph myGameMap(7);

	map<string, int> cityNameIDPair;
	cityNameIDPair.insert(pair<string, int>("Boston", 0));
	cityNameIDPair.insert(pair<string, int>("New York", 1));
	cityNameIDPair.insert(pair<string, int>("Philadelphia", 2));
	cityNameIDPair.insert(pair<string, int>("Washington DC", 3));
	cityNameIDPair.insert(pair<string, int>("Pittsburgh", 4));
	cityNameIDPair.insert(pair<string, int>("Detroit", 5));
	cityNameIDPair.insert(pair<string, int>("Buffalo", 6));

	createBaseCity(&myGameMap, cityNameIDPair);

	addEdge(&myGameMap, "Boston", "New York", 3, cityNameIDPair);
	addEdge(&myGameMap, "New York", "Philadelphia", 0, cityNameIDPair);
	addEdge(&myGameMap, "Philadelphia", "Washington DC", 3, cityNameIDPair);
	addEdge(&myGameMap, "Washington DC", "Pittsburgh", 6, cityNameIDPair);
	addEdge(&myGameMap, "Pittsburgh", "Detroit", 6, cityNameIDPair);
	addEdge(&myGameMap, "Detroit", "Buffalo", 7, cityNameIDPair);
	addEdge(&myGameMap, "Buffalo", "Pittsburgh", 7, cityNameIDPair);
	addEdge(&myGameMap, "Buffalo", "New York", 8, cityNameIDPair);


	//Initialize resources on the map
	//Resources(int c, int o, int g, int u, int p);
	Resources *array_resource = new Resources[12];
	array_resource[0] = Resources(0, 0, 0, 0, 1);
	array_resource[1] = Resources(3, 0, 0, 0, 2);
	array_resource[2] = Resources(3, 1, 0, 0, 3);
	array_resource[3] = Resources(3, 3, 0, 0, 4);
	array_resource[4] = Resources(3, 3, 0, 0, 5);
	array_resource[5] = Resources(0, 3, 0, 0, 6);
	array_resource[6] = Resources(0, 3, 2, 0, 7);
	array_resource[7] = Resources(0, 3, 3, 0, 8);
	array_resource[8] = Resources(0, 0, 0, 0, 10);
	array_resource[9] = Resources(0, 0, 0, 0, 12);
	array_resource[10] = Resources(0, 0, 0, 0, 14);
	array_resource[11] = Resources(6, 0, 0, 0, 16);


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


	//Assume Player 1 has 150 Elektro PowerPlants 5,6,9

	players[0].setPowerPlant(powerPlants[5], 0);
	players[0].setPowerPlant(powerPlants[6], 1);
	players[0].setPowerPlant(powerPlants[9], 2);
	players[0].setNumOfPowerPlant(3);
	players[0].setMoney(50);

	//Assume Player 1 has 100 Elektro PowerPlants 20,21,26
	players[1].setPowerPlant(powerPlants[20], 0);
	players[1].setPowerPlant(powerPlants[21], 1);
	players[1].setPowerPlant(powerPlants[26], 2);
	players[1].setNumOfPowerPlant(3);
	players[1].setMoney(100);

	//Initialization finshed!


	//======================================================================
	std::cout << "[INFO] PHASE3: Buying Resources" << std::endl;

	//buy resources
	for (int i = numOfPlayer-1; i >= 0; i--) {
		players[i].buyResources(array_resource);
	}

	//======================================================================
	std::cout << "[INFO] PHASE4: Building" << std::endl;

	//build city

	int step = 1;
	for (int i = numOfPlayer-1; i >= 0; i--) {
		players[i].building(&myGameMap,step,6);
	}

	for(int i = 0; i<numOfPlayer;i++){
		players[i].toString();
	}

	delete[] array_resource;
	system("pause");
	return 0;
}