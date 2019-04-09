
#include "Game.h"
#include "GameObserver.h"
int main() {

	Game* myGame = new  Game(2);
    GameObserver* gameOB = new GameObserver(myGame);
    myGame->loader();

	while(true){
		myGame->phase1();
		myGame->phase3();
		myGame->phase4();
		if(myGame->checkWin()) break;
		myGame->phase5();

	}
	system("pause");
	return 0;
}