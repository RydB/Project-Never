#ifndef CHARACTER_H
#define CHARACTER_H

#include "Sprite.h"
#include "TileMap.h"

    class Character {
    public:
        virtual void move(Direction direction_input, const TileMap& currentlevel) = 0;
        virtual void animate() = 0;

        virtual void setAttributes( int h, int sp, int ad, int d, int m, int md, int l, std::string n){
            hearts = h; speed = sp; attackdamage = ad;
            defense = d; magicdamage = m; magicdefense = md;
            level = l; name = n;
        }

        bool isDead() const{
            return hearts == 0;
        }

        void heal(int heartsup){
            hearts += heartsup;
        }

        void dealDamage(int heartsDown){
            hearts -= heartsDown;
        }


    protected:

        int hearts;
        int speed;
        int attackdamage;
        int defense;
        int magicdamage;
        int magicdefense;
        int level;
        std::string name;

    };


#endif //CHARACTER_H
