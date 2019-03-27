#include "Resources.h"
#include "PowerPlant.h"
#include "Player.h"
#include "Phase1_2.h"
#include <time.h>
#include <vector>
#include <iostream>
using namespace std;



int main() {
	Phase1_2 phase1_2;
	//Initialize how many players

	cout << "Please enter the number of the players: ";
	cin >> phase1_2.numberOfPlayers;
	cout << endl;
	Player *players = new Player[phase1_2.numberOfPlayers];

	//set a simple name for each player
	for (int i = 0; i < phase1_2.numberOfPlayers; i++) {
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

	//give a random order in the first phase1_2.turn
	if (phase1_2.turn == 1) {
		phase1_2.shufflePlayers(players, phase1_2.numberOfPlayers);
		for (int i = 0; i < phase1_2.numberOfPlayers; i++) {
			//players[i].setNumOfCity(i);
			cout << players[i].getName() << endl;
			cout << players[i].toString() << endl;
			cout << endl;
		}
	}

	////*************************test check resources*************************
	////coal: 3
	//players[0].setCoalNum(3);
	//players[0].setPowerPlant(powerPlants[12], 0);
	////oil: 3
	//players[0].setOilNum(3);
	//players[0].setPowerPlant(powerPlants[13], 1);
	////uranium: 2
	//players[0].setUraniumNum(2);
	//players[0].setPowerPlant(powerPlants[14], 2);
	//players[0].setNumOfPowerPlant(3);
	////change to garbage: 2
	//buyCard(players[0], powerPlants[16]);

	////coal: 5
	//players[1].setCoalNum(5);
	//players[1].setPowerPlant(powerPlants[12], 0);
	////oil: 5
	//players[1].setOilNum(5);
	//players[1].setPowerPlant(powerPlants[13], 1);
	////hybrid: 2 (1 coal + 1 oil)
	//players[1].setPowerPlant(powerPlants[9], 2);
	//players[1].setNumOfPowerPlant(3);
	////change to garbage: 2
	//buyCard(players[1], powerPlants[16]);
	////*************************test check resources*************************


	////***********************test set cards order in each players & test if a player have 4 cards*************************
	//for (int i = 0; i < phase1_2.numberOfPlayers; i++) {
	//	int numOfCards = players[i].getNumOfPowerPlant();
	//	while (numOfCards < 3) {
	//		players[i].setPowerPlant(powerPlants.front(), numOfCards);
	//		powerPlants.erase(powerPlants.begin());
	//		numOfCards++;
	//		players[i].setNumOfPowerPlant(numOfCards);
	//	}
	//	setCardOwnedByPlayer(players[i]);
	//}
	//for (int i = 0; i < phase1_2.numberOfPlayers; i++) {
	//	cout << players[i].getName() << endl;
	//	cout << players[i].toString() << endl;
	//	cout << endl;
	//}
	//cout << endl;
	//setPlayerOrder(players, phase1_2.numberOfPlayers);
	//cout << "New order of the players " << endl;
	//for (int i = 0; i < phase1_2.numberOfPlayers; i++) {
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
	if (phase1_2.turn == 1) {
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

	//in the first phase1_2.turn, each players must buy one power plant
	if (phase1_2.turn == 1) {
		int playerLeft = phase1_2.numberOfPlayers;
		//PowerPlant phase1_2.currentPowerPlant;

		while (playerLeft > 1)
		{
			int choice;
			//int indexOfCard;

			// auction process
			int numOfPlayerPass = 0;
			while (numOfPlayerPass < playerLeft - 1)
			{
				for (int i = 0; i < phase1_2.numberOfPlayers; i++) {
					if (players[i].getNumOfPowerPlant() == 1) {
						phase1_2.pass(players[i]);

					}
					else {
						if (numOfPlayerPass >= playerLeft - 1) {
							break;
						}
						//cout << "Status:" << players[i].getAuction() << endl;
						if (players[i].getAuction() == true) {

							cout << players[i].getName() << endl;
							cout << "It's your phase1_2.turn" << endl;

							//who's phase1_2.turn right now
							/*cout << players[i].getName() << endl;
							cout << "It's your phase1_2.turn" << endl;*/
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
							//in the first phase1_2.turn, no player can pass the whole round, each player should buy a power plant card
							if (phase1_2.currentPowerPlant.getNumber() == 0 && status == 0) {
								do {
									cout << "This is the first phase1_2.turn, you cannot pass your round" << endl;
									cout << "Please enter 1 to start auction" << endl;
									cin >> status;
								} while (status !=1);
							}

							if (status == 0) {
								phase1_2.pass(players[i]);
								numOfPlayerPass++;
							}
							else {
								
								//if no card is auction
								if (phase1_2.currentPowerPlant.getNumber() == 0) {
									//choose a card to auction
									cout << "Enter the number of the card in the market to start auction: ";
									cin >> choice;

									//check if the card is exist
									phase1_2.abilityOfPurchase(market, choice);

								}

								if (numOfPlayerPass < playerLeft - 1) {
									phase1_2.auction(players[i], market[phase1_2.indexOfCard]);
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
			for (int i = 0; i < phase1_2.numberOfPlayers; i++) {
				if (players[i].getAuction() == true && phase1_2.currentPowerPlant.getNumber()!=0) {
					int num = players[i].getNumOfPowerPlant();
					players[i].setPowerPlant(market[phase1_2.indexOfCard], num);
					players[i].setMoney(players[i].getMoney() - market[phase1_2.indexOfCard].getNumber());
					//print the information of the card
					cout << "Congratulation, " << players[i].getName() << endl;
					cout << "You get: " << endl;
					cout << phase1_2.currentPowerPlant.toString() << endl;
					cout << endl;

					num = players[i].getNumOfPowerPlant() + 1;
					players[i].setNumOfPowerPlant(num);

				}
			}

			//draw a new plant card, put it in the market and change the order
			market[phase1_2.indexOfCard] = powerPlants.front();
			powerPlants.erase(powerPlants.begin());
			phase1_2.setMarketOrder(market);

			//reset the status to true
			for (int i = 0; i < phase1_2.numberOfPlayers; i++) {
				players[i].setAuction(true);
			}

			//reset auction price and auction card
			phase1_2.currentPowerPlant.setNumber(0);
			phase1_2.currentAuctionPrice = 0;
			//numOfPlayerPass = 0;
			phase1_2.indexOfCard = NULL;

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
			for (int i = 0; i < phase1_2.numberOfPlayers; i++) {
				if (players[i].getNumOfPowerPlant() == 0) {
					who = i;
				}
			}
			//who's phase1_2.turn right now
			cout << players[who].getName() << endl;
			cout << "You are the last one" << endl;
			//choose a card to auction
			cout << "Enter the number of the card you want: ";
			cin >> choice;
			cout << endl;

			//check if the card is exist
			phase1_2.abilityOfPurchase(market, choice);
			
			phase1_2.auction(players[who], market[phase1_2.indexOfCard]);
			//set card and money
			int num = players[who].getNumOfPowerPlant();
			players[who].setPowerPlant(market[phase1_2.indexOfCard], num);
			players[who].setMoney(players[who].getMoney() - market[phase1_2.indexOfCard].getNumber());
			//print the information of the card
			cout << "Congratulation, " << players[who].getName() << endl;
			cout << "You get: " << endl;
			cout << phase1_2.currentPowerPlant.toString() << endl;
			cout << endl;

			num = players[who].getNumOfPowerPlant() + 1;
			players[who].setNumOfPowerPlant(num);

			//draw a new plant card, put it in the market and change the order
			market[phase1_2.indexOfCard] = powerPlants.front();
			powerPlants.erase(powerPlants.begin());
			phase1_2.setMarketOrder(market);

			//reset auction price and auction card
			phase1_2.currentPowerPlant.setNumber(0);
			phase1_2.currentAuctionPrice = 0;
			//numOfPlayerPass = 0;
			phase1_2.indexOfCard = NULL;

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

		// set the order of the players at the end of each phase1_2.turn
		phase1_2.setPlayerOrder(players, phase1_2.numberOfPlayers);
		for (int i = 0; i < phase1_2.numberOfPlayers; i++) {
			cout << players[i].getName() << endl;
			cout << players[i].toString() << endl;
			cout << endl;
		}

		cout << "Moving to the next phase" << endl;
		phase1_2.turn++;
		cout << endl;

	}


	//****************************************************phase1_2.turn > 1***************************************************
	else {
		int playerLeft = phase1_2.numberOfPlayers;
		//start phase1_2.turn
		while (playerLeft > 1)
		{
			int choice;
			//int indexOfCard;

			//reset the status to true
			/*for (int i = 0; i < phase1_2.numberOfPlayers; i++) {
				players[i].setAuction(true);
			}
*/
			// auction process
			int numOfPlayerPass = 0;

			while (numOfPlayerPass < playerLeft - 1)
			{
				for (int i = 0; i < phase1_2.numberOfPlayers; i++) {
					if (numOfPlayerPass >= playerLeft - 1) {
						break;
					}
					if (players[i].getRoundStatus() == false || players[i].getBought() == true) {
						phase1_2.pass(players[i]);
					}
					else {
						//cout << "Bought?" << players[i].getBought() << endl; //test
						if (players[i].getAuction() == true) {

							cout << players[i].getName() << endl;
							cout << "It's your phase1_2.turn" << endl;
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
							//in the first phase1_2.turn, no player can pass the whole round, each player should buy a power plant card
							if (phase1_2.currentPowerPlant.getNumber() == 0 && status == 0) {
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
								phase1_2.pass(players[i]);
								numOfPlayerPass++;
							}
							else if (status == 9) {
								players[i].setRoundStatus(false);
								phase1_2.pass(players[i]);
								numOfPlayerPass++;
								playerLeft--;

							}
							else {
								
								if (phase1_2.currentPowerPlant.getNumber() == 0) {
									//if no card is auction, choose a card to start auction
									cout << "Enter the number of the card in the market to start auction: ";
									cin >> choice;
									//check if the card is exist
									phase1_2.abilityOfPurchase(market, choice);
								}

								if (numOfPlayerPass < playerLeft - 1) {
									phase1_2.auction(players[i], market[phase1_2.indexOfCard]);
								}

							}

						}


					}
				}
			}
			//the number of player who doesn't buy the card
			//playerLeft--;
			//who buy this card
			for (int i = 0; i < phase1_2.numberOfPlayers; i++) {
				if (players[i].getAuction() == true && phase1_2.currentPowerPlant.getNumber() != 0) {

					phase1_2.buyCard(players[i], market[phase1_2.indexOfCard]);

					//print the information of the card
					cout << "Congratulation, " << players[i].getName() << endl;
					cout << "You get: " << endl;
					cout << phase1_2.currentPowerPlant.toString() << endl;
					cout << endl;

					playerLeft--;

					//draw a new plant card, put it in the market and change the order
					market[phase1_2.indexOfCard] = powerPlants.front();
					if (powerPlants.front().getTypeName() == "step3") {
						phase1_2.step = 3;
						phase1_2.setMarketOrder(market);
						phase1_2.changeMarketToStep3(market);
						powerPlants.erase(powerPlants.begin());
					}
					else {
						powerPlants.erase(powerPlants.begin());
						phase1_2.setMarketOrder(market);
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
			for (int i = 0; i < phase1_2.numberOfPlayers; i++) {
				players[i].setAuction(true);
			}

			//reset auction price and auction card
			phase1_2.currentPowerPlant.setNumber(0);
			phase1_2.currentAuctionPrice = 0;
			//numOfPlayerPass = 0;
			phase1_2.indexOfCard = NULL;

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
			for (int i = 0; i < phase1_2.numberOfPlayers; i++) {
				if (players[i].getBought() == false && players[i].getRoundStatus() == true) {
					who = i;
					//who's phase1_2.turn right now
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
						phase1_2.pass(players[who]);
						playerLeft--;

					}
					else {

						if (phase1_2.currentPowerPlant.getNumber() == 0) {
							//choose a card to auction
							cout << "Enter the number of the card in the market to start auction: ";
							cin >> choice;
							//check if the card is exist
							phase1_2.abilityOfPurchase(market, choice);

						}
						phase1_2.auction(players[who], market[phase1_2.indexOfCard]);

						phase1_2.buyCard(players[who], market[phase1_2.indexOfCard]);

						//print the information of the card
						cout << "Congratulation, " << players[who].getName() << endl;
						cout << "You get: " << endl;
						cout << phase1_2.currentPowerPlant.toString() << endl;
						cout << endl;

						//draw a new plant card, put it in the market and change the order
						market[phase1_2.indexOfCard] = powerPlants.front();
						if (powerPlants.front().getTypeName() == "step3") {
							phase1_2.step = 3;
							phase1_2.setMarketOrder(market);
							phase1_2.changeMarketToStep3(market);
							powerPlants.erase(powerPlants.begin());
						}
						else {
							powerPlants.erase(powerPlants.begin());
							phase1_2.setMarketOrder(market);
						}

						//reset the status to true
						for (int i = 0; i < phase1_2.numberOfPlayers; i++) {
							players[i].setAuction(true);
						}

						//reset auction price and auction card
						phase1_2.currentPowerPlant.setNumber(0);
						phase1_2.currentAuctionPrice = 0;
						//numOfPlayerPass = 0;
						phase1_2.indexOfCard = NULL;

					}


				}
			}
			
		}

		//reset the Bought status to false
		for (int i = 0; i < phase1_2.numberOfPlayers; i++) {
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
	if (phase1_2.checkNoOneBuyCard(players)) {
		cout << "No one buy power plant card in this phase1_2.turn" << endl;
		cout << "------------------------------Market (Updated)------------------------------" << endl;
		market[0] = powerPlants.front();
		phase1_2.setMarketOrder(market);
		powerPlants.erase(powerPlants.begin());
		for (int i = 0; i < market.size(); i++) {
			cout << market[i].toString() << endl;
		}
		cout << endl;
	}


	

	// set the order of the players at the end of each phase1_2.turn
	phase1_2.setPlayerOrder(players, phase1_2.numberOfPlayers);
	cout << "New order of the players " << endl;
	for (int i = 0; i < phase1_2.numberOfPlayers; i++) {
		cout << players[i].getName() << endl;
		cout << players[i].toString() << endl;
		cout << endl;
	}

	cout << "Moving to the next phase" << endl;
	phase1_2.turn++;
	cout << endl;

	system("pause");
	return 0;
}