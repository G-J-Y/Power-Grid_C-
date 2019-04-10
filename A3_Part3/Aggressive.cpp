#include "Player.h"
#include <iostream>
using std::cout;
using std::endl;

void Aggressive::execute(PowerPlant& currentPowerPlant, int& currentPrice, 
	vector<PowerPlant>& market, int& numOfPlayerPass, 
	int& playerLeft, int& indexOfCard, Player &p, int turn)
{
	cout << "---Aggressive strategy used by " << p.getName() << "---\n";
	//cout << p.getName() << endl;
	cout << p.getName() << " will automatically choose to auction" << endl;

	//if this aggressive player is the only one who hasn't got a card
	if (playerLeft == 1) {
		cout << p.getName() << " is the last Player who hasn't got a card. \n";
		cout << p.getName() << " automatically chose the 4th card in the market \n";
		int choice = 3;
		//if the money is not enough to buy 4th card
		while (p.getMoney() < market[choice].getNumber())
		{
			choice--;
			if (choice < 0) {
				cout << "You canno afford any card.\n";
				p.setAuction(false);
				numOfPlayerPass++;
				return; //terminate the function execute
			}
		}
		currentPowerPlant = market[choice];
		cout << p.getName() << " has chosen " << currentPowerPlant.toString() << endl;

		currentPrice = market[choice].getNumber();
		indexOfCard = choice;
		cout << p.getName() << " bid " << currentPrice << " Elektroes!!\n" << endl;
		return;
	}

	//if this environmental player is not the only one who hasn't got a card	
	if (currentPowerPlant.getNumber() == 0) { //if I am the first to start a card auction 
		//Print the cards in the market
		cout << "------------------------------Market------------------------------"
			<< endl;
		for (int i = 0; i < market.size(); i++) {
			cout << market[i].toString() << endl;
		}
		cout << endl;

		//automatically choose the "best" card to auction
		cout << p.getName() << " automatically chose the 4th card in the market \n";
		int choice = 3;
		//if the money is not enough to buy 4th card
		while (p.getMoney() < market[choice].getNumber())
		{
			choice--;
			if (choice < 0) {
				cout << "You canno afford any card.\n";
				p.setAuction(false);
				numOfPlayerPass++;
				return; //terminate the function execute
			}
		}
		indexOfCard = choice;
		currentPowerPlant = market[choice];
		cout << p.getName() << " has chosen " << currentPowerPlant.toString() << endl;

		currentPrice = market[choice].getNumber();
		cout << p.getName() << " bid " << currentPrice << " Elektroes!!\n" << endl;

	}
	else {
		if (numOfPlayerPass < playerLeft - 1) {  //if there are more than two player bidding
			//if the aggressive player doesn't have enough money, the function ends
			if (p.getMoney() <= currentPrice) {
				cout << p.getName() << " doesn't have enough money to continue auction.\n";
				p.setAuction(false);
				//cout << p.getName() << "\'s auction status: " << p.getAuction() << endl;
				numOfPlayerPass++;
				return;
			}
			//if the aggressive player has enough money, 
			//he/she will always continue bidding
			currentPrice = currentPrice + 1;
			//cout <<"Price" <<players[i].getPrice() << endl;
			cout << p.getName() << " bid " << currentPrice << " Elektroes!!\n" << endl;
		}		
	}
}