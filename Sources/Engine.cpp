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
	while(SDL_PollEvent(&event)){
        Direction playerDir = NONE;

        if(event.type == SDL_KEYDOWN){
            switch(event.key.keysym.sym ){
                case SDLK_w:
                playerDir = UP;
                break;
                case SDLK_s:
                playerDir = DOWN;
                break;
                case SDLK_a:
                    playerDir = LEFT;
                    break;
                case SDLK_d:
                    playerDir = RIGHT;
                    break;
                default:
                break;
            }

        }
        player.move(playerDir, levels[currLevel]);
        player.updateCamera(levels[currLevel]);

        if(event.type == SDL_QUIT) play = false;
    }
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
