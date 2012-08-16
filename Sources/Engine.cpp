#include "Engine.h"


void Engine::initSDL(){
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_BPP, SDL_SWSURFACE);
	std::string caption = CAPTION + VERSION;
	SDL_WM_SetCaption(caption.c_str(), NULL);
}

void Engine::run(){
    initGame();

    while(play){
        render();
        processInput();
    }
}


void Engine::render(){
	levels[currLevel].drawMap(screen);
	player.animate(levels[0]);
	SDL_Flip(screen);
}

void Engine::processInput(){

    Uint8* keystate = SDL_GetKeyState(NULL);
    Direction playerDir = NONE;

    if(keystate[SDLK_a])   playerDir = LEFT;
    if(keystate[SDLK_d])   playerDir = RIGHT;
    if(keystate[SDLK_w])  playerDir = UP;
    if(keystate[SDLK_s])    playerDir = DOWN;

	while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                play = false;
            break;
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE) play = false;
            break;
        }
	}
    player.move(playerDir, levels[currLevel]);
    player.updateCamera(levels[currLevel]);
}

void Engine::initGame(){
    std::string firstLevel = "Test_Maze.txt";
    levels[0].init(firstLevel);

    std::string startPlayerImage = "player32.png";
    int numClipsPlayerSheet = 8;
    player.setLoc(levels[0].startX(), levels[0].startY());
    player.setupCollider(5, 5, 20, 0);
    player.updateCamera(levels[0]);
    player.setupSheet(screen, startPlayerImage, numClipsPlayerSheet, DOWN, 32, 2);
    player.init();
}

void Engine::initGame(){
    std::string firstLevel = "test_open.txt";
    levels[0].init(firstLevel);

    std::string startPlayerImage = "player32.png";
    int numClipsPlayerSheet = 8;
    player.setLoc(levels[0].startX(), levels[0].startY());
    player.setupCollider(5, 5, 20, 0);
    player.updateCamera(levels[0]);
    player.setupSheet(screen, startPlayerImage, numClipsPlayerSheet, DOWN, 32, 2);
    player.init();
}
