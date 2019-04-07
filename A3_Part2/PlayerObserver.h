#pragma once
#include "Observer.h"
#include "Player.h"

class PlayerObserver :	public Observer
{
private:
	Player* subject;
public:
	PlayerObserver();
	PlayerObserver(Player* player);
	~PlayerObserver();
	void update();
};

