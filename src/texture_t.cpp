#include "texture_t.hpp"
#include <SDL.h>
#include <iostream>

Texture_T::Texture_T() {}

/*
Texture_T::Texture_T(const Texture_T & t)
{
  sdl_text = std::move(t.sdl_text);
}

Texture_T& Texture_T::operator=(const Texture_T& t)
{
  sdl_text = std::move(t.sdl_text);
  //sdl_text = t.sdl_text;
  return *this;
}
*/

Texture_T::Texture_T(Texture_T&& t) : sdl_text(std::move(t.sdl_text))
{

}

Texture_T::Texture_T(SDL_Renderer *renderer, SDL_Surface *surface) {
  //sdl_text = SDL_CreateTextureFromSurface(renderer, surface);
  auto t = SDL_CreateTextureFromSurface(renderer, surface);
  sdl_text = std::unique_ptr<SDL_Texture, SDL_Deleter>(t, SDL_Deleter());
}

Texture_T::~Texture_T() {
  //if (sdl_text) {
  //SDL_DestroyTexture(sdl_text);
  //}
  std::cout << "Deleting: \n";// << sdl_text << std::endl;
}

SDL_Texture *Texture_T::get() { return sdl_text.get(); }
