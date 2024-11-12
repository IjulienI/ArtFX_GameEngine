#include <iostream>
#include "Game.h"
#include <SDL.h>

#include "PongScene.h"

int main(int argc, char* argv[])
{
	Game* game = new Game("Hello World",{new PongScene()});
	game->Initialize();
	return 0;
}
