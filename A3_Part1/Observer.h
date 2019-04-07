#pragma once
class Observer
{	
protected:
	Observer();
public:
	virtual void updateHeader() = 0;
	~Observer();
};

