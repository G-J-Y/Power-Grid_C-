#ifndef PLAYER_H_
#define PLAYER_H_
#include <string>
#include "PowerPlant.h"
using namespace std;

class Player {
private:
	//basic data
	int money;
	int numOfCity;
	int numOfPowerPlant;
	int numOfPoweredCities;
	PowerPlant powerPlant[3];
	//Resources
	int coalNum;
	int oilNum;
	int garbageNum;
	int uraniumNum;
	//status of auction
	bool auction;
	int auctionPrice;

public:
	Player();
	//set methods
	void setMoney(int m);
	void setNumOfCity(int c);
	void setNumOfPowerPlant(int p);
	void setNumOfPoweredCities(int pc);
	void setCoalNum(int c);
	void setOilNum(int o);
	void setGarbageNum(int g);
	void setUraniumNum(int u);
	void setAuction(bool);
	void setPrice(int);
	void setPowerPlant(PowerPlant p,int n);
	//get methods
	int getMoney(void);
	int getNumOfCity(void);
	int getNumOfPowerPlant(void);
	int getNumOfPoweredCities();
	int getCoalNum(void);
	int getOilNum(void);
	int getGarbageNum(void);
	int getUraniumNum(void);
	bool getAuction();
	int getPrice();
	PowerPlant getPowerPlant(int n);
	//print information
	string toString();
};

#endif // !PLAYER_H__H_
#pragma once

