#ifndef PROJECT_PHASE5_H
#define PROJECT_PHASE5_H

#include "Player.h"
#include "Resources.h"
#include <vector>




//    Player *players;    //player array
 //   int numOfPlayer;    //the size of player
  //  int step;   ///
    //int turn;




    void earnCash(Player*, int);                    //the players earn cash
    bool validUsingPowerPlant(Player*, int, PowerPlant);    //return true if the input is valid for the number of cities the player wants to power
    void reSupplyResource(int, int, Resources *);  //Based on the number of players and the step of the game, the players re-supply the resource market from the supply of resources.
    void updateMarket(int, std::vector<PowerPlant> &, std::vector<PowerPlant> &);//Place the highest numbered power plant from the future market face down under the draw stack and draw a new one to replace it. Rearrange the market appropriately.



#endif //PROJECT_PHASE5_H
