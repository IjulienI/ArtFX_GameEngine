/**
 * @file Main.cpp
 * @brief Entry point for the game engine. Initializes the game and starts the main loop.
 */

#include <iostream>
#include "Game.h"
#include <SDL.h>

#include "Bowling/Scene/BowlingScene.h"
#include "Doom/Scene/DoomScene.h"
#include "Scenes/Base/BaseScene.h"
#include "Scenes/Debug/GLTestScene.h"

/**
 * @brief Main function of the game engine.
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return Exit code of the application.
 */
int main(int argc, char* argv[])
{
	// Create a new game instance with the specified scenes.
	Game* game = new Game("XCore - DebugEngine", {new DoomScene()});
	
	// Initialize the game engine.
	game->Initialize();
	
	// Return the exit code.
	return 0;
}
