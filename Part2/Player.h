#ifndef PLAYER_H_
#define PLAYER_H_
#include <string>
#include "PowerPlant.h"
#include "Resources.h"
#include "mapLoader.h"

using namespace std;

class Player {
private:
	//basic data
	string name;
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
    bool roundStatus;
    bool auction;
    bool bought;
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
	void setName(string);
    void setRoundStatus(bool);
    void setBought(bool);
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
	string getName() const;
    bool getRoundStatus();
    bool getBought();
	PowerPlant getPowerPlant(int n);

	//decrease methods
	void deCoalNum(int c);
	void deOilNum(int o);
	void deGarbageNum(int g);
	void deUraniumNum(int u);


	//print information
	string toString();
	void buyResources(Resources *res);
	void building(Graph* graph, int step);

};

#endif // !PLAYER_H__H_
#pragma once

