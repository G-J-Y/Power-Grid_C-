#include "Game.h"

int main() {

	Game myGame(4);
	myGame.loader();

	while(true){
		myGame.phase1();
		myGame.phase3();
		myGame.phase4();
		if(myGame.checkWin()) break;
		myGame.phase5();

	}
	system("pause");
	return 0;
}