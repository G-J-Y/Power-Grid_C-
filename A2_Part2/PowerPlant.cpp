#include "PowerPlant.h"
#include <time.h>
#include <iostream>
#include <string>
using namespace std;

PowerPlant::PowerPlant() {
	number = 0;
	need = 0;
	type = PowerPlant::unknown;
	supplyCity =0;
}


PowerPlant::PowerPlant(int n, int s, Type t, int c) {
	number = n;
	need = s;
	type = t;
	supplyCity = c;
}
//set method: change value
void PowerPlant::setNumber(int n) {
	number = n;
}
//get method: get value
int PowerPlant::getNeed(){
	return need;
}
//get method: get value
int PowerPlant::getNumber() {
	return number;
}
//get method: get value
int PowerPlant::getSupplyCity() {
	return supplyCity;
}

//get method: get value
PowerPlant::Type PowerPlant::getType() {
	return type;
}

//get method: get value
string PowerPlant::getTypeName() {

	switch (type)
	{
		case 0:
			return "coal";
	
		case 1:
			return "oil";

		case 2:
			return "garbage";
	
		case 3:
			return "uranium";

		case 4:
			return "hybrid";
	
		case 5:
			return "eco";
	
		case 6:
			return "step3";

		default:
			return "Unknown";
	}
}
//change the order of power plant cards
//void PowerPlant::shuffle(PowerPlant array[], int length) {
//	int value;
//	PowerPlant temp;
//
//	if (array == NULL || length == 0)
//		return;
//	//change the random number
//	srand((unsigned)time(NULL));
//	for (int i = 0; i < length; i++) {
//	//create a random number
//		value = rand() % length;
//		//shuffle
//		temp = array[i];
//		array[i] = array[value];
//		array[value] = temp;
//	}
//	
//}


void PowerPlant::shuffle(vector<PowerPlant> &pp) {
	int value;
	PowerPlant temp;

	if (pp.empty())
		return;
	//change the random number
	srand((unsigned)time(NULL));
	for (int i = 0; i < pp.size(); i++) {
		//create a random number
		value = rand() % pp.size();
		//shuffle
		temp = pp[i];
		pp[i] = pp[value];
		pp[value] = temp;
	}

}
//output the information

string PowerPlant::toString() {
	string print = "Card "+to_string(number) + "\t| " + "Need "+ to_string(need) + " | " + this->getTypeName() +" | "+"Supply "+ to_string(supplyCity)+" city/cities";
	return print;
}