#include "texture_t.hpp"
#include <SDL.h>
#include <iostream>

Texture_T::Texture_T() {}

Texture_T::Texture_T(Texture_T&& t) : sdl_text(std::move(t.sdl_text)) {}

Texture_T::Texture_T(SDL_Renderer *renderer, SDL_Surface *surface) {
  auto t = SDL_CreateTextureFromSurface(renderer, surface);
  sdl_text = std::unique_ptr<SDL_Texture, SDL_Deleter>(t, SDL_Deleter());
}

Texture_T::~Texture_T() {}

SDL_Texture *Texture_T::get() { return sdl_text.get(); }
