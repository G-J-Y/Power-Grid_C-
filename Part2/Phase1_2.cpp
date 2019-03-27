#include "Phase1_2.h"
#include <iostream>
using namespace std;

Phase1_2::Phase1_2() {
	//static variable
	 int currentAuctionPrice = 0;
	 int numberOfPlayers;
	 int turn = 2;
	 int step = 1;
	 int indexOfCard = NULL;
	 PowerPlant currentPowerPlant;
}
//in the first turn, the order of players is random
void Phase1_2::shufflePlayers(Player array[], int length) {
	int value;
	Player temp;

	if (array == NULL || length == 0)
		return;
	//change the random number
	srand((unsigned)time(NULL));
	for (int i = 0; i < length; i++) {
		//create a random number
		value = rand() % length;
		//shuffle
		temp = array[i];
		array[i] = array[value];
		array[value] = temp;
	}

}

//set the order of the players
void Phase1_2::setPlayerOrder(Player p[], int n) {
	Player temp;
	int cardPrice1;
	int cardPrice2;
	for (int i = 1; i < n; i++) {
		for (int j = n - 1; j > i - 1; j--) {
			if (p[j].getNumOfCity() > p[j - 1].getNumOfCity()) {
				temp = p[j];
				p[j] = p[j - 1];
				p[j - 1] = temp;
			}
			else if (p[j].getNumOfCity() == p[j - 1].getNumOfCity()) {
				cardPrice1 = p[j].getPowerPlant(0).getNumber();
				cardPrice2 = p[j - 1].getPowerPlant(0).getNumber();
				//need to create a method that set the powerPlant cards from big to small
				if (cardPrice1 > cardPrice2) {
					temp = p[j];
					p[j] = p[j - 1];
					p[j - 1] = temp;
				}
			}
		}
	}
}

//every time a new card put into the market, set a new order
void Phase1_2::setMarketOrder(vector<PowerPlant> &p) {
	PowerPlant temp;
	int cardPrice1;
	int cardPrice2;
	for (int i = 1; i < p.size(); i++) {
		for (int j = p.size() - 1; j > i - 1; j--) {
			if (p[j].getNumber() < p[j - 1].getNumber()) {
				temp = p[j];
				p[j] = p[j - 1];
				p[j - 1] = temp;
			}

		}
	}
}

//every time players buy a new card, set the order of card owned by player
void Phase1_2::setCardOwnedByPlayer(Player &p) {
	PowerPlant big;
	PowerPlant small;

	for (int i = 1; i < p.getNumOfPowerPlant(); i++) {
		for (int j = p.getNumOfPowerPlant() - 1; j > i - 1; j--) {
			if (p.getPowerPlant(j).getNumber() > p.getPowerPlant(j - 1).getNumber()) {
				big = p.getPowerPlant(j);
				small = p.getPowerPlant(j - 1);
				p.setPowerPlant(big, j - 1);
				p.setPowerPlant(small, j);
			}

		}
	}
}

