#ifndef PROJECT_PHASE5_H
#define PROJECT_PHASE5_H

#include "Player.h"
#include "Resources.h"
#include <vector>


class Phase5 {
private:
    Player *players;    //player array
    int numOfPlayer;    //the size of player
    int step;   ///
    //int turn;
    int payment[21] = {10, 22, 33, 44, 54, 64, 73, 82, 90, 98, 105, 112, 118, 124, 129, 134, 138, 142, 145, 148,
                       150};     //payment corresponding to the number of powered cities
    Resources recycle;


public:
    Phase5();

    Phase5(Player *, int);

    void earnCash();                    //the players earn cash
    bool validUsingPowerPlant(int,
                              PowerPlant);    //return true if the input is valid for the number of cities the player wants to power
    void reSupplyResource(
            Resources *);  //Based on the number of players and the step of the game, the players re-supply the resource market from the supply of resources.
    void updateMarket(std::vector<PowerPlant> &,
                      std::vector<PowerPlant> &);//Place the highest numbered power plant from the future market face down under the draw stack and draw a new one to replace it. Rearrange the market appropriately.
};


#endif //PROJECT_PHASE5_H
