#include "Utility Functions.h"

int uti::string_to_int(const std::string& s){
	int ret;
	std::stringstream con(s);
	con >> ret;
	return ret;
}

SDL_Surface* uti::load_image(std::string filename){
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;

	loadedImage = IMG_Load(filename.c_str());

	if (loadedImage != NULL){
		optimizedImage = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);
		if(optimizedImage != NULL){
			//This will make it so that pink color is transparent
			SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY,
							  SDL_MapRGB(optimizedImage->format, 0xFF, 0, 0xFF));
		}
	}

	if(optimizedImage == NULL) throw UtilityError();

	return optimizedImage;
}

void uti::apply_surface(int x, int y, SDL_Surface* source,
							SDL_Surface* destination, SDL_Rect* clip)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, clip, destination, &offset);
}


bool uti::check_collision( SDL_Rect A, SDL_Rect B )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    bool collision = true;
    if( bottomA <= topB ) collision = false;
    if( topA >= bottomB ) collision = false;
    if( rightA <= leftB ) collision = false;
    if( leftA >= rightB ) collision = false;

    return collision;
}