//return excess resources
void Phase1_2::checkReturnResources(Player &p) {
	int coal_max = 0;
	int oil_max = 0;
	int garbage_max = 0;
	int uranium_max = 0;
	int hybrid_max = 0;
	bool isHybrid = false;
	//calculate the total amount of each resource
	for (int i = 0; i < p.getNumOfPowerPlant(); i++) {
		if (p.getPowerPlant(i).getTypeName() == "coal") {
			coal_max += p.getPowerPlant(i).getNeed() * 2;
		}
		if (p.getPowerPlant(i).getTypeName() == "oil") {
			oil_max += p.getPowerPlant(i).getNeed() * 2;
		}
		if (p.getPowerPlant(i).getTypeName() == "garbage") {
			garbage_max += p.getPowerPlant(i).getNeed() * 2;
		}
		if (p.getPowerPlant(i).getTypeName() == "uranium") {
			uranium_max += p.getPowerPlant(i).getNeed() * 2;
		}
		if (p.getPowerPlant(i).getTypeName() == "hybrid") {
			isHybrid = true;
			hybrid_max += p.getPowerPlant(i).getNeed() * 2;
		}
	}
	int coalOilHybrid_max = coal_max + oil_max + hybrid_max;
	//calculate the maximum resources a player can hold
	int coal_player = p.getCoalNum();
	int oil_player = p.getOilNum();
	int garbage_player = p.getGarbageNum();
	int uranium_player = p.getUraniumNum();
	int coalOilHybrid_player = coal_player + oil_player;

	if (isHybrid == true) {
		int excess_coal = coal_player - coal_max;
		int excess_oil = oil_player - oil_max;
		if (excess_coal + excess_oil > hybrid_max) {
			if (excess_coal > 0 && excess_oil <= 0) {
				if (coal_player - (coal_max + hybrid_max > 0)) {
					cout << "Excess and return " << coal_player - (coal_max + hybrid_max) << " coal" << endl;
					p.setCoalNum(coal_max);
				}

			}
			else if (excess_oil > 0 && excess_coal <= 0) {
				if (oil_player - (oil_max + hybrid_max) > 0) {
					cout << "Excess and return " << oil_player - (oil_max + hybrid_max) << " oil" << endl;
					p.setOilNum(oil_max);
				}
			}
			else {                                                      //excess_coal > 0 && excess_oil > 0
				int keep;
				int leftHybridSpace;
				cout << "Excess " << excess_coal << " coal, and you have " << hybrid_max << " hybrid space" << endl;
				cout << "The coal resources do you want to put in hybrid: ";
				cin >> keep;
				while (keep < 0 || keep > hybrid_max) {
					cout << "The number you enter is exceed, please enter a valid number: ";
					cin >> keep;
				}
				cout << "Excess and return " << excess_coal - keep << " coal" << endl;
				p.setCoalNum(coal_max + keep);
				leftHybridSpace = hybrid_max - keep;
				if (excess_oil - leftHybridSpace > 0) {
					cout << "Excess and return " << excess_oil - leftHybridSpace << " coal" << endl;
					p.setOilNum(oil_max + leftHybridSpace);
				}
			}
			if (garbage_player > garbage_max) {
				cout << "Excess and return " << garbage_player - garbage_max << " garbage" << endl;
				p.setGarbageNum(garbage_max);
			}
			if (uranium_player > uranium_max) {
				cout << "Excess and return " << uranium_player - uranium_max << " uranium" << endl;
				p.setUraniumNum(uranium_max);
			}
		}
	}
	else {
		if (coal_player > coal_max) {
			cout << "Excess and return " << coal_player - coal_max << " coal" << endl;
			p.setCoalNum(coal_max);
		}
		if (oil_player > oil_max) {
			cout << "Excess and return " << oil_player - oil_max << " oil" << endl;
			p.setOilNum(oil_max);
		}
		if (garbage_player > garbage_max) {
			cout << "Excess and return " << garbage_player - garbage_max << " garbage" << endl;
			p.setGarbageNum(garbage_max);
		}
		if (uranium_player > uranium_max) {
			cout << "Excess and return " << uranium_player - uranium_max << " uranium" << endl;
			p.setUraniumNum(uranium_max);
		}
	}

}

//check if the cards owned by players over 4
void Phase1_2::buyCard(Player &p, PowerPlant card) {
	int num = p.getNumOfPowerPlant();

	if (num >= 3) {
		int cardNumber;
		bool success = false;
		cout << p.getName() << ", The maximum number of cards of players is 3, now you own: " << endl;
		for (int i = 0; i < num; i++) {
			cout << p.getPowerPlant(i).toString() << endl;
		}
		cout << endl;
		cout << "The new card you bought: " << endl;
		cout << card.toString() << endl;
		cout << endl;
		cout << "Please enter the number of the card you want to switch: ";
		cin >> cardNumber;
		do {
			for (int j = 0; j < num; j++) {
				if (p.getPowerPlant(j).getNumber() == cardNumber) {
					success = true;

					//switch
					p.setPowerPlant(card, j);
					setCardOwnedByPlayer(p);
					cout << "Success! Now you own: " << endl;
					p.setMoney(p.getMoney() - card.getNumber());

					//print
					for (int i = 0; i < num; i++) {
						cout << p.getPowerPlant(i).toString() << endl;
					}
					cout << endl;

					//check resouces method
					checkReturnResources(p);
					cout << endl;
				}
			}
			if (success == false) {
				cout << "You don't have this card please enter a correct number: ";
				cin >> cardNumber;
			}
		} while (success == false);


	}
	else {
		p.setPowerPlant(card, num);
		p.setBought(true);
		p.setMoney(p.getMoney() - card.getNumber());
		num = num + 1;
		p.setNumOfPowerPlant(num);
	}

}

//check if no one buy card in this turn
bool Phase1_2::checkNoOneBuyCard(Player p[]) {
	int numOfPassRound = 0;
	for (int i = 0; i < numberOfPlayers; i++) {
		if (p[i].getRoundStatus() == false) {
			numOfPassRound++;
		}
	}
	if (numOfPassRound == numberOfPlayers) {
		return true;
	}
	else {
		return false;
	}
}

//if draw step3 card
void Phase1_2::changeMarketToStep3(vector<PowerPlant> &p) {
	p.pop_back();
	p.erase(p.begin());
}

//check if a player can buy a card
void Phase1_2::abilityOfPurchase(vector<PowerPlant> m, int c) {
	if (step == 3) {
		for (int i = 0; i < m.size(); i++) {
			if (m[i].getNumber() == c) {
				currentPowerPlant = m[i];
				indexOfCard = i;
			}
		}
		while (currentPowerPlant.getNumber() == 0)
		{
			int choice;
			cout << "You cannot buy this card, please enter a new number: ";
			cin >> choice;
			for (int i = 0; i < m.size(); i++) {
				if (m[i].getNumber() == choice) {
					currentPowerPlant = m[i];
					indexOfCard = i;
				}
			}
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			if (m[i].getNumber() == c) {
				currentPowerPlant = m[i];
				indexOfCard = i;
			}
		}
		while (currentPowerPlant.getNumber() == 0)
		{
			int choice;
			cout << "You cannot buy this card, please enter a new number: ";
			cin >> choice;
			for (int i = 0; i < 4; i++) {
				if (m[i].getNumber() == choice) {
					currentPowerPlant = m[i];
					indexOfCard = i;
				}
			}
		}
	}
}

//this method set the status of the player to "pass"
void Phase1_2::pass(Player &p) {
	p.setAuction(false);
}

//this method set the price when in the auction process
void Phase1_2::auction(Player &p, PowerPlant n) {
	//currentAuctionPrice;
	int price;
	cout << "Please enter the price you auction: ";
	cin >> price;
	if (price > p.getMoney()) {
		do {
			cout << "You don't have enough money " << endl;
			cout << "Enter another price" << endl;
			cout << "Enter 0 to pass" << endl;
			cin >> price;
			if (price == 0) {
				pass(p);
				break;
			}
		} while (price > p.getMoney());
	}
	else if (currentAuctionPrice == 0) {
		if (price < n.getNumber()) {
			do {
				cout << "The price is cheaper than current price" << endl;
				cout << "Enter another price" << endl;
				cout << "Enter 0 to pass" << endl;
				cin >> price;
				if (price == 0) {
					pass(p);
					break;
				}
			} while (price < currentAuctionPrice);
		}
	}
	else if (currentAuctionPrice != 0) {
		if (price <= currentAuctionPrice) {
			//the first person can give == card price but second cannot
			do {
				cout << "The price should higher than current price" << endl;
				cout << "Enter another price" << endl;
				cout << "Enter 0 to pass" << endl;
				cin >> price;
				if (price == 0) {
					pass(p);
					break;
				}
			} while (price <= currentAuctionPrice);
		}
	}

	cout << endl;

	if (price != 0) {
		currentAuctionPrice = price;
		cout << "The current price is: " << currentAuctionPrice << endl;
		cout << endl;
		p.setPrice(price);
	}

}