//
// Created by Tyler on 2019-04-09.
//

#include "GameObserver.h"

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

void GameObserver::updatePositionInfo(){
    cout<<"Here is the Position of Players:"<<endl;
    for (int j = 0 ;j<m_game->numOfPlayer;j++){
        cout<<"[" << (j+1) <<"] --> "<< m_game->players[j].getName()<<endl;
    }
}

void GameObserver::updatePlayerInfo(){
    for(int i = 0 ;i<m_game->numOfPlayer;i++){
        cout<< m_game->players[i].toString()<<endl;
    }
}