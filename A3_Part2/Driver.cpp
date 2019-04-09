#include "Game.h"



int main() {

	Game myGame(2);
	myGame.loader();


	//test for singleton
	ResourcesMarket* testSinleton = ResourcesMarket:s_instance();

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