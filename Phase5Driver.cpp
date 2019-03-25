#include "Phase5.h"
#include "Player.h"
#include "Money.h"
#include "Resources.h"


#include <iostream>

using std::cout;
using std::endl;

int main() {

    //test Phase 5 Bureaucracy
	//Initialize 4 players
    Player * players = new Player[4];
    players[0] = Player();
    players[1] = Player();
    players[2] = Player();
    players[3] = Player();

    //set player1:  owns 6 cities, 0 Elektro, 4 coal, 6 oil, 2 garbage, the power plants 06, 07 and 10
    players[0].setMoney(0);
    players[0].setNumOfCity(6);
    players[0].setNumOfPowerPlant(3);
    players[0].setPowerPlant(PowerPlant(6, 1, PowerPlant::garbage, 1),0);
    players[0].setPowerPlant(PowerPlant(7, 3, PowerPlant::oil, 2),1);
    players[0].setPowerPlant(PowerPlant(10, 2, PowerPlant::coal, 2),2);
    players[0].setCoalNum(4);
    players[0].setOilNum(6);
    players[0].setGarbageNum(2);

    //set player2:  owns 3 cities, 2 Elektro, 2 coal, 2 oil, 2 uranium, the power plants 05 and 11
    players[1].setMoney(2);
    players[1].setNumOfCity(3);
    players[1].setNumOfPowerPlant(2);
    players[1].setPowerPlant(PowerPlant(5, 2, PowerPlant::hybrid, 1),0);
    players[1].setPowerPlant(PowerPlant(11, 1, PowerPlant::uranium, 2),1);
    players[1].setCoalNum(2);
    players[1].setOilNum(2);
    players[1].setUraniumNum(2);

    //set player3:  owns 0 cities, 3 Elektro, 2 garbage, the power plants 06
    players[2].setMoney(3);
    players[2].setNumOfCity(1);
    players[2].setNumOfPowerPlant(1);
    players[2].setPowerPlant(PowerPlant(16, 2, PowerPlant::oil, 3),0);
    players[2].setOilNum(2);

    //set player4:  owns 2 cities, 4 Elektro, 1 coal, the power plants 15
    players[3].setMoney(4);
    players[3].setNumOfCity(2);
    players[3].setNumOfPowerPlant(1);
    players[3].setPowerPlant(PowerPlant(15, 2, PowerPlant::coal, 3),0);
    players[3].setCoalNum(1);


    //Initialize resources on the map
    //test for re-supply the resource market:  10 coal, 2 oil, and 1 garbage were brought by players
    Resources *array_resource = new Resources[12];
    array_resource[0] = Resources(0, 0, 0, 0, 1);
    array_resource[1] = Resources(0, 0, 0, 0, 2);
    array_resource[2] = Resources(0, 1, 0, 0, 3);
    array_resource[3] = Resources(2, 3, 0, 0, 4);
    array_resource[4] = Resources(3, 3, 0, 0, 5);
    array_resource[5] = Resources(3, 3, 0, 0, 6);
    array_resource[6] = Resources(3, 3, 2, 0, 7);
    array_resource[7] = Resources(3, 3, 3, 0, 8);
    array_resource[8] = Resources(0, 0, 0, 0, 10);
    array_resource[9] = Resources(0, 0, 0, 0, 12);
    array_resource[10] = Resources(0, 0, 0, 1, 14);
    array_resource[11] = Resources(0, 0, 0, 1, 16);


    //create 43 powerPlants cards
    std::vector<PowerPlant> powerPlants(43);
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

    //create Market
    std::vector<PowerPlant> market(0);

    //put first 8 cards into market
    for (int i = 0; i < 8; i++) {
        market.push_back(powerPlants[0]);
        powerPlants.erase(powerPlants.begin());
    }



    //phase 5 begins
    Phase5 phase5 = Phase5(players, 4);
    phase5.earnCash();


    //print each player possession
    for (int i = 0; i < 4; i++) {
        cout << "Player " << i+1 << ": \n" << players[i].toString() << "\n";
    }
    cout << endl;
    cout << "-------------------------------" << endl;

    /**/

    //print the resources in the market before re-supply
    for (int i = 0; i < 12; i++) {
        cout << array_resource[i].toString() << endl;
    }
    cout << "-------------------------------" << endl;

    //re-supply the resource market
    phase5.reSupplyResource(array_resource);

    //print the resources after re-supply
    cout << "-------------------------------" << endl;
    for (int i = 0; i < 12; i++) {
        cout << array_resource[i].toString() << endl;
    }

    /**/

    //update the power plant market
    phase5.updateMarket(powerPlants, market);
    //PowerPlant::shuffle(powerPlants, 8);

    //print the power plant market and the draw stack
    cout << "-------------------------------" << endl;
    for(int i=0; i<8; i++){
        cout << market[i].toString() << endl;
    }
    cout << "-------------------------------" << endl;
    for (int i = 0; i < 35; i++) {
        cout << powerPlants[i].toString() << endl;
    }

    /**/

    //release memory
    delete[] array_resource;
    delete[] players;

    return 0;
}
