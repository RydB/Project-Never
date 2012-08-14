#include "Player.h"


const int Player::HEART_RES = 50;
const std::string Player::HEART = "heart.png";

Player::Player(){
    hearts = 3;
    speed = 10;
}


void Player::move(Direction direction_input, const TileMap& currentlevel){
    int prevX(getX()), prevY(getY());

    int newX{prevX}, newY{prevY};

    switch(direction_input){
        case UP:
            newY = getY() - speed;
            if(getActiveClip() == UP1) setActiveClip(UP2);
            else setActiveClip(UP1);
            break;
        case DOWN:
            newY = getY() + speed;
            if(getActiveClip() == DOWN1) setActiveClip(DOWN2);
            else setActiveClip(DOWN1);
            break;
        case LEFT:
            newX = getX() - speed;
            if(getActiveClip() == LEFT1) setActiveClip(LEFT2);
            else setActiveClip(LEFT1);
        break;
        case RIGHT:
            newX = getX() + speed;
            if(getActiveClip() == RIGHT1) setActiveClip(RIGHT2);
            else setActiveClip(RIGHT1);
            break;
        case NONE:
            return;
    }

    setLoc(newX, newY);
    updateCollider();

    if(currentlevel.tileCollision(box())){
        setLoc(prevX, prevY);
        updateCollider();
    }
}


void Player::animate(){
    draw();

    for(int i = 0; i < hearts; ++i){
        uti::apply_surface(SCREEN_WIDTH - 45- i * HEART_RES,
                                        0, heart, getDest(), NULL);

	}
}


void Player::updateCamera(TileMap& currLevel){

    int cX = (getX() + getResolution() / 2) - SCREEN_WIDTH / 2;
    int cY = (getY() + getResolution() / 2) - SCREEN_HEIGHT / 2;

    if(cX < 0) cX = 0;
    if(cY < 0) cY = 0;
    if(cX > currLevel.getLevelWidth() - currLevel.getCamera().w) cX = currLevel.getLevelWidth() - currLevel.getCamera().w;
    if(cY > currLevel.getLevelHeight() - currLevel.getCamera().h) cY = currLevel.getLevelHeight() - currLevel.getCamera().h;

    currLevel.setCamOffsets(cX, cY);
}

