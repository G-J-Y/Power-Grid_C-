#pragma once
#include "Strategy.h"

/**
* A concrete Strategy that implements actions of an aggressive player
*/

class Aggressive : public Strategy {
public:
	void execute(PowerPlant& currentCard, int& currentPrice, 
		 vector<PowerPlant> market, int& numOfPlayerPass,
		int& playerLeft, int& indexOfCard, int money, string name);
};
