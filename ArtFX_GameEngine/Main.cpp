#include <iostream>
#include "Game.h"
#include <SDL.h>

#include "Game/Scenes/PongScene.h"
#include "Scenes/Debug/DebugCollisionScene.h"

int main(int argc, char* argv[])
{
	Game* game = new Game("Hello World",{new DebugCollisionScene()});
	game->Initialize();
	return 0;
}
