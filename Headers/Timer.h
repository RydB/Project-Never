#ifndef TIMER_H
#define TIMER_H

#include "Common.h"

class Timer{

private:
    int    startTicks,
           pausedTicks;

    bool   started,
           paused;

    public:

        Timer() : startTicks(0), pausedTicks(0), started(false), paused(false) {}

        void start();
        void stop();
        void pause();
        void unpause();

        int getTicks() const;

        bool isStarted() const;
        bool isPaused() const;



};


#endif //TIMER_H
