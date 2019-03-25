//
// Created by Tyler on 2019-02-28.
//

#include "Money.h"

Money::Money() {};
Money::Money(const int &value): m_value(value){};

void Money::printInfo(){
    std::cout<<"This is "<< m_value<<" Elektro"<< std::endl;
}