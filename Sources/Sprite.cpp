#include "Sprite.h"

Sprite::Sprite(){
    spriteSheetAttributes.sheet = NULL;
    spriteSheetAttributes.clips = NULL;
}

Sprite::~Sprite() {
    if(spriteSheetAttributes.clips != NULL) delete [] spriteSheetAttributes.clips;
}

void Sprite::setupCollider(int xo, int yo, int ho, int wo){
    collisionAttributes.x_offset = xo;
    collisionAttributes.y_offset = yo;
    collisionAttributes._box.h = ho;
    collisionAttributes._box.w = ho;
}

void Sprite::setupSheet(SDL_Surface* dest, std::string file, int numClips, int ac, int _res, int sr){
    spriteSheetAttributes.destination = dest;
    spriteSheetAttributes.active = ac;
    spriteSheetAttributes.res = _res;
    spriteSheetAttributes.sheetrows = sr;


    //Load the surface
    if(spriteSheetAttributes.sheet != NULL) SDL_FreeSurface(spriteSheetAttributes.sheet);
    spriteSheetAttributes.sheet = uti::load_image(file);

    //Initialize the sprite sheet rect
    if(spriteSheetAttributes.clips != NULL) delete [] spriteSheetAttributes.clips;
    spriteSheetAttributes._numClips = numClips;
    spriteSheetAttributes.clips = new SDL_Rect[spriteSheetAttributes._numClips];

    //Apply each rect to the sprite sheet
    int index = 0;
    int res = spriteSheetAttributes.res;
    for(int i = 0; i < spriteSheetAttributes.sheetrows; ++i){
        for(int j = 0; j < spriteSheetAttributes._numClips/spriteSheetAttributes.sheetrows; ++j){
            spriteSheetAttributes.clips[index].x = (i * res) + (j * res);
            spriteSheetAttributes.clips[index].y = i * res;
            spriteSheetAttributes.clips[index].h = res;
            spriteSheetAttributes.clips[index].w = res;
            ++index;
        }
    }
}

void Sprite::setActiveClip(int a) {
    spriteSheetAttributes.active = a;
}
int Sprite::getActiveClip() const {
    return spriteSheetAttributes.active;
}
void Sprite::draw(const SDL_Rect& camera) const {
    uti::apply_surface(_x-camera.x, _y-camera.y , spriteSheetAttributes.sheet, spriteSheetAttributes.destination,
                        &spriteSheetAttributes.clips[spriteSheetAttributes.active]);
}

int Sprite::getResolution() const{
    return spriteSheetAttributes.res;
}

SDL_Surface* Sprite::getDest(){
    return spriteSheetAttributes.destination;
}

void Sprite::updateCollider(){
    collisionAttributes._box.x = _x + collisionAttributes.x_offset;
    collisionAttributes._box.y = _y + collisionAttributes.y_offset;
}

SDL_Rect Sprite::box() const {
    return collisionAttributes._box;
}

bool Sprite::collision(SDL_Rect other) const {
    return uti::check_collision(collisionAttributes._box, other);
}

