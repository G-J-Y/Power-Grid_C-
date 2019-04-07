#pragma once
#include "Observer.h"
#include "Game.h"

class GameObserver :public Observer
{
private:
	Game *m_game;
public:
	GameObserver();
	GameObserver(Game* g);
	~GameObserver();
	void updateStep();
	void updateTurn();
	void updatePlayer();
	void updatePhase();
	void updateHeader();
	
};

