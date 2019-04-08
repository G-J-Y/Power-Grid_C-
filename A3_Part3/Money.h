//
// Created by Tyler on 2019-02-28.
//

#ifndef PROJECT345_MONEY_H
#define PROJECT345_MONEY_H

#include <iostream>

class Money {

private:
    int m_value;

public:
	//default constructor
    Money();

    explicit Money(const int &value);

    void printInfo();
};


#endif //PROJECT345_MONEY_H
