#include <iostream>
#include "Game.h"
#include <SDL.h>

#include "Scenes/Debug/GLTestScene.h"

int main(int argc, char* argv[])
{
	Game* game = new Game("Hello World",{new GLTestScene});
	game->Initialize();
	return 0;
}
