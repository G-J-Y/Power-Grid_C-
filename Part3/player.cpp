#include <iostream>
#include "Player.h"
#include <string>


using namespace std;

// default 
Player::Player() {
	name = "";
	money = 50;
	numOfCity = 0;
	numOfPowerPlant = 0;
	numOfPoweredCities = 0;
	//powerPlant;
	coalNum = 0;
	oilNum = 0;
	garbageNum = 0;
	uraniumNum = 0;
	auction = true;
	auctionPrice = 0;
	roundStatus = true;
	bought = false;
}

//set method: change value
void Player::setMoney(int m) {
	money = m;
}
//set method: change value
void Player::setNumOfCity(int c) {
	numOfCity = c;
}
//set method: change value
void Player::setNumOfPowerPlant(int p) {
	numOfPowerPlant = p;
}
//set method: change value
void Player::setNumOfPoweredCities(int pc){
	numOfPoweredCities = pc;
}
//set method: change value
void Player::setCoalNum(int c) {
	coalNum = c;
}
//set method: change value
void Player::setOilNum(int o) {
	oilNum = o;
}
//set method: change value
void Player::setGarbageNum(int g) {
	garbageNum = g;
}
//set method: change value
void Player::setUraniumNum(int u) {
	uraniumNum = u;
}
//set method: change value
void Player::setAuction(bool b) {
	auction = b;
}
//set method: change value
void Player::setRoundStatus(bool b) {
	roundStatus = b;
}
//set method: change value
void Player::setBought(bool b) {
	bought = b;
}
//set method: change value
void Player::setPowerPlant(PowerPlant p,int n) {
	powerPlant[n] = p;
}
//get method: get value
int Player::getMoney(void) {
	return money;
}
//get method: get value
int Player::getNumOfCity(void) {
	return numOfCity;
}
//get method: get value
int Player::getNumOfPowerPlant(void) {
	return numOfPowerPlant;
}
//get method: get value
int Player::getNumOfPoweredCities(){
	return numOfPoweredCities;
}
//get method: get value
int Player::getCoalNum(void) {
	return coalNum;
}
//get method: get value
int Player::getOilNum(void) {
	return oilNum;
}
//get method: get value
int Player::getGarbageNum(void) {
	return garbageNum;
}
//get method: get value
int Player::getUraniumNum(void) {
	return uraniumNum;
}
//get method: get value
bool Player::getAuction() {
	return auction;
}
//get method: get value
bool Player::getRoundStatus() {
	return roundStatus;
}
//get method: get value
bool Player::getBought() {
	return bought;
}
//get method: get value
int Player::getPrice() {
	return auctionPrice;
}
//get method: get value
PowerPlant Player::getPowerPlant(int n) {
	return powerPlant[n];
}


void Player::setName(string n) {
	name = n;
}

string Player::getName() const{
	return name;
}

// print the data of players
string Player::toString() {
	string print = "Overview card for Player: " + name + "\n->Money: " + to_string(money);
	print += " | coal: " + to_string(coalNum) + " | oil: " + to_string(oilNum) + "  | garbage: " + to_string(garbageNum) + " | uranium: " + to_string(uraniumNum) + "\n";
	print += "->Num of City: " + to_string(numOfCity) + " | Num Of PoweredCity: " + to_string(numOfPoweredCities)+ "\n";
	print += "->Cards:\n";
	for (int i = 0; i < numOfPowerPlant; i++) {
		print += "  " + powerPlant[i].toString()+"\n";
	}
	print += "\n";
	return print;
}

void Player::printPlayerPossession(Player* players, int n){
	for(int i = 0; i<n;i++){
    cout << players[i].toString() << endl;
	}
}

void Player::buyResources(Resources *res) {

	std::cout << "[INFO] " <<name << ", it's your turn now!" << std::endl;
	std::cout << toString();
	std::cout << std::endl;

	std::cout << "[INFO] Here is the Resource Market:" << std::endl;

	for (int i = 0; i < 12; i++) {
		std::cout << res[i].toString() << std::endl;
	}

	int coalMax = 0;
	int oilMax = 0;
	int garbageMax = 0;
	int uraniumMax = 0;
	int hybridMax = 0;

	for (int i = 0; i < numOfPowerPlant; i++) {
		if (powerPlant[i].getTypeName() == "coal") {
			coalMax += powerPlant[i].getNeed() * 2;
		}
		if (powerPlant[i].getTypeName() == "oil") {
			oilMax += powerPlant[i].getNeed() * 2;
		}
		if (powerPlant[i].getTypeName() == "garbage") {
			garbageMax += powerPlant[i].getNeed() * 2;
		}
		if (powerPlant[i].getTypeName() == "uranium") {
			uraniumMax += powerPlant[i].getNeed() * 2;
		}
		if (powerPlant[i].getTypeName() == "hybrid") {
			hybridMax += powerPlant[i].getNeed() * 2;
		}
	}

	while (true)
	{
		//Coal Turn
		while (true)
		{
			int inputNum;
			std::cout << std::endl;
			std::cout << "[PROMPT] How many coal do you want to buy? (Enter 0 to skip) " << std::endl;
			std::cout << "[ENTER] ";
			std::cin >> inputNum;
			std::cout << std::endl;
			if (inputNum == 0) {
				break;
			}
			//Check if Player's inventory is full
			if (inputNum > coalMax + hybridMax - coalNum + ((oilMax - oilNum) < 0 ? (oilMax - oilNum) : 0)) {
				std::cout << "[ERROR] You do not have enough space! Please enter a smaller numeber."<<std::endl;
				continue;
			}

			//Check if Player's Money and Market's inventory is enough
			
			//two temp variable
			int cost = 0;		
			int tempAmount = 0;
			
			for (int i = 0; i < 12; i++) {
				int left = res[i].getCoal();					//left is the resources left in the marketS
				if (left == 0) {
					continue;
				}
				if (left >= inputNum - tempAmount) {
					cost += res[i].getPrice() * (inputNum - tempAmount);
					tempAmount = inputNum;
					break;
				}
				else if (left < inputNum - tempAmount) {
					cost += res[i].getPrice() * left;
					tempAmount += left;
				}
			}

			if (tempAmount < inputNum) {
				std::cout << "[ERROR] Coal is out of stock. Please enter a smaller number!" << std::endl;
				continue;
			}
			if (cost > money) {
				std::cout << "[ERROR] You do not have enough money. Please enter a smaller number!" << std::endl;
				continue;
			}

			//pay money
			money -= cost;

			tempAmount = 0;
			for (int i = 0; i < 12; i++) {

				int left = res[i].getCoal();

				if (left == 0) {
					continue;
				}
				if (left >= inputNum - tempAmount) {
					res[i].setCoal(left - (inputNum - tempAmount));
					break;
				}
				else if (left < inputNum - tempAmount) {
					tempAmount += left;
					res[i].setCoal(0);
				}
			}
			//get resources
			coalNum = inputNum;

			std::cout << "[SUCCESS] " <<inputNum << " coal cost " << cost << " Elektro. You have " << money << " Elektro now." << std::endl;
			
			break;
		}
		
		//Oil Turn
		while (true)
		{
			int inputNum;
			std::cout << std::endl;
			std::cout << "[PROMPT] How many oil do you want to buy? (Enter 0 to skip)"<< std::endl;
			std::cout << "[ENTER] ";
			std::cin >> inputNum;
			std::cout << std::endl;
			if (inputNum == 0) {
				break;
			}
			//Check if Player's inventory is vaild

			if (inputNum > oilMax + hybridMax - oilNum + ((coalMax - coalNum) < 0 ? (coalMax - coalNum) : 0)) {
				std::cout << "[ERROR] You do not have enough space! Please enter a smaller numeber.";
				continue;
			}


			//Check if Player's Money and Market's inventory is enough

			//two temp variable
			int cost = 0;
			int tempAmount = 0;

			for (int i = 0; i < 12; i++) {
				int left = res[i].getOil();
				if (left == 0) {
					continue;
				}
				if (left >= inputNum - tempAmount) {
					cost += res[i].getPrice() * (inputNum - tempAmount);
					tempAmount = inputNum;
					break;
				}
				else if (left < inputNum - tempAmount) {
					cost += res[i].getPrice() * left;
					tempAmount += left;
				}
			}

			if (tempAmount < inputNum) {
				std::cout << "[ERROR] Oil is out of stock. Please enter a smaller number!" << std::endl;
				continue;
			}
			if (cost > money) {
				std::cout << "[ERROR] You do not have enough money. Please enter a smaller number!" << std::endl;
				continue;
			}

			//pay money
			money -= cost;

			tempAmount = 0;
			for (int i = 0; i < 12; i++) {

				int left = res[i].getOil();

				if (left == 0) {
					continue;
				}
				if (left >= inputNum - tempAmount) {
					res[i].setOil(left - (inputNum - tempAmount));
					break;
				}
				else if (left < inputNum - tempAmount) {
					tempAmount += left;
					res[i].setOil(0);
				}
			}
			//get resources
			oilNum = inputNum;

			std::cout << "[SUCCESS]" << inputNum << " oil cost " << cost << " Elektro. You have " << money << " Elektro now." << std::endl;
			break;
		}
		
		//Garbage Turn
		while (true)
		{
			int inputNum;
			std::cout << std::endl;
			std::cout << "[PROMPT] How many garbage do you want to buy? (Enter 0 to skip)" << std::endl;
			std::cout << "[ENTER] ";
			std::cin >> inputNum;
			std::cout << std::endl;
			if (inputNum == 0) {
				break;
			}
			//Check if Player's inventory is vaild

			if (inputNum > garbageMax ) {
				std::cout << "[ERROR] You do not have enough space! Please enter a smaller numeber.";
				continue;
			}


			//Check if Player's Money and Market's inventory is enough

			//two temp variable
			int cost = 0;
			int tempAmount = 0;

			for (int i = 0; i < 12; i++) {
				int left = res[i].getGarbage();
				if (left == 0) {
					continue;
				}
				if (left >= inputNum - tempAmount) {
					cost += res[i].getPrice() * (inputNum - tempAmount);
					tempAmount = inputNum;
					break;
				}
				else if (left < inputNum - tempAmount) {
					cost += res[i].getPrice() * left;
					tempAmount += left;
				}
			}

			if (tempAmount < inputNum) {
				std::cout << "[ERROR] Garbage is out of stock. Please enter a smaller number!" << std::endl;
				continue;
			}
			if (cost > money) {
				std::cout << "[ERROR] You do not have enough money. Please enter a smaller number!" << std::endl;
				continue;
			}

			//pay money
			money -= cost;

			tempAmount = 0;
			for (int i = 0; i < 12; i++) {

				int left = res[i].getGarbage();

				if (left == 0) {
					continue;
				}
				if (left >= inputNum - tempAmount) {
					res[i].setGarbage(left - (inputNum - tempAmount));
					break;
				}
				else if (left < inputNum - tempAmount) {
					tempAmount += left;
					res[i].setGarbage(0);
				}
			}
			//get resources
			garbageNum = inputNum;

			std::cout << "[SUCCESS]" << inputNum << " garbage cost " << cost << " Elektro. You have " << money << " Elektro now." << std::endl;
			break;
		}
		
		//Uranium Turn
		while (true)
		{
			int inputNum;
			std::cout << std::endl;
			std::cout << "[PROMPT] How many uranium do you want to buy? (Enter 0 to skip)" << std::endl;
			std::cout << "[ENTER] ";
			std::cin >> inputNum;
			std::cout << std::endl;
			if (inputNum == 0) {
				break;
			}
			//Check if Player's inventory is vaild

			if (inputNum > uraniumMax) {
				std::cout << "[ERROR] You do not have enough space! Please enter a smaller numeber.";
				continue;
			}


			//Check if Player's Money and Market's inventory is enough

			//two temp variable
			int cost = 0;
			int tempAmount = 0;

			for (int i = 0; i < 12; i++) {
				int left = res[i].getUranium();
				if (left == 0) {
					continue;
				}
				if (left >= inputNum - tempAmount) {
					cost += res[i].getPrice() * (inputNum - tempAmount);
					tempAmount = inputNum;
					break;
				}
				else if (left < inputNum - tempAmount) {
					cost += res[i].getPrice() * left;
					tempAmount += left;
				}
			}

			if (tempAmount < inputNum) {
				std::cout << "[ERROR] Uranium is out of stock. Please enter a smaller number!" << std::endl;
				continue;
			}
			if (cost > money) {
				std::cout << "[ERROR] You do not have enough money. Please enter a smaller number!" << std::endl;
				continue;
			}

			//pay money
			money -= cost;

			tempAmount = 0;
			for (int i = 0; i < 12; i++) {

				int left = res[i].getUranium();

				if (left == 0) {
					continue;
				}
				if (left >= inputNum - tempAmount) {
					res[i].setUranium(left - (inputNum - tempAmount));
					break;
				}
				else if (left < inputNum - tempAmount) {
					tempAmount += left;
					res[i].setUranium(0);
				}
			}
			//get resources
			garbageNum = inputNum;

			std::cout << "[SUCCESS]" << inputNum << " uranium cost " << cost << " Elektro. You have " << money << " Elektro now." << std::endl;
			break;
		}
		break;
	}
}


