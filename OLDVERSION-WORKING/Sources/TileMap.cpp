#include "TileMap.h"

const std::string TileMap::GROUND_IMG = "darkground64.png";
const std::string TileMap::WALL_IMG = "darkgreywall64.png";
const std::string TileMap::START_IMG = "ground64.png";
const std::string TileMap::END_IMG = "ground64.png";
const std::string TileMap::SIGHT_BLOCK = "sightblocker.png";


bool TileMap::tileCollision(const SDL_Rect& player) const{
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
            if(tiles[i][j].type == WALL){
                if(uti::check_collision(player, tiles[i][j].box))
                    return true;
            }
        }
    }
    return false;
}

int TileMap::getLevelHeight() const{
    return levelHeight;
}

int TileMap::getLevelWidth()const{
    return levelWidth;
}

void TileMap::setCamOffsets(int x, int y){
    camera.x = x;
    camera.y = y;
}

int TileMap::camX() const{
    return camera.x;
}

int TileMap::camY() const{
    return camera.y;
}

SDL_Rect TileMap::getCamera() const{
    return camera;
}

void TileMap::init(std::string level_file){

	std::fstream map_in(level_file.c_str());
	if(!map_in.good()) throw TileMapError("Problem with file input stream.");

	initMapInfo(map_in);

	for(int r = 0; r < rows; ++r){
	    std::vector<Tile> thisCol;
		for(int c = 0; c < cols; ++c){
			if(map_in.eof()) throw TileMapError("It appears that there wasn't any tile info in the file.");

			Tile in;
			char t;
			map_in >> t;
			in.init(c * TILE_SIZE, r * TILE_SIZE, convert_char_to_tile(t));


			if(in.type == START){
				startLoc.x = c * TILE_SIZE;
				startLoc.y = r * TILE_SIZE;
				startLoc.h = TILE_SIZE;
				startLoc.w = TILE_SIZE;
			}

			if(in.type == END){
				endLoc.x = c * TILE_SIZE;
				endLoc.y = r * TILE_SIZE;
                endLoc.h = TILE_SIZE;
                endLoc.w = TILE_SIZE;
			}

			thisCol.push_back(in);
		}
		tiles.push_back(thisCol);
	}
}

void TileMap::drawMap(SDL_Surface* screen) const{

    for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			SDL_Surface* tile = NULL;
			Tile curr = tiles[i][j];

			if(uti::check_collision(curr.box, camera)){

                switch(curr.type){
                case START:
                    tile = uti::load_image(START_IMG);
                    uti::apply_surface(curr.box.x - camera.x, curr.box.y - camera.y, tile, screen, NULL);
                    break;
                case END:
                    tile = uti::load_image(END_IMG);
                    uti::apply_surface(curr.box.x - camera.x, curr.box.y - camera.y, tile, screen, NULL);
                    break;
                case WALL:
                    tile = uti::load_image(WALL_IMG);
                    uti::apply_surface(curr.box.x - camera.x, curr.box.y - camera.y, tile, screen, NULL);
                    break;
                case GROUND:
                    tile = uti::load_image(GROUND_IMG);
                    uti::apply_surface(curr.box.x - camera.x, curr.box.y - camera.y, tile, screen, NULL);
                    break;
                case EMPTY:
                    break;
                }
			}

			/*if(it->covered) {
                tile = uti::load_image(SIGHT_BLOCK);
                uti::apply_surface(j*TILE_SIZE, i*TILE_SIZE, tile, screen, NULL);
			}*/
			if(tile) SDL_FreeSurface(tile);
		}
    }
}




void TileMap::initMapInfo(std::fstream& map_in){
	char x;
	std::string holder;

	//First line: get level number
	std::getline(map_in, holder);
	level = uti::string_to_int(holder);

	//Second line: get background image file name
	std::getline(map_in, holder);
	background = uti::load_image(holder);

	//Third line: get name of the level
	std::getline(map_in, mapName);

	//Fourth line: get rows and cols
	std::getline(map_in, holder);
	std::stringstream s(holder);
	s >> rows >> x >> cols;

	levelWidth = cols * TILE_SIZE;
	levelHeight = rows * TILE_SIZE;

	camera.h = SCREEN_HEIGHT;
	camera.w = SCREEN_WIDTH;
}


TileMap::TileType TileMap::convert_char_to_tile(char t) const{
	TileType ret;
	if(t == '.') ret = GROUND;
	else if(t == 'X' || t == 'x') ret = WALL;
	else if(t == 'S') ret = START;
	else if(t == 'E') ret = END;
	else if(t == 'O') ret = EMPTY;
	else throw TileMapError("Invalid character in the map text file.");

	return ret;
}

char TileMap::convert_tile_to_char(TileType t) const{
	char ret;

	switch(t){
	case START:
		ret = 'S';
		break;
	case END:
		ret = 'E';
		break;
	case WALL:
		ret = 'X';
		break;
	case GROUND:
		ret = '.';
		break;
	case EMPTY:
		ret = ' ';
		break;
	}

	return ret;
}
