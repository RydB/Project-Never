#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <set>
#include <map>

#include "SDL.h"
#include "SDL_image.h"


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int COLOR_BPP = 32;

const std::string VERSION = "v0.0.1";
const std::string CAPTION = "Maze Warrior ";

enum Direction {UP, DOWN, LEFT, RIGHT, NONE};


#endif //COMMON_H