bool Player::building(Graph* myGameMap, int &step, int numOfPlayer, vector<PowerPlant> &market, vector<PowerPlant> &powerPlants) {

	std::cout << std::endl;
	printGraph(myGameMap);
	std::cout << "[INFO]" << name << ", it's your turn!"<<std::endl;
	bool goToStep3 = false;
	while (true) {
		//check the step
		if (numOfPlayer == 2){
			if (numOfCity ==10){
				if (step == 1) {
					step = 2;
					goToStep3 = adjustMarket(step, market, powerPlants);
				}
			}
		}
		if (numOfPlayer==3||numOfPlayer==4||numOfPlayer==5){
			if(numOfCity==7){
				if (step == 1) {
					step = 2;
					goToStep3 = adjustMarket(step, market, powerPlants);
				}
			}
		}
		if (numOfPlayer==6){
			if(numOfCity==6){
				if (step == 1) {
					step = 2;
					goToStep3 = adjustMarket(step, market, powerPlants);
				}
			}
		}

		std::cout << "[PROMPT]" << "Please enter the ID of the city that you want to build.(Enter -1 to skip)" << std::endl;
		std::cout << "[ENTER] ";
		int inputNum;
		std::cin >> inputNum;
		std::cout << std::endl;
		
		if (inputNum == -1) {
			break;
		}

		vector<string> owners = myGameMap->getArr()[inputNum].getBase()->getOwners();
		size_t size = owners.size();


		//check if the city is on the map
		if (myGameMap->getArr()[inputNum].getHead() == NULL) {
			cout << "[ERROR] This city is not on the map. Please try another city!!\n";
			continue;
		}

		//check if the player have already built one
		bool isBuilt = false;
		for (int i = 0; i < size; i++) {
			if (name == owners[i]) {
				cout << "[ERROR] You have owned this city. Please try another city!!\n";
				isBuilt = true;
				continue;
			}
		}
		if (isBuilt) { continue; }

		//check if there is enough space 
		if (size >= step) {
			std::cout << "[ERROR] You can not build plant in this city because there is no more space!" << std::endl;
			continue;
		}
		
		//check if player has enough money
		size_t price = myGameMap->getArr()[inputNum].getBase()->getPrice(size);
		//add network price
		price += myGameMap->lowestPathPrice(inputNum,name);
		if (money < price){
			std::cout << "[ERROR] You do not have enough money. Please try another city!" << std::endl;
			continue;
		}

		myGameMap->getArr()[inputNum].getBase()->addOwner(name);
		money -= price;
		numOfCity++;
		std::cout << "[SUCCESS] You have built a house in "<< myGameMap->getArr()[inputNum].getBase()->getName() << " successfully." << std::endl;
		std::cout << "[SUCCESS] It cost you  "<< price <<" Elektro. Now you have "<< money<< " Elektro." << std::endl;

	}
	
	printGraph(myGameMap);
	return goToStep3;
}



