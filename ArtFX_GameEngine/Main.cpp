#include <iostream>
#include "Game.h"
#include <SDL.h>

#include "Scenes/BowlingScene.h"
#include "Scenes/Base/BaseScene.h"
#include "Scenes/Debug/GLTestScene.h"

int main(int argc, char* argv[])
{
	Game* game = new Game("XCore - DebugEngine",{new BowlingScene()});
	game->Initialize();
	return 0;
}
