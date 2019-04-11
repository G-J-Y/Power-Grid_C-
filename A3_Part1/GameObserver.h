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
	void update();
	/*void updateStep();
	void updateTurn();
	void updatePlayer();
	void updatePhase();
	void updateHeader();
	void updateAuctionResult(Player p, PowerPlant card);
	void updateOnePlayerTurn(Player p);*/
	
};

