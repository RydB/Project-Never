#include "Timer.h"


void Timer::start(){

    started = true;
    paused = false;

    startTicks = SDL_GetTicks();
}

void Timer::stop(){

    started = false;
    paused = false;

}

void Timer::pause(){
    if(started && !paused) {
        paused = true;
        pausedTicks = SDL_GetTicks() - startTicks;
    }

}

void Timer::unpause(){
    if(paused){
        paused = false;
        startTicks = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    }
}

int Timer::getTicks() const{
    if(started && paused) return pausedTicks;
    return SDL_GetTicks() - startTicks;
}

bool Timer::isStarted() const{
    return started;
}

bool Timer::isPaused() const{
    return paused;
}
