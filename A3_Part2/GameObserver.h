//
// Created by Tyler on 2019-04-09.
//

#ifndef INC_345PROJECT_GAMEOBSERVER_H
#define INC_345PROJECT_GAMEOBSERVER_H
#include "Observer.h"
#include "Game.h"

class GameObserver : public Observer {
private:
    Game *m_game;
public:
    GameObserver();
    GameObserver(Game* g);
    ~GameObserver();
    void updatePositionInfo();
    void updatePlayerInfo();
};


#endif //INC_345PROJECT_GAMEOBSERVER_H
