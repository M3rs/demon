#ifndef RECT_HPP
#define RECT_HPP

#include <SDL.h>

//Rectangle with float coordinates and dimensions
class Rect {
public:
	float x;
	float y;
	float w;
	float h;

	//keep an object for transmitting out to SDL systems
	//I think this is the right move for managing the lifetime of a 'temp'
	//SDL_Rect that we aren't using directly?
	SDL_Rect sdl_rect;
	SDL_Rect* to_sdl_rect();
};

#endif //RECT_HPP
