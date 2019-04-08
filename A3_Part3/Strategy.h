#pragma once

#include "PowerPlant.h"


/**
* The classes that implement a concrete strategy should inherit this.
* The Player class uses this to use a concrete strategy.
*/


class Strategy {
public:
	/**
	* Method whose implementation varies depending on the strategy adopted.
	*/
	
	virtual void execute(PowerPlant& currentCard, int& currentPrice,
		 vector<PowerPlant> market, int& numOfPlayerPass,
		int& playerLeft, int& indexOfCard, int money, string name) = 0;
};