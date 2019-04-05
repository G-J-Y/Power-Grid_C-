#pragma once
#include "mapLoader.h"
#include "Player.h"
#include "Resources.h"
#include "Phase1_2.h"
#include "Phase3_4.h"
//#include "Phase5.h"

class Game {
private:
	int step;
	int turn;
	int numOfPlayer;
	Player* players;
	Resources resources[12];
	House house[132];
	vector<PowerPlant> powerPlants;
	vector<PowerPlant> market;
	Graph* graph;




//phase5
	void earnCash(Resources);                    //the players earn cash
	bool validUsingPowerPlant(int, PowerPlant, Resources);    //return true if the input is valid for the number of cities the player wants to power
	void reSupplyResource(Resources);  //Based on the number of players and the step of the game, the players re-supply the resource market from the supply of resources.
	void updateMarket();//Place the highest numbered power plant from the future market face down under the draw stack and draw a new one to replace it. Rearrange the market appropriately.



public:
	Game();
	Game(int numOfPlayer);
	
	void loader();
	void phase1();
	void phase2();
	void phase3();
	void phase4();
	void phase5();



};