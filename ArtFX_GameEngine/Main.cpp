/**
 * @file Main.cpp
 * @brief Point d'entrée principal du moteur de jeu.
 */

#include <iostream>
#include "Game.h"
#include <SDL.h>

#include "Bowling/Scene/BowlingScene.h"
#include "Doom/Scene/DoomScene.h"
#include "Scenes/Base/BaseScene.h"
#include "Scenes/Debug/GLTestScene.h"

int main(int argc, char* argv[])
{
	Game* game = new Game("XCore - DebugEngine",{new DoomScene()});
	game->Initialize();
	return 0;
}

