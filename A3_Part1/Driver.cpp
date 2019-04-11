#include "Game.h"
#include"GameObserver.h"
int main() {

	Game *myGame = new Game(3);
	GameObserver *gameObserver = new GameObserver(myGame);
	myGame->loader();
	while(true){
		myGame->phase1();
		myGame->phase2();
		myGame->phase3();
		myGame->phase4();
		if(myGame->checkWin()) break;
		myGame->phase5();
	}
	
	delete gameObserver;
	delete myGame;
	system("pause");
	return 0;
}