#pragma once
class Observer
{	
protected:
	Observer();
public:

	~Observer();

	//update();
    virtual void updatePositionInfo()=0;

    virtual void updatePlayerInfo()=0;
};

