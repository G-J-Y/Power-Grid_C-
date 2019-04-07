#include "GameObserver.h"
#include "Game.h"
#include <iostream>
using namespace std;

GameObserver::GameObserver()
{
}

GameObserver::GameObserver(Game* g) {
	m_game = g;
	m_game->attach(this);
}

GameObserver::~GameObserver()
{
	m_game->detach(this);
}

void GameObserver::updateStep() {
	int m_step = m_game->getStep();
	cout << "---------- Step " << m_step << " ----------" << endl;
}

void GameObserver::updateTurn() {
	int m_turn = m_game->getTurn();
	cout << "---------- Round " << m_turn << " ----------" << endl;
}                                   

void GameObserver::updatePhase() {
	int m_phase = m_game->getPhase();
	cout << "---------- Phase " << m_phase << " ----------" << endl;
}

void GameObserver::updatePlayer() {
	Player *m_player = m_game->getPlayers();\
	cout << "---------- Players ----------" << endl;
	for (int i = 0; i < m_game->getNumOfPlayers(); i++) {
		cout << m_player->toString() << endl;
	}
}

void GameObserver::updateHeader() {
	int m_phase = m_game->getPhase();
	updateStep();
	updateTurn();
	updatePlayer();
	cout << endl;
	
}