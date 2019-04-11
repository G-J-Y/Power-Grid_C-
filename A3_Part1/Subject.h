#pragma once
#include "Observer.h"
#include <list>

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
	virtual void notify();
	/*virtual void notifyStep();
	virtual void notifyTurn();
	virtual void notifyPhase();
	virtual void notifyPlayer();
	virtual void notifyHeader();
	virtual void notifyAuctionResult(Player p, PowerPlant card);
	virtual void notifyOnePlayerTurn(Player p);*/
};

