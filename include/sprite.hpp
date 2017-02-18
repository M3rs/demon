#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <string>
#include "SDL.h"

class Texture_T;

class Sprite {
public:
  SDL_Texture* texture;
  SDL_Rect texture_coords; // texture coords to use (NULL = whole texture)
  SDL_Rect world_coords; // where object is in world

  void set_texture(int x, int y, int w, int h);
  void set_texture_and_offset(int x, int y, int w, int h);
  void change_texture(Texture_T* newtexture);
};

#endif // SPRITE_HPP
