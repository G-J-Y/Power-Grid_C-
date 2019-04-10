#include "Player.h"
#include <iostream>
using std::cout;
using std::endl;

void Moderate::execute(PowerPlant& currentPowerPlant, int& currentPrice,
	vector<PowerPlant>& market, int& numOfPlayerPass,
	int& playerLeft, int& indexOfCard, Player &p, int turn)
{
	cout << "\n---Moderate strategy used by " << p.getName() << "---\n";

	int capacity = 0; //stores the max units of resources a player can buy
					  //regardless of type
	int held; //stores the total units of resources a player holds
			  //regardless of type

	for (int j = 0; j < p.getNumOfPowerPlant(); j++) 
		capacity = capacity + p.getPowerPlant(j).getNeed();
		
	capacity = capacity * 2;
	held = p.getCoalNum() + p.getOilNum()
		+ p.getGarbageNum() + p.getUraniumNum();

	int left = capacity - held; //if left == 0, the player's resource is full

	//if (left == 0)
	cout << "With his/her current Powerplant cards, "
		<< p.getName() 	<< " can buy " << left << " unit(s) of resources.\n";
	if (left > 0)
	{
		cout << p.getName()
			<< " still has " << left 
			<<" space to hold resources and will pass this round. \n";
		p.setAuction(false);
		numOfPlayerPass++;
		return;
	}		

	//find the most inefficient card's need
	int min = 100; //set a big enough number to min
	for (int j = 0; j < p.getNumOfPowerPlant(); j++) 
		if (min > p.getPowerPlant(j).getNeed())
			min = p.getPowerPlant(j).getNeed();		
	
		

	//find the most inefficient card's type
	string minType = "";
	for (int j = 0; j < p.getNumOfPowerPlant(); j++)
		if (min == p.getPowerPlant(j).getNeed()) 
			minType = p.getPowerPlant(j).getTypeName();		
		
			

	cout << p.getName()
		<< " needs to buy a more efficient card of type: " << minType << endl;
	string type = minType;

	//if this environmental player is the only one who hasn't got a card
	if (playerLeft == 1) {
		cout << p.getName() << " is the last Player who hasn't got a card. \n";

		int choice = -1;
		int max = 0;
		for (int i = 0; i < 4; i++) {
			if (type == market[i].getTypeName() && max < market[i].getNeed())
				choice = i;
		}

		//if a more efficient Card is not found in the market
		if (choice == -1) {
			cout << "a more efficient Card is not found in the market.\n";	
			p.setAuction(false);
			numOfPlayerPass++;
			return;
		}
		//if the money is not enough to buy environmental card
		else if (p.getMoney() < market[choice].getNumber())
		{
			cout << "You cannot afford this card.\n";
			p.setAuction(false);
			numOfPlayerPass++;
			return; //terminate the function execute
		}
		cout << p.getName() << " automatically chose the more efficient Plant in the market \n";
		currentPowerPlant = market[choice];
		indexOfCard = choice;
		cout << p.getName() << " has chosen " << currentPowerPlant.toString() << endl;

		currentPrice = market[choice].getNumber();
		cout << p.getName() << " bid " << currentPrice << " Elektroes!!\n" << endl;
		return;
	}
	//if this moderate player is not the only one who hasn't got a card	
	if (currentPowerPlant.getNumber() == 0) { //if I am the first to start a card auction 
		//Print the cards in the market
		cout << "------------------------------Market------------------------------"
			<< endl;
		for (int i = 0; i < market.size(); i++) {
			cout << market[i].toString() << endl;
		}
		cout << endl;

		
		cout << p.getName() << " will automatically choose to bid a more efficient Plant,\n"
			<< "because he/she reaches the limit of possessing resources.\n";
			
		
		int choice = -1;	
		int max = 0;
		//a more efficient card is the right type of recource with bigger capacity
		//the "right type" means this type is type of the least efficienty card the player holds
		//now we want a card of this type more efficient
		for (int i = 0; i < 4; i++) {
			if (type == market[i].getTypeName() && max < market[i].getNeed())
				choice = i;
		}

		if (choice == -1) {
			cout << "A more efficient Card is not found in the market."
				<< p.getName() << " will pass.\n";
			p.setAuction(false);
			numOfPlayerPass++;
			return;
		}

		if (p.getMoney() < market[choice].getNumber())
		{
			cout << "You cannot afford this more efficienty card.\n";
			p.setAuction(false);
			numOfPlayerPass++;
			return; //terminate the function execute
		}

		indexOfCard = choice;
		cout << p.getName() << " automatically chose the more efficienty Plant in the market \n";
		currentPowerPlant = market[choice];
		cout << p.getName() << " has chosen " << currentPowerPlant.toString() << endl;

		currentPrice = market[choice].getNumber();
		cout << p.getName() << " bid " << currentPrice << " Elektroes!!\n" << endl;
	}

	else { //if I am not the first to start a card auction 
		if (currentPowerPlant.getTypeName() != type) {
			cout << "Current card type: " << currentPowerPlant.getTypeName() << endl;
			cout << "Other players are bidding a card that is not more effiecent. "
				<< p.getName() << " passes because he/she needs " << type << endl;
			p.setAuction(false);
			numOfPlayerPass++;
			return;
		}

		if (numOfPlayerPass < playerLeft - 1) {  //if there are more than two player bidding
			//if the aggressive player doesn't have enough money, the function ends
			if (p.getMoney() <= currentPrice) {
				cout << p.getName() << " doesn't have enough money to continue auction.\n";
				p.setAuction(false);
				numOfPlayerPass++;
				return;
			}
			//if the moderate player has enough money, 
			//he/she will always continue bidding for a more efficient card
			currentPrice = currentPrice + 1;
			//cout <<"Price" <<players[i].getPrice() << endl;
			cout << "\nThis is a more efficienty card! ";
			cout << p.getName() << " bid " << currentPrice << " Elektroes!!\n" << endl;
		}


	}
	
}