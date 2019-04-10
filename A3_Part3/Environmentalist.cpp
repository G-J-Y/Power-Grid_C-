#include "Player.h"
#include <iostream>
using std::cout;
using std::endl;

void Environmentalist::execute(PowerPlant& currentPowerPlant, int& currentPrice,
	vector<PowerPlant>& market, int& numOfPlayerPass,
	int& playerLeft, int& indexOfCard, Player &p, int turn)
{
	cout << "---Environmentalist strategy used by " << p.getName() << "---\n";
	cout << p.getName() << " will automatically choose to bid a environmental Plant,\n"
		<< " and will pass if no environmental Plant was in the market.\n";
	
	//if this environmental player is the only one who hasn't got a card
	if (playerLeft == 1) {
		cout << p.getName() << " is the last Player who hasn't got a card. \n";
		
		int choice = -1;
		for (int i = 0; i < 4; i++) {
			if (market[i].getTypeName() == "eco")
				choice = i;
		}

		//if "No environmental Card found in the market
		if (choice == -1) {
			cout << "No environmental Card found in the market.\n";
			if (turn == 1) {
				cout << "But it is turn 1, " << p.getName()
					<< " automatically chose a card with smallest number "
					<< "though no environmental Card found in the market.\n";
				choice = 0;
				if (p.getMoney() < market[choice].getNumber())
				{
					cout << "You cannot afford this card.\n";
					p.setAuction(false);
					numOfPlayerPass++;
					return; //terminate the function execute
				}
				indexOfCard = choice;
				cout << p.getName() << " automatically chose smallest number Plant in the market \n";
				currentPowerPlant = market[choice];
				cout << p.getName() << " has chosen " << currentPowerPlant.toString() << endl;

				currentPrice = market[choice].getNumber();
				cout << p.getName() << " bid " << currentPrice << " Elektroes!!\n" << endl;
			}
			if (choice == -1) {
				p.setAuction(false);
				numOfPlayerPass++;
				return;
			}
				
		}

		//if the money is not enough to buy environmental card
		else if (p.getMoney() < market[choice].getNumber())
		{
			cout << "You cannot afford the environmental card.\n";
			p.setAuction(false);
			numOfPlayerPass++;
			return; //terminate the function execute
		}
		cout << p.getName() << " automatically chose the environmental Plant in the market \n";
		currentPowerPlant = market[choice];
		cout << p.getName() << " has chosen " << currentPowerPlant.toString() << endl;

		currentPrice = market[choice].getNumber();
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

		//automatically choose the environmental Plant card to auction
		int choice = -1;
		
		//if there is a environmental card in the market
		for (int i = 0; i < 4; i++) {			
			if (market[i].getTypeName() == "eco")
				choice =  i;
		}

		//if "No environmental Card found in the market
		if (choice == -1) {
			cout << "No environmental Card found in the market.\n";
			if (turn == 1) {
				cout << "But it is turn 1, " << p.getName()
					<< " automatically chose a card with smallest number "
					<< "though no environmental Card found in the market.\n";					
				choice = 0;
				if (p.getMoney() < market[choice].getNumber())
				{
					cout << "You cannot afford this card.\n";
					p.setAuction(false);
					numOfPlayerPass++;
					return; //terminate the function execute
				}
				indexOfCard = choice;
				cout << p.getName() << " automatically chose smallest number Plant in the market \n";
				currentPowerPlant = market[choice];
				cout << p.getName() << " has chosen " << currentPowerPlant.toString() << endl;

				currentPrice = market[choice].getNumber();
				cout << p.getName() << " bid " << currentPrice << " Elektroes!!\n" << endl;
			}
			if (choice == -1) {
				p.setAuction(false);
				numOfPlayerPass++;
				return;
			}

				
		}
		
		//if the money is not enough to buy environmental card
		else {	
			
			if (p.getMoney() < market[choice].getNumber())
			{
				cout << "You cannot afford the environmental card.\n";
				p.setAuction(false);
				numOfPlayerPass++;
				return; //terminate the function execute
			}
			indexOfCard = choice;
			cout << p.getName() << " automatically chose the environmental Plant in the market \n";
			currentPowerPlant = market[choice];
			cout << p.getName() << " has chosen " << currentPowerPlant.toString() << endl;

			currentPrice = market[choice].getNumber();
			cout << p.getName() << " bid " << currentPrice << " Elektroes!!\n" << endl;
		}
	}

	else 
	{ //if I am not the first to start a card auction 
		if (currentPowerPlant.getTypeName() != "eco") {			
			cout << "Other players are bidding for a non-environmental Card. " 
				 << p.getName() << " passes.\n";
			
			if (turn == 1) {
				cout << "But it is turn 1, " << p.getName()
					<< " continues bidding "
					<< "though no environmental Card found in the market.\n";				
				if (p.getMoney() < currentPrice)
				{
					cout << "You cannot afford this card.\n";
					p.setAuction(false);
					numOfPlayerPass++;
					return; //terminate the function execute
				}

				
				//an environmental player only wants to pays initial price for a non-envir card				
				if (currentPrice >= currentPowerPlant.getNumber()) {
					cout << p.getName() << " passed because "
						<< "he/she only wants to pays initial price for a non-envir card.\n";
					p.setAuction(false);
					numOfPlayerPass++;
					return;
				}

				currentPrice = currentPrice + 1;
				cout << p.getName() << " bid " << currentPrice << " Elektroes!!\n" << endl;
			}			
			return; //terminate the function execute
		}

		else {
			if (numOfPlayerPass < playerLeft - 1) 
			{  //if there are more than two player bidding
			//if the aggressive player doesn't have enough money, the function ends
				if (p.getMoney() <= currentPrice) {
					cout << p.getName() << " doesn't have enough money to continue auction.\n";
					p.setAuction(false);
					numOfPlayerPass++;
					return;
				}
				//if the environmental player has enough money, 
				//he/she will always continue bidding for a environmental card
				currentPrice = currentPrice + 1;
				//cout <<"Price" <<players[i].getPrice() << endl;
				cout << p.getName() << " bid " << currentPrice << " Elektroes!!\n" << endl;
			}
		}		
	}
}