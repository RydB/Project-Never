#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

class Player : public Character, public Sprite{
public:
    Player();
    ~Player(){
        if(heart) SDL_FreeSurface(heart);
    }
    static const int HEART_WIDTH;

    void move(Direction direction_input, const TileMap& currentlevel);
    void animate();

    void init(){ heart = uti::load_image(HEART); }

    void updateCamera(TileMap& currLevel);


 private:

    SDL_Surface* heart;

    enum ClipFace
    {
        LEFT1,
        LEFT2,
        RIGHT1,
        RIGHT2,
        DOWN1,
        DOWN2,
        UP1,
        UP2
    };

    static const std::string HEART;
    static const int HEART_RES;

};

#endif //PLAYER_H




