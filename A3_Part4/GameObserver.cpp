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

void GameObserver::update(){
    cout<<"====================Game Static Observer======================="<<endl;
    for(int i = 0 ;i<m_game->numOfPlayer;i++){
        cout<<"[" << (i+1) <<"] --> "<< m_game->players[i].getName()<<endl;
        cout<< m_game->players[i].toString()<<endl;
    }
    cout<<"===================End Game Static Observer===================="<<endl;
}