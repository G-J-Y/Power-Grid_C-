#include "GameObserver.h"
//#include "Game.h"
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

void GameObserver::update() {
	int turn = m_game->getTurn();
	int step = m_game->getStep();
	int phase = m_game->getPhase();
	Player player = m_game->getCurrentPlayer();
	if (player.getName() == "") {
		cout << "-------------------- Step " << step << " ---------------------" << endl;
		cout << "-------------------- Turn " << turn << " ---------------------" << endl;
		cout << "-------------------- Phase " << phase << " --------------------" << endl;
		if (phase == 1) {
			cout << "Determine Player Order" << endl;
		}
		if (phase == 2) {
			cout << "Auction Process, player can buy a power Plant card in this phase" << endl;
		}
		if (phase == 3) {
			cout << "Buying Resources, where the players can buy resources for their power plants from the resource market" << endl;
		}
		if (phase == 4) {
			cout << "Building, where the players start or add cities to their networks on the map" << endl;
		}
		if (phase == 5) {
			cout << "Bureaucracy, where the players earn cash, re-supply the resource market, and remove a power plant from the power plant market, replacing it with a new one from the stack" << endl;
		}
	}
	else {
		cout << "It's player \"" << player.getName() << "\" turn" << endl;
	}

	cout << endl;
}

//void GameObserver::updateStep() {
//	int m_step = m_game->getStep();
//	cout << "-------------------- Step " << m_step << " ---------------------" << endl;
//}
//
//void GameObserver::updateTurn() {
//	int m_turn = m_game->getTurn();
//	cout << "-------------------- Turn " << m_turn << " ---------------------" << endl;
//}                                   
//
//void GameObserver::updatePhase() {
//	int m_phase = m_game->getPhase();
//	cout << "-------------------- Phase " << m_phase << " --------------------" << endl;
//}
//
//void GameObserver::updatePlayer() {
//	Player *m_player = m_game->getPlayers();\
//	cout << "------------------- Players --------------------" << endl;
//	for (int i = 0; i < m_game->getNumOfPlayers(); i++) {
//		cout << (m_player+i)->toString() << endl;
//	}
//}
//
//void GameObserver::updateHeader() {
//	int m_phase = m_game->getPhase();
//	updateStep();
//	updateTurn();
//	updatePlayer();
//	cout << endl;
//	
//}
//
//void GameObserver::updateAuctionResult(Player p, PowerPlant card) {
//	cout << "Congratulation! " << p.getName() << " get: " << card.toString() << endl;
//	//cout << card.toString() << endl;
//	cout << endl;
//}
//
//void GameObserver::updateOnePlayerTurn(Player p) {
//	cout << "It's player \"" << p.getName() << "\" turn" << endl;
//	cout << endl;
//}