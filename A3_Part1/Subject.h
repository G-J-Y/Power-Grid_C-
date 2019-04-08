#pragma once
#include <list>
#include "Observer.h"
//class Observer;
class Subject
{
private:
	std::list<Observer*> *_observers;
public:
	Subject();
	~Subject();
	virtual void attach(Observer *o);
	virtual void detach(Observer *o);
	virtual void notifyStep();
	virtual void notifyTurn();
	virtual void notifyPhase();
	virtual void notifyPlayer();
	virtual void notifyHeader();
	
};

