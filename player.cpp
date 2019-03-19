#include <iostream>
#include "Player.h"
#include <string>
using namespace std;

// default 
Player::Player() {
	money = 0;
	numOfCity = 0;
	numOfPowerPlant = 0;
	powerPlant[3];
	coalNum = 0;
	oilNum = 0;
	garbageNum = 0;
	uraniumNum = 0;
	auction = true;
	auctionPrice = 0;
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
void Player::setNumOgPowerPlant(int p) {
	numOfPowerPlant = p;
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
void Player::setPrice(int p) {
	auction = p;
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
int Player::getNumOgPowerPlant(void) {
	return numOfPowerPlant;
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
int Player::getPrice() {
	return auctionPrice;
}
//get method: get value
PowerPlant Player::getPowerPlant(int n) {
	return powerPlant[n];
}
// print the data of players
string Player::toString() {
	string print = "Money: " + to_string(money) + "\n" + "Number of city: "+ to_string(numOfCity)+"\n";
	return print;
}



