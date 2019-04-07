#include "PlayerObserver.h"



PlayerObserver::PlayerObserver(){}

PlayerObserver::PlayerObserver(Player* player)
{
    subject = player;
    subject->attach(this);
}

PlayerObserver::~PlayerObserver()
{
    delete subject;
}

void PlayerObserver::update(){
    cout<<subject->toString()<<endl;
}
