#ifndef SPRITE_H
#define SPRITE_H


#include "Common.h"
#include "Utility Functions.h"

class SpriteError{
public:
    SpriteError(std::string e){
        error = e;
    }
    void print(){
        std::cout << error << std::endl;
    }
private:
    std::string error;
};

class Sprite{
public:
    Sprite();
    virtual ~Sprite() = 0;

    //Initialization functions - MUST be called before anything else in the class can be used.
    void setupCollider(int xo, int yo, int ho, int wo);
    void setupSheet(SDL_Surface* dest, std::string file, int numClips, int ac, int _res, int sr);

    //SpriteSheet functions
    void setActiveClip(int a);
    int getActiveClip() const;
    void draw() const;
    int getResolution() const;
    SDL_Surface* getDest();


    //Collider functions
    void updateCollider();
    SDL_Rect box() const;
    bool collision(SDL_Rect other) const;

    //Access and Modify coordinates of the sprite
    void setLoc(int x, int y) { _x = x; _y = y; }
    int getX() const { return _x; }
    int getY() const { return _y; }

private:
    struct Collider{
        SDL_Rect  _box;
        int       x_offset,
                  y_offset;
    };

    struct SpriteSheet{
        SDL_Surface*     destination;
        SDL_Surface*    sheet;
        SDL_Rect*       clips;
        int             _numClips;
        int             active;
        int             res;
        int             sheetrows;
    };


    Collider     collisionAttributes;
    SpriteSheet  spriteSheetAttributes;
    int          _x, _y;

};


#endif //SPRITE_H
