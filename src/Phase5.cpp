
#include "Phase5.h"
#include "Player.h"
#include "Money.h"
#include "Resources.h"
#include "PowerPlant.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;


int payment[21] = {10, 22, 33, 44, 54, 64, 73, 82, 90, 98, 105, 112, 118, 124, 129, 134, 138, 142, 145, 148,
                   150};     //payment corresponding to the number of powered cities
Resources recycle;

//every player indicates how many cities in his network he wishes
//(and is able) to supply with electricity. He earns cash based on the number of cities
//he powers as shown on the payment table
void earnCash(Player* players, int numOfPlayer) {
    string yesInput;
    int earnedCash, money;
    for (int i = 0; i < numOfPlayer; i++) {
        int numOfPowerPlant = players[i].getNumOfPowerPlant();
        int totalNumInput=0;
        for (int j = 0; j < numOfPowerPlant; j++) {
            PowerPlant currentPlant = players[i].getPowerPlant(j);
            cout << "[PROMPT] Player " << (i + 1)
                 << ": Do you wish to supply cities with electricity by using power plant "
                 << currentPlant.getNumber() << " ?" << endl;
            do {
                cin >> yesInput;
                if (yesInput == "Y" || yesInput == "y") {
                    if (validUsingPowerPlant(players, i, currentPlant)) {
                        totalNumInput += currentPlant.getSupplyCity();
                        break;
                    }
                } else
                    break;
            } while (true);

            if (totalNumInput > players[i].getNumOfCity())
                totalNumInput = players[i].getNumOfCity();
        }

        players[i].addNumOfPoweredCities(totalNumInput);

        earnedCash = payment[totalNumInput];
        money = players[i].getMoney() + earnedCash;
        players[i].setMoney(money);
        cout << "[SUCCESS] You have supplied " << totalNumInput << " city/cities this round." << endl;
        cout << "[INFO] You have earned "<< earnedCash<< " this round."<< endl;
        cout << "[INFO] Now you have "<<players[i].getNumOfPoweredCities()<<" city/cities that have been powered.\n"<< endl;
    }
}

