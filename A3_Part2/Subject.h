#pragma once
#include <list>
#include "Observer.h"
class Subject
{
protected:
	std::list<Observer*> *_observers;
public:
	Subject();
	~Subject();
	virtual void attach(Observer *o);
	virtual void detach(Observer *o);
	//virtual void notify();
    virtual void notifyPositionInfo() =0;

    virtual void notifyPlayerInfo() =0;
};

