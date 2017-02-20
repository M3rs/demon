#include "rect.hpp"

SDL_Rect* Rect::to_sdl_rect() {
	sdl_rect.x = x;
	sdl_rect.y = y;
	sdl_rect.w = w;
	sdl_rect.h = h;
	return &sdl_rect;
}