#pragma once
#include "mapLoader.h"
#include "Player.h"
#include "Resources.h"
#include "Phase1_2.h"
#include "Phase3_4.h"
#include "Phase5.h"

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