//return true if the input is valid for the number of cities the player wants to power
bool validUsingPowerPlant(Player* players, int i, PowerPlant currentPlant) {
    PowerPlant::Type type = currentPlant.getType();
    int needNum = currentPlant.getNeed();
    if (type == PowerPlant::hybrid) {
        int numCoalHybrid, numOilHybrid;
        do {
            do{
                cout << "\n[PROMPT] Please enter the coal that you want to use to power the power plant:" << endl;
                cout << "-> ";
                if(!cin){
                    cout << "[ERROR] Invalid input";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }while(!(cin >> numCoalHybrid));

            do{
                cout << "\n[PROMPT] Please enter the oil that you want to use to power the power plant:" << endl;
                cout << "-> ";
                if(!cin){
                    cout << "[ERROR] Invalid input";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }while(!(cin >> numOilHybrid));
        } while (numCoalHybrid + numOilHybrid != currentPlant.getNeed());
        recycle.addCoal(numCoalHybrid);
        players[i].deCoalNum(numCoalHybrid);
        recycle.addOil(numOilHybrid);
        players[i].deOilNum(numOilHybrid);
    }
    switch (type) {
        case PowerPlant::coal:
            if (players[i].getCoalNum() >= needNum) {
                recycle.addCoal(needNum);
                players[i].deCoalNum(needNum);
                return true;
            } else
                cout << "[ERROR] You can not power cities by using power plant "<< currentPlant.getNumber()<<
                " because you do not have enough coals." << endl;
            return false;
        case PowerPlant::oil:
            if (players[i].getOilNum() >= currentPlant.getNeed()) {
                recycle.addOil(needNum);
                players[i].deOilNum(needNum);
                return true;
            } else
                cout << "[ERROR] You can not power cities by using power plant "<< currentPlant.getNumber()<<
                     " because you do not have enough oil." << endl;
            return false;
        case PowerPlant::garbage:
            if (players[i].getGarbageNum() >= currentPlant.getNeed()) {
                recycle.addGarbage(needNum);
                players[i].deGarbageNum(needNum);
                return true;
            } else
                cout << "[ERROR] You can not power cities by using power plant "<< currentPlant.getNumber()<<
                     " because you do not have enough garbage." << endl;
            return false;
        case PowerPlant::uranium:
            if (players[i].getUraniumNum() >= currentPlant.getNeed()) {
                recycle.addUranium(needNum);
                players[i].deUraniumNum(needNum);
                return true;
            } else
                cout << "[ERROR] You can not power cities by using power plant "<< currentPlant.getNumber()<<
                     " because you do not have enough uranium." << endl;
            return false;
        default:
            return true;
    }
}

void reSupplyResource(int step, int numOfPlayer, Resources *array_resource) {

    //Based on the number of players and the step of the game, the players re-supply the resource market (see table at the back of the rules) from the supply of resources
    Resources table;
    switch (numOfPlayer) {
        case 2:
            switch (step) {
                case 1:
                    table = Resources(3, 2, 1, 1, 0);
                    break;
                case 2:
                    table = Resources(4, 2, 2, 1, 0);
                    break;
                case 3:
                    table = Resources(3, 4, 3, 1, 0);
                    break;
            }
            break;
        case 3:
            switch (step) {
                case 1:
                    table = Resources(4, 2, 1, 1, 0);
                    break;
                case 2:
                    table = Resources(5, 3, 2, 1, 0);
                    break;
                case 3:
                    table = Resources(3, 4, 3, 1, 0);
                    break;
            }
            break;
        case 4:
            switch (step) {
                case 1:
                    table = Resources(5, 3, 2, 1, 0);
                    break;
                case 2:
                    table = Resources(6, 4, 3, 2, 0);
                    break;
                case 3:
                    table = Resources(4, 5, 4, 2, 0);
                    break;
            }
            break;
        case 5:
            switch (step) {
                case 1:
                    table = Resources(5, 4, 3, 2, 0);
                    break;
                case 2:
                    table = Resources(7, 5, 3, 3, 0);
                    break;
                case 3:
                    table = Resources(5, 6, 5, 2, 0);
                    break;
            }
            break;
        case 6:
            switch (step) {
                case 1:
                    table = Resources(7, 5, 3, 2, 0);
                    break;
                case 2:
                    table = Resources(9, 6, 5, 3, 0);
                    break;
                case 3:
                    table = Resources(6, 7, 6, 3, 0);
                    break;
            }
            break;
    }


    //change the number of resources that will be supplied according to the available in the game
    // (if the players store too many resources in their power plants, the resource is not fully re-supplied! The resource tokens in the game are limited.)
    Resources toSupply;
    if (recycle.getCoal() >= table.getCoal()) {
        recycle.setCoal(recycle.getCoal() - table.getCoal());
        toSupply.setCoal(table.getCoal());
    } else {
        toSupply.setCoal(recycle.getCoal());
        recycle.setCoal(0);
    }

    if (recycle.getOil() >= table.getOil()) {
        recycle.setOil(recycle.getOil() - table.getOil());
        toSupply.setOil(table.getOil());
    } else {
        toSupply.setOil(recycle.getOil());
        recycle.setOil(0);
    }

    if (recycle.getGarbage() >= table.getGarbage()) {
        recycle.setGarbage(recycle.getGarbage() - table.getGarbage());
        toSupply.setGarbage(table.getGarbage());
    } else {
        toSupply.setGarbage(recycle.getGarbage());
        recycle.setGarbage(0);
    }

    if (recycle.getUranium() >= table.getUranium()) {
        recycle.setUranium(recycle.getUranium() - table.getUranium());
        toSupply.setUranium(table.getUranium());
    } else {
        toSupply.setUranium(recycle.getUranium());
        recycle.setUranium(0);
    }

    //print the resources that will be supplied to the market
    int numOfCoalToSupply = toSupply.getCoal();
    int numOfOilToSupply = toSupply.getOil();
    int numOfGarbageToSupply = toSupply.getGarbage();
    int numOfUraniumToSupply = toSupply.getUranium();
    cout << "[INFO] To be re-supplied in step " << step << " for coal: " << numOfCoalToSupply << endl;
    cout << "[INFO] To be re-supplied in step " << step << " for oil: " << numOfOilToSupply << endl;
    cout << "[INFO] To be re-supplied in step " << step << " for garbage: " << numOfGarbageToSupply << endl;
    cout << "[INFO] To be re-supplied in step " << step << " for uranium: " << numOfUraniumToSupply << endl;

    //re-supply the uranium
    for (int i = 11; i >= 0; i--) {
        if (numOfUraniumToSupply > 0) {
            if (array_resource[i].getUranium() == 1)
                continue;
            else {
                if (array_resource[i].getUranium() == 0) {
                    array_resource[i].setUranium(1);
                    numOfUraniumToSupply--;
                }
            }
        }
    }


    for (int i = 7; i >= 0; i--) {
        //re-supply the coal
        if (numOfCoalToSupply > 0) {
            switch (array_resource[i].getCoal()) {
                case 3:
                    break;
                case 2: {
                    numOfCoalToSupply--;
                    array_resource[i].setCoal(3);
                    break;
                }
                case 1: {
                    int spaceCoalTemp = numOfCoalToSupply - 2;
                    if (spaceCoalTemp >= 0) {
                        array_resource[i].setCoal(3);
                        numOfCoalToSupply -= 2;
                    } else {
                        array_resource[i].setCoal(2);
                        numOfCoalToSupply--;
                    }
                    break;
                }
                case 0: {
                    int spaceCoalTemp = numOfCoalToSupply - 3;
                    if (spaceCoalTemp >= 0) {
                        array_resource[i].setCoal(3);
                        numOfCoalToSupply -= 3;
                    } else {
                        array_resource[i].setCoal(numOfCoalToSupply);
                        numOfCoalToSupply = 0;
                    }
                    break;
                }
            }
        }

        //re-supply the oil
        if (numOfOilToSupply > 0) {
            switch (array_resource[i].getOil()) {
                case 3:
                    break;
                case 2: {
                    numOfOilToSupply--;
                    array_resource[i].setOil(3);
                    break;
                }
                case 1: {
                    int spaceOilTemp = numOfOilToSupply - 2;
                    if (spaceOilTemp >= 0) {
                        array_resource[i].setOil(3);
                        numOfOilToSupply -= 2;
                    } else {
                        array_resource[i].setOil(2);
                        numOfOilToSupply--;
                    }
                    break;
                }
                case 0: {
                    int spaceOilTemp = numOfOilToSupply - 3;
                    if (spaceOilTemp >= 0) {
                        array_resource[i].setOil(3);
                        numOfOilToSupply -= 3;
                    } else {
                        array_resource[i].setOil(numOfOilToSupply);
                        numOfOilToSupply = 0;
                    }
                    break;
                }
            }
        }

        //re-supply the garbage
        if (numOfGarbageToSupply > 0) {
            switch (array_resource[i].getGarbage()) {
                case 3:
                    break;
                case 2: {
                    numOfGarbageToSupply--;
                    array_resource[i].setGarbage(3);
                    break;
                }
                case 1: {
                    int spaceGarbageTemp = numOfGarbageToSupply - 2;
                    if (spaceGarbageTemp >= 0) {
                        array_resource[i].setGarbage(3);
                        numOfGarbageToSupply -= 2;
                    } else {
                        array_resource[i].setGarbage(2);
                        numOfGarbageToSupply--;
                    }
                    break;
                }
                case 0: {
                    int spaceGarbageTemp = numOfGarbageToSupply - 3;
                    if (spaceGarbageTemp >= 0) {
                        array_resource[i].setGarbage(3);
                        numOfGarbageToSupply -= 3;
                    } else {
                        array_resource[i].setGarbage(numOfGarbageToSupply);
                        numOfGarbageToSupply = 0;
                    }
                    break;
                }
            }
        }


    }
}

//Place the highest numbered power plant from the future market face down under the draw stack and draw a new one to replace it
void updateMarket(int step, std::vector<PowerPlant> &powerPlants, std::vector<PowerPlant> &market) {
	//If the »Step 3« card is drawn in phase 5 (Bureaucracy),
	//remove this card and the lowest numbered power plant from the game and do not draw replacements
	PowerPlant theFirstInDrawStack = powerPlants.front();
	if (theFirstInDrawStack.getTypeName() == "step3") {
        cout <<"[INFO] It is STEP 3 Card !!" <<endl;
		market.erase(market.begin());
		PowerPlant::setMarketOrder(market);
		powerPlants.erase(powerPlants.begin());
		step = 3;
		PowerPlant::shuffle(powerPlants);
	}
	else {
		PowerPlant theHighest = market.back();
		market.pop_back();
		market.push_back(powerPlants.front());
		powerPlants.push_back(theHighest);
		powerPlants.erase(powerPlants.begin());
	}
}





