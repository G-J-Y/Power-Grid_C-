#ifndef PHASE1_2_H_
#define PHASE1_2_H_

#include "Resources.h"
#include "PowerPlant.h"
#include "Player.h"
#include <time.h>
#include <vector>
#include <iostream>


//static variable
 static int currentAuctionPrice = 0;
//static int numberOfPlayers;
//static int turn = 1;
//static int step = 1;
 static int indexOfCard = 0 ;
 static PowerPlant currentPowerPlant;


void shufflePlayers(Player array[], int length);

void setPlayerOrder(Player p[], int n);

void setMarketOrder(vector<PowerPlant> &p);

void setCardOwnedByPlayer(Player &p);

void checkReturnResources(Player &p);

void buyCard(Player &p, PowerPlant card);

bool checkNoOneBuyCard(Player p[],int n);

void changeMarketToStep3(vector<PowerPlant> &p);

void abilityOfPurchase(vector<PowerPlant> m, int c,int step);

void pass(Player &p);

void auction(Player &p, PowerPlant n);

void auctionPhase(Player p[], vector<PowerPlant> &, vector<PowerPlant> &, int numberOfPlayers,int step,int turn);


#endif // !PHASE1_2_H__H_
#pragma once