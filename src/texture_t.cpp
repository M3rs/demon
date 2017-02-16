#include "texture_t.hpp"
#include <SDL.h>

Texture_t::Texture_t(SDL_Renderer* renderer, SDL_Surface* surface) {
	sdl_text = SDL_CreateTextureFromSurface(renderer, surface);
}

Texture_t::~Texture_t() {
	SDL_DestroyTexture(sdl_text);
}

SDL_Texture * Texture_t::get()
{
	return sdl_text;
}
