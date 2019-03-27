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

//every time when a new card put into the market, set a new order
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
void changeMarketToStep3(vector<PowerPlant> p, int index) {
	step = 3;
	p.erase(p.begin() + index - 1);
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
	powerPlants[42] = PowerPlant(0, 0, PowerPlant::step3, 0);

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








	//when turn > 1
	else {
		int playerLeft = numberOfPlayers;
		PowerPlant currentPowerPlant;

		while (playerLeft > 1)
		{
			int choice;
			//int indexOfCard;

			//reset the status to true
			for (int i = 0; i < numberOfPlayers; i++) {
				players[i].setAuction(true);
			}

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
						//cout << "Status:" << players[i].getAuction() << endl;
						if (players[i].getAuction() == true) {

							cout << players[i].getName() << endl;
							cout << "It's your turn" << endl;

							//if no card is auction

							//who's turn right now
							/*cout << players[i].getName() << endl;
							cout << "It's your turn" << endl;*/
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
							if (status == 0) {
								pass(players[i]);
								numOfPlayerPass++;
							}
							else if (status == 9) {
								players[i].setRoundStatus(false);
								pass(players[i]);
								numOfPlayerPass++;
								//playerLeft--;

							}
							else {
								cout << "Test: " << currentPowerPlant.getNumber() << endl;             //test
								if (currentPowerPlant.getNumber() == 0) {
									//if no card is auction, choose a card to start auction
									cout << "Enter the number of the card in the market to start auction: ";
									cin >> choice;
									//check if the card is exist

									abilityOfPurchase(market, choice);

									/*for (int i = 0; i < 4; i++) {
										if (market[i].getNumber() == choice) {
											currentPowerPlant = market[i];
											indexOfCard = i;
										}
									}
									while (currentPowerPlant.getNumber() == 0)
									{

										cout << "You cannot buy this card, please enter a new number: ";
										cin >> choice;
										for (int i = 0; i < 4; i++) {
											if (market[i].getNumber() == choice) {
												currentPowerPlant = market[i];
												indexOfCard = i;
											}
										}
									}*/
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
			playerLeft--;
			//who buy this card
			for (int i = 0; i < numberOfPlayers; i++) {
				if (players[i].getAuction() == true && currentPowerPlant.getNumber() != 0) {     //test
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
					players[i].setBought(true);
					

					//draw a new plant card, put it in the market and change the order
					market[indexOfCard] = powerPlants.front();
					powerPlants.erase(powerPlants.begin());
					setMarketOrder(market);

					////reset the status to true
					//for (int i = 0; i < numberOfPlayers; i++) {
					//	players[i].setAuction(true);
					//}

			

				}

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
				}
			}
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
					for (int i = 0; i < 4; i++) {
						if (market[i].getNumber() == choice) {
							currentPowerPlant = market[i];
							indexOfCard = i;
						}
					}
					while (currentPowerPlant.getNumber() == 0)
					{

						cout << "You cannot buy this card, please enter a new number: ";
						cin >> choice;
						for (int i = 0; i < 4; i++) {
							if (market[i].getNumber() == choice) {
								currentPowerPlant = market[i];
								indexOfCard = i;
							}
						}
					}
				}
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

			}

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