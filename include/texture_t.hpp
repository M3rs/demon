#ifndef TEXTURE_T_HPP
#define TEXTURE_T_HPP

#include <SDL.h>

#include "sdlhelpers.hpp"

class Texture_T {
public:
  
  Texture_T();
  Texture_T(SDL_Renderer *renderer, SDL_Surface *surface);
  ~Texture_T();

  Texture_T(Texture_T&& t);
  //Texture_T(const Texture_T &t);
  //Texture_T &operator=(const Texture_T &t);

  SDL_Texture *get();

private:
  // SDL_Texture* sdl_text;
  Texture_ptr sdl_text;
};

#endif // TEXTURE_T_HPP
