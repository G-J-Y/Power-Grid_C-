//
// Created by Tyler on 2019-02-28.
//

#include "Money.h"

Money::Money() {};
Money::Money(const int &value): m_value(value){};

void Money::printInfo(){
    std::cout<<"Money of value "<< m_value<<" Elektro(s) has been loaded."<< std::endl;
}