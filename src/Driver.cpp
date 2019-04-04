#include "Game.h"

int main() {

	Game myGame(2);
	myGame.loader();
	myGame.phase1();
	myGame.phase3();
	myGame.phase4();

	system("pause");
	return 0;
}