/********************************************************************
To do:
-Think of how the menu is going to interact with the the engine
-Specifically, how the options will be selected and used to change
  the game state.
-Use of enum for the game state good enough?
*********************************************************************/

#ifndef ENGINE_H
#define ENGINE_H

#include "Common.h"
#include "Utility Functions.h"
#include "TileMap.h"
#include "Timer.h"
#include "Player.h"

/* Constants used in the Engine Class */
const int NUM_LEVELS = 5;
const std::string TEST_MAZE = "Test_Maze.txt";

/*************************************************/
/* The Engine class, contains the main game loop */
/*************************************************/

enum GameState {MENU, PLAY};

class EngineError{}; //For exceptions.

class Engine{
public:
	Engine() :
		currentState(MENU),currLevel(0)
    	{ initSDL(); }

	void run();
private:

	SDL_Surface*        screen;
	GameState           currentState;
	int                 currLevel;
	TileMap             levels[5];
	Player              player;
	SDL_Event           event;
	double              timeFactor;
	bool                play;

	//Initializes the screen and sets the caption.
	void initSDL();

	/******************************************************/

	void initGame();

	/* Primary functions to be used in the main game loop */

	//First, input from the player will be taken
	void processInput();
	//Based on the user input, various game world elements will be updated.
	void update();
	//Based on what was updated, the screen will be redrawn accordingly.
	void render();
	/////////////////////////////////////////////////////////
};

#endif //ENGINE_H
