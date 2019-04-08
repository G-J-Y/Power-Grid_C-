#include "Aggressive.h"
#include <iostream>
using std::cout;
using std::endl;

void Aggressive::execute(PowerPlant& currentPowerPlant, int& currentPrice, 
	vector<PowerPlant> market, int& numOfPlayerPass, 
	int& playerLeft, int& indexOfCard, int money, string name) 
{
	cout << "---Aggressive stratege used by " << name << "---\n";
	//cout << p.getName() << endl;
	cout << name << " will automatically choose to auction" << endl;

	//if this aggressive player is the only one who hasn't got a card
	if (playerLeft == 1) {
		cout << name << " is the last Player who hasn't got a card. \n";
		cout << name << " automatically chose the 4th card in the market \n";
		int choice = 3;
		//if the money is not enough to buy 4th card
		while (money < market[choice].getNumber())
		{
			choice--;
			if (choice < 0) {
				cout << "You canno afford any card.\n";
				return; //terminate the function execute
			}
		}
		currentPowerPlant = market[choice];
		cout << name << " has chosen " << currentPowerPlant.toString() << endl;

		currentPrice = market[choice].getNumber();
		cout << name << " bid " << currentPrice << " Elektroes!!\n" << endl;
		return;
	}


	if (currentPowerPlant.getNumber() == 0) { //if I am the first to start a card auction 
		//Print the cards in the market
		cout << "------------------------------Market------------------------------"
			<< endl;
		for (int i = 0; i < market.size(); i++) {
			cout << market[i].toString() << endl;
		}
		cout << endl;

		//automatically choose the "best" card to auction
		cout << name << " automatically chose the 4th card in the market \n";
		int choice = 3;
		//if the money is not enough to buy 4th card
		while (money < market[choice].getNumber())
		{
			choice--;
			if (choice < 0) {
				cout << "You canno afford any card.\n";
				return; //terminate the function execute
			}
		}
		currentPowerPlant = market[choice];
		cout << name << " has chosen " << currentPowerPlant.toString() << endl;

		currentPrice = market[choice].getNumber();
		cout << name << " bid " << currentPrice << " Elektroes!!\n" << endl;

	}
	else {
		if (numOfPlayerPass < playerLeft - 1) {  //if there are more than two player bidding
			//if the aggressive player doesn't have enough money, the function ends
			if (money <= currentPrice) {
				cout << name << " doesn't have enough money to continue auction.\n";
				return;
			}
			//if the aggressive player has enough money, 
			//he/she will always continue bidding
			currentPrice = currentPrice + 1;
			//cout <<"Price" <<players[i].getPrice() << endl;
			cout << name << " bid " << currentPrice << " Elektroes!!\n" << endl;
		}		
	}
}