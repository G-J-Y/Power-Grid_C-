#include "House.h"
#include "SummaryCard.h"
#include "Money.h"
#include "Resources.h"
#include "PowerPlant.h"
#include "Player.h"
//#include "map.h"
#include "mapLoader.h"
#include <time.h>
#include <vector>
#include <iostream>
using namespace std;

//static variable
static int currentAuctionPrice = 0;
static int numberOfPlayers;
static int turn = 2;
static int step = 1;
static int indexOfCard = NULL;
static PowerPlant currentPowerPlant;

//in the first turn, the order of players is random
void shufflePlayers(Player array[], int length) {
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
void setPlayerOrder(Player p[], int n) {
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
void setMarketOrder(vector<PowerPlant> &p) {
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
void setCardOwnedByPlayer(Player &p) {
	PowerPlant big;
	PowerPlant small;
	
	for (int i = 1; i < p.getNumOfPowerPlant(); i++) {
		for (int j = p.getNumOfPowerPlant() - 1; j > i - 1; j--) {
			if (p.getPowerPlant(j).getNumber() > p.getPowerPlant(j - 1).getNumber()) {
				big = p.getPowerPlant(j);
				small = p.getPowerPlant(j - 1);
				p.setPowerPlant(big, j-1);
				p.setPowerPlant(small, j);
			}

		}
	}
}

//return excess resources
void checkReturnResources(Player &p) {
	int coal_max = 0;
	int oil_max = 0;
	int garbage_max = 0;
	int uranium_max = 0;
	int hybrid_max= 0;
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

	if (isHybrid==true) {
		int excess_coal = coal_player - coal_max;
		int excess_oil = oil_player - oil_max;
		if (excess_coal + excess_oil > hybrid_max) {
			if (excess_coal > 0 && excess_oil <= 0) {
				if (coal_player-(coal_max+hybrid_max > 0)) {
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
				cout << "The coal resources do you want to keep: ";
				cin >> keep;
				while (keep < 0 || keep > hybrid_max) {
					cout << "The number you enter is exceed, please enter a valid number: ";
					cin >> keep;
				}
				cout << "Excess and return " << excess_coal-keep << " coal" << endl;
				p.setCoalNum(coal_max+keep);
				leftHybridSpace = hybrid_max - keep;
				if (excess_oil - leftHybridSpace > 0) {
					cout << "Excess and return " << excess_oil - leftHybridSpace << " coal" << endl;
					p.setOilNum(oil_max+leftHybridSpace);
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
void buyCard(Player &p, PowerPlant card) {
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
		} while (success==false);

		
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
bool checkNoOneBuyCard(Player p[]) {
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
void changeMarketToStep3(vector<PowerPlant> &p) {
	p.pop_back();
	p.erase(p.begin());
}

//check if a player can buy a card
void abilityOfPurchase(vector<PowerPlant> m, int c) {
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
void pass(Player &p) {
	p.setAuction(false);
}

//this method set the price when in the auction process
void auction(Player &p, PowerPlant n) {
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




int main() {
	//Initialize how many players

	cout << "Please enter the number of the players: ";
	cin >> numberOfPlayers;
	cout << endl;
	Player *players = new Player[numberOfPlayers];

	//set a simple name for each player
	for (int i = 0; i < numberOfPlayers; i++) {
		string name = "Player" + to_string(i + 1);
		players[i].setName(name);
	}

	//Create power plant cards
		//int numberOfCards = 43;
	vector<PowerPlant> powerPlants(43);
	//PowerPlant *powerPlants = new PowerPlant[numberOfCards];

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
	powerPlants[42] = PowerPlant(99, 0, PowerPlant::step3, 0);

	//give a random order in the first turn
	if (turn == 1) {
		shufflePlayers(players, numberOfPlayers);
		for (int i = 0; i < numberOfPlayers; i++) {
			//players[i].setNumOfCity(i);
			cout << players[i].getName() << endl;
			cout << players[i].toString() << endl;
			cout << endl;
		}
	}

	//*************************test check resources*************************
	//coal: 3
	players[0].setCoalNum(3);
	players[0].setPowerPlant(powerPlants[12], 0);
	//oil: 3
	players[0].setOilNum(3);
	players[0].setPowerPlant(powerPlants[13], 1);
	//uranium: 2
	players[0].setUraniumNum(2);
	players[0].setPowerPlant(powerPlants[14], 2);
	players[0].setNumOfPowerPlant(3);
	//change to garbage: 2
	buyCard(players[0], powerPlants[16]);

	//coal: 5
	players[1].setCoalNum(5);
	players[1].setPowerPlant(powerPlants[12], 0);
	//oil: 5
	players[1].setOilNum(5);
	players[1].setPowerPlant(powerPlants[13], 1);
	//hybrid: 2 (1 coal + 1 oil)
	players[1].setPowerPlant(powerPlants[9], 2);
	players[1].setNumOfPowerPlant(3);
	//change to garbage: 2
	buyCard(players[1], powerPlants[16]);
	//*************************test check resources*************************


	////***********************test set cards order in each players & test if a player have 4 cards*************************
	//for (int i = 0; i < numberOfPlayers; i++) {
	//	int numOfCards = players[i].getNumOfPowerPlant();
	//	while (numOfCards < 3) {
	//		players[i].setPowerPlant(powerPlants.front(), numOfCards);
	//		powerPlants.erase(powerPlants.begin());
	//		numOfCards++;
	//		players[i].setNumOfPowerPlant(numOfCards);
	//	}
	//	setCardOwnedByPlayer(players[i]);
	//}
	//for (int i = 0; i < numberOfPlayers; i++) {
	//	cout << players[i].getName() << endl;
	//	cout << players[i].toString() << endl;
	//	cout << endl;
	//}
	//cout << endl;
	//setPlayerOrder(players, numberOfPlayers);
	//cout << "New order of the players " << endl;
	//for (int i = 0; i < numberOfPlayers; i++) {
	//	cout << players[i].getName() << endl;
	//	cout << players[i].toString() << endl;
	//	cout << endl;
	//}
	//cout << endl;

	////test if a player have 4 cards
	//buyCard(players[0], powerPlants[20]);
	////***********************test set cards order in each players & test if a player have 4 cards*************************


	//Creat market area
		//create Market
	vector<PowerPlant> market(0);
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
	}

	//start the auction, status: pass(0) || auction(1)
	int status;

	//in the first turn, each players must buy one power plant
	if (turn == 1) {
		int playerLeft = numberOfPlayers;
		//PowerPlant currentPowerPlant;

		while (playerLeft > 1)
		{
			int choice;
			//int indexOfCard;

			// auction process
			int numOfPlayerPass = 0;
			while (numOfPlayerPass < playerLeft - 1)
			{
				for (int i = 0; i < numberOfPlayers; i++) {
					if (players[i].getNumOfPowerPlant() == 1) {
						pass(players[i]);

					}
					else {
						if (numOfPlayerPass >= playerLeft - 1) {
							break;
						}
						//cout << "Status:" << players[i].getAuction() << endl;
						if (players[i].getAuction() == true) {

							cout << players[i].getName() << endl;
							cout << "It's your turn" << endl;

							//who's turn right now
							/*cout << players[i].getName() << endl;
							cout << "It's your turn" << endl;*/
							cout << "Auction -> Enter: 1" << endl;
							cout << "Pass -> Enter: 0" << endl;
							cin >> status;
							cout << endl;

							while (status != 0 && status != 1)
							{
								cout << "Please enter a correct number" << endl;
								cout << "Auction -> Enter: 1" << endl;
								cout << "Pass -> Enter: 0" << endl;
								cin >> status;
							}
							//in the first turn, no player can pass the whole round, each player should buy a power plant card
							if (currentPowerPlant.getNumber() == 0 && status == 0) {
								do {
									cout << "This is the first turn, you cannot pass your round" << endl;
									cout << "Please enter 1 to start auction" << endl;
									cin >> status;
								} while (status !=1);
							}

							if (status == 0) {
								pass(players[i]);
								numOfPlayerPass++;
							}
							else {
								
								//if no card is auction
								if (currentPowerPlant.getNumber() == 0) {
									//choose a card to auction
									cout << "Enter the number of the card in the market to start auction: ";
									cin >> choice;

									//check if the card is exist
									abilityOfPurchase(market, choice);

								}

								if (numOfPlayerPass < playerLeft - 1) {
									auction(players[i], market[indexOfCard]);
									//cout <<"Price" <<players[i].getPrice() << endl;
								}

							}

						}

					}
				}
			}
			//the number of player who doesn't buy the card
			playerLeft--;
			//who buy this card
			for (int i = 0; i < numberOfPlayers; i++) {
				if (players[i].getAuction() == true && currentPowerPlant.getNumber()!=0) {
					int num = players[i].getNumOfPowerPlant();
					players[i].setPowerPlant(market[indexOfCard], num);
					players[i].setMoney(players[i].getMoney() - market[indexOfCard].getNumber());
					//print the information of the card
					cout << "Congratulation, " << players[i].getName() << endl;
					cout << "You get: " << endl;
					cout << currentPowerPlant.toString() << endl;
					cout << endl;

					num = players[i].getNumOfPowerPlant() + 1;
					players[i].setNumOfPowerPlant(num);

				}
			}

			//draw a new plant card, put it in the market and change the order
			market[indexOfCard] = powerPlants.front();
			powerPlants.erase(powerPlants.begin());
			setMarketOrder(market);

			//reset the status to true
			for (int i = 0; i < numberOfPlayers; i++) {
				players[i].setAuction(true);
			}

			//reset auction price and auction card
			currentPowerPlant.setNumber(0);
			currentAuctionPrice = 0;
			//numOfPlayerPass = 0;
			indexOfCard = NULL;

			//Print the cards in the market
			cout << "------------------------------Market (Updated)------------------------------" << endl;
			for (int i = 0; i < market.size(); i++) {
				cout << market[i].toString() << endl;
			}
			cout << endl;


		}

		//only one player left
		if (playerLeft == 1) {
			int who = 0;
			int choice;
			for (int i = 0; i < numberOfPlayers; i++) {
				if (players[i].getNumOfPowerPlant() == 0) {
					who = i;
				}
			}
			//who's turn right now
			cout << players[who].getName() << endl;
			cout << "You are the last one" << endl;
			//choose a card to auction
			cout << "Enter the number of the card you want: ";
			cin >> choice;
			cout << endl;

			//check if the card is exist
			abilityOfPurchase(market, choice);
			
			auction(players[who], market[indexOfCard]);
			//set card and money
			int num = players[who].getNumOfPowerPlant();
			players[who].setPowerPlant(market[indexOfCard], num);
			players[who].setMoney(players[who].getMoney() - market[indexOfCard].getNumber());
			//print the information of the card
			cout << "Congratulation, " << players[who].getName() << endl;
			cout << "You get: " << endl;
			cout << currentPowerPlant.toString() << endl;
			cout << endl;

			num = players[who].getNumOfPowerPlant() + 1;
			players[who].setNumOfPowerPlant(num);

			//draw a new plant card, put it in the market and change the order
			market[indexOfCard] = powerPlants.front();
			powerPlants.erase(powerPlants.begin());
			setMarketOrder(market);

			//reset auction price and auction card
			currentPowerPlant.setNumber(0);
			currentAuctionPrice = 0;
			//numOfPlayerPass = 0;
			indexOfCard = NULL;

			//Print the cards in the market
			cout << "------------------------------Market (Updated)------------------------------" << endl;
			for (int i = 0; i < market.size(); i++) {
				cout << market[i].toString() << endl;
			}
			cout << endl;
		}
		//print every players' information
		cout << "Each player has a power plant card now" << endl;
		cout << endl;

		// set the order of the players at the end of each turn
		setPlayerOrder(players, numberOfPlayers);
		for (int i = 0; i < numberOfPlayers; i++) {
			cout << players[i].getName() << endl;
			cout << players[i].toString() << endl;
			cout << endl;
		}

		cout << "Moving to the next phase" << endl;
		turn++;
		cout << endl;

	}


	//****************************************************turn > 1***************************************************
	else {
		int playerLeft = numberOfPlayers;
		//start turn
		while (playerLeft > 1)
		{
			int choice;
			//int indexOfCard;

			//reset the status to true
			/*for (int i = 0; i < numberOfPlayers; i++) {
				players[i].setAuction(true);
			}
*/
			// auction process
			int numOfPlayerPass = 0;

			while (numOfPlayerPass < playerLeft - 1)
			{
				for (int i = 0; i < numberOfPlayers; i++) {
					if (numOfPlayerPass >= playerLeft - 1) {
						break;
					}
					if (players[i].getRoundStatus() == false || players[i].getBought() == true) {
						pass(players[i]);
					}
					else {
						//cout << "Bought?" << players[i].getBought() << endl; //test
						if (players[i].getAuction() == true) {

							cout << players[i].getName() << endl;
							cout << "It's your turn" << endl;
							cout << "Pass the whole round -> Enter: 9" << endl;
							cout << "Auction -> Enter: 1" << endl;
							cout << "Pass -> Enter: 0" << endl;
							cin >> status;
							cout << endl;

							while (status != 0 && status != 1 && status != 9)
							{
								cout << "Please enter a correct number" << endl;
								cout << "Pass the whole round -> Enter: 9" << endl;
								cout << "Auction -> Enter: 1" << endl;
								cout << "Pass -> Enter: 0" << endl;
								cin >> status;
							}
							//in the first turn, no player can pass the whole round, each player should buy a power plant card
							if (currentPowerPlant.getNumber() == 0 && status == 0) {
								do {
									cout << "This is the process of auction. If you want to pass the whole round, please enter 9: " << endl;
									cin >> status;
									while (status != 0 && status != 1 && status != 9)
									{
										cout << "Please enter a correct number" << endl;
										cout << "Pass the whole round -> Enter: 9" << endl;
										cout << "Auction -> Enter: 1" << endl;
										cin >> status;
									}
								} while (status == 0);
							}
							if (status == 0) {
								pass(players[i]);
								numOfPlayerPass++;
							}
							else if (status == 9) {
								players[i].setRoundStatus(false);
								pass(players[i]);
								numOfPlayerPass++;
								playerLeft--;

							}
							else {
								
								if (currentPowerPlant.getNumber() == 0) {
									//if no card is auction, choose a card to start auction
									cout << "Enter the number of the card in the market to start auction: ";
									cin >> choice;
									//check if the card is exist
									abilityOfPurchase(market, choice);
								}

								if (numOfPlayerPass < playerLeft - 1) {
									auction(players[i], market[indexOfCard]);
								}

							}

						}


					}
				}
			}
			//the number of player who doesn't buy the card
			//playerLeft--;
			//who buy this card
			for (int i = 0; i < numberOfPlayers; i++) {
				if (players[i].getAuction() == true && currentPowerPlant.getNumber() != 0) {     

					buyCard(players[i], market[indexOfCard]);

					//print the information of the card
					cout << "Congratulation, " << players[i].getName() << endl;
					cout << "You get: " << endl;
					cout << currentPowerPlant.toString() << endl;
					cout << endl;

					playerLeft--;

					//draw a new plant card, put it in the market and change the order
					market[indexOfCard] = powerPlants.front();
					if (powerPlants.front().getTypeName() == "step3") {
						step = 3;
						setMarketOrder(market);
						changeMarketToStep3(market);
						powerPlants.erase(powerPlants.begin());
					}
					else {
						powerPlants.erase(powerPlants.begin());
						setMarketOrder(market);
					}
					
					//**************check step3 process****************
					//changeMarketToStep3(market);
					//cout << "------------------------------Market (Updated)------------------------------" << endl;//test
					//for (int i = 0; i < market.size(); i++) {
					//	cout << market[i].toString() << endl;
					//}
					cout << endl;

				}

			}
			//reset the status to true
			for (int i = 0; i < numberOfPlayers; i++) {
				players[i].setAuction(true);
			}

			//reset auction price and auction card
			currentPowerPlant.setNumber(0);
			currentAuctionPrice = 0;
			//numOfPlayerPass = 0;
			indexOfCard = NULL;

			//Print the cards in the market
			cout << "------------------------------Market (Updated)------------------------------" << endl;
			for (int i = 0; i < market.size(); i++) {
				cout << market[i].toString() << endl;
			}
			cout << endl;

		}

		//only one player left
		if (playerLeft == 1) {
			int who;
			int choice;
			for (int i = 0; i < numberOfPlayers; i++) {
				if (players[i].getBought() == false && players[i].getRoundStatus() == true) {
					who = i;
					//who's turn right now
					cout << players[who].getName() << endl;
					cout << "You are the last player" << endl;
					cout << "Pass the whole round -> Enter: 9" << endl;
					cout << "Auction -> Enter: 1" << endl;
					cin >> status;
					cout << endl;

					while (status != 1 && status != 9)
					{
						cout << "Please enter a correct number" << endl;
						cout << "Pass the whole round -> Enter: 9" << endl;
						cout << "Auction -> Enter: 1" << endl;
						cout << "Pass -> Enter: 0" << endl;
						cin >> status;
					}

					if (status == 9) {
						players[who].setRoundStatus(false);
						pass(players[who]);
						playerLeft--;

					}
					else {

						if (currentPowerPlant.getNumber() == 0) {
							//choose a card to auction
							cout << "Enter the number of the card in the market to start auction: ";
							cin >> choice;
							//check if the card is exist
							abilityOfPurchase(market, choice);

						}
						auction(players[who], market[indexOfCard]);

						buyCard(players[who], market[indexOfCard]);

						//print the information of the card
						cout << "Congratulation, " << players[who].getName() << endl;
						cout << "You get: " << endl;
						cout << currentPowerPlant.toString() << endl;
						cout << endl;

						//draw a new plant card, put it in the market and change the order
						market[indexOfCard] = powerPlants.front();
						if (powerPlants.front().getTypeName() == "step3") {
							step = 3;
							setMarketOrder(market);
							changeMarketToStep3(market);
							powerPlants.erase(powerPlants.begin());
						}
						else {
							powerPlants.erase(powerPlants.begin());
							setMarketOrder(market);
						}

						//reset the status to true
						for (int i = 0; i < numberOfPlayers; i++) {
							players[i].setAuction(true);
						}

						//reset auction price and auction card
						currentPowerPlant.setNumber(0);
						currentAuctionPrice = 0;
						//numOfPlayerPass = 0;
						indexOfCard = NULL;

					}


				}
			}
			
		}

		//reset the Bought status to false
		for (int i = 0; i < numberOfPlayers; i++) {
			players[i].setBought(false);
		}

		//Print the cards in the market
		cout << "------------------------------Market (Updated)------------------------------" << endl;
		for (int i = 0; i < market.size(); i++) {
			cout << market[i].toString() << endl;
		}
		cout << endl;

	}

	cout << "Phase finish" << endl;
	cout << endl;

	//if no one buy card, delete the smallest one
	if (checkNoOneBuyCard(players)) {
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
	setPlayerOrder(players, numberOfPlayers);
	cout << "New order of the players " << endl;
	for (int i = 0; i < numberOfPlayers; i++) {
		cout << players[i].getName() << endl;
		cout << players[i].toString() << endl;
		cout << endl;
	}

	cout << "Moving to the next phase" << endl;
	turn++;
	cout << endl;

	system("pause");
	return 0;
}