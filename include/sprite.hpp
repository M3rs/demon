#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SDL.h>
#include <string>

struct Sprite {
  SDL_Texture* texture;
  SDL_Rect texture_coords; // texture coords to use (NULL = whole texture)
  SDL_Rect world_coords; // where object is in world
};

#endif // SPRITE_HPP
