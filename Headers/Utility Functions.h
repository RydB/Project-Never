#ifndef UTILITY_H
#define UTILITY_H

#include "Common.h"

namespace uti{

	//Exception handling class for the utility functions *give this some error message logging
	class UtilityError{};

	int string_to_int(const std::string&);

	//Returns an optimized SDL_Surface pointer
	SDL_Surface* load_image(std::string filename);

	//Blits an image to the source at the x, y, coordinates.
	void apply_surface(int x, int y, SDL_Surface* source,
						SDL_Surface* destination, SDL_Rect* clip);

    bool check_collision( SDL_Rect A, SDL_Rect B );
}


#endif //UTILITY_H