//add methods
void Player::addNumOfPoweredCities(int c){
	numOfPoweredCities += c;
}


//decrease methods
void Player::deCoalNum(int c){
	coalNum -= c;
}
void Player::deOilNum(int o){
	oilNum -= o;
}
void Player::deGarbageNum(int g){
	garbageNum -= g;
}
void Player::deUraniumNum(int u){
	uraniumNum -= u;
}

bool adjustMarket(int &step, vector<PowerPlant> &market, vector<PowerPlant> &powerPlants) {
	bool goToStep3 = false;
	std::cout << "[INFO] It is STEP 2 now!!" << std::endl;
	std::cout << "[INFO] Remove first card in the market!" << std::endl;
	market.erase(market.begin());						//remove first card in market
	std::cout << "[INFO] Add a new card to the market!" << std::endl;
	if (powerPlants[0].getType() == PowerPlant::step3) {
		std::cout << "[INFO] Find STEP 3 Card. Shuffle the deck." << std::endl;
		std::cout << "[INFO] STEP 3 starts in phase 5!!" << std::endl;
		powerPlants.erase(powerPlants.begin());
		PowerPlant::shuffle(powerPlants);
		bool goToStep3 = true;
	}
	else {
		market.push_back(powerPlants[0]);
		powerPlants.erase(powerPlants.begin());
	}
	
	std::cout << "[INFO] Reorder the cards in the market!" << std::endl;
	PowerPlant::setMarketOrder(market);					//reorder
	return goToStep3;
}