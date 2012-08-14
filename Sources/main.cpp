#include "Common.h"
#include "Engine.h"
#include "MapObject.h"

int main(int argc, char** argv)
{

   Engine e;

    try{
        e.run();
    } catch(TileMapError& e){
        e.print();
    }


    return 0;
}
