#ifndef PHASE1_2_H_
#define PHASE1_2_H_
#include "Resources.h"
#include "PowerPlant.h"
#include "Player.h"
#include <time.h>
#include <vector>
#include <iostream>

class Phase1_2 {
public:
	//static variable
	 int currentAuctionPrice;
	 int numberOfPlayers;
	 int turn;
	 int step;
	 int indexOfCard = NULL;
	 PowerPlant currentPowerPlant;

	Phase1_2();

	void shufflePlayers(Player array[], int length);
	void setPlayerOrder(Player p[], int n);
	void setMarketOrder(vector<PowerPlant> &p);
	void setCardOwnedByPlayer(Player &p);
	void checkReturnResources(Player &p);
	void buyCard(Player &p, PowerPlant card);
	bool checkNoOneBuyCard(Player p[]);
	void changeMarketToStep3(vector<PowerPlant> &p);
	void abilityOfPurchase(vector<PowerPlant> m, int c);
	void pass(Player &p);
	void auction(Player &p, PowerPlant n);
}


#endif // !PHASE1_2_H__H_
#pragma once