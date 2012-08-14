#ifndef TILE_MAP_H
#define TILE_MAP_H

#include "Common.h"
#include "Utility Functions.h"
#include "MapObject.h"

class TileMapError{
public:
    void print(){
        std::cerr << error << std::endl;
    }

    TileMapError(std::string e) : error(e) {}
private:
    std::string error;

};

class TileMap{

private:

    /** Private Constants **/
    static const std::string GROUND_IMG;
    static const std::string WALL_IMG;
    static const std::string START_IMG;
    static const std::string END_IMG;
    static const std::string SIGHT_BLOCK;

    /**Private Structures**/
    enum TileType
    {
        WALL,
        GROUND,
        START,
        END,
        EMPTY
    };

    struct Tile
    {
        TileType type;
        SDL_Rect box;
        bool covered, inCam;

        Tile() : type(EMPTY), covered(true), inCam(false)
        {
            box.x = 0;
            box.y = 0;
            box.h = TILE_SIZE;
            box.w = TILE_SIZE;
        }

        void init(int x, int y, TileType t)
        {
            type = t;
            box.x = x;
            box.y = y;
        }


    };

public:
    /** Interface **/
    /*Initializes all the data members using a text file of the following format:
	1				        | -First line is the level number of the maze
	level.png	            |-Background image for the level
	Level Name		        |-Name of the level
	4x4			    	    |-Number of rows x cols
	S.XX		        	|-The actual map:
	X...                    |  -S: start location
	XXX.		            |  -X: Wall, .: passable ground
	E...  			        |  -E: end of the level*/
	void init(std::string level_file);
    void drawMap(SDL_Surface* screen) const;

    int getLevelWidth() const;
    int getLevelHeight() const;

    void setCamOffsets(int x, int y);

    //Get camera offsets
    int camX() const;
    int camY() const;
    //Get Camera
    SDL_Rect getCamera() const;

    bool tileCollision(const SDL_Rect& player) const;

    int startX() const { return startLoc.x; }
    int startY() const { return startLoc.y; }

private:

    int                      levelWidth,levelHeight;
    int                      rows, cols;
    int                      level;
    std::string              mapName;
    SDL_Surface*             background;
    SDL_Rect                 camera;
    SDL_Rect                 startLoc, endLoc;
    std::vector < std::vector <Tile> > tiles;

    /** Private Utility Functions **/

	//Used to map characters and tiletypes
	TileType convert_char_to_tile(char t) const;
	char convert_tile_to_char(TileType t) const;

	//Initialize the map's data members
	void initMapInfo(std::fstream& map_in);


};



#endif //TILE_MAP_H
