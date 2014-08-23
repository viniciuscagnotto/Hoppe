#include "header.h"

int main()
{
	srand(time(NULL));
	Game *pGame = new Game();
	pGame->Update();
	pGame->Cleanup();
	delete pGame;

    return 0;
}
