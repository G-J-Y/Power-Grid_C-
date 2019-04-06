#pragma once
class Observer
{	
protected:
	Observer();
public:
	virtual void update() = 0;
	~Observer();
};

