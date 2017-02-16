#include "texture_t.hpp"
#include <SDL.h>

Texture_T::Texture_T(SDL_Renderer* renderer, SDL_Surface* surface) {
	sdl_text = SDL_CreateTextureFromSurface(renderer, surface);
}

Texture_T::~Texture_T() {
	SDL_DestroyTexture(sdl_text);
}

SDL_Texture * Texture_T::get()
{
	return sdl_text;
}
