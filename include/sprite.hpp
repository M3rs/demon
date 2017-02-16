#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SDL.h>
#include <string>

struct Sprite {
  SDL_Texture* texture;
  SDL_Rect texture_coords; // texture coords to use (NULL = whole texture)
  SDL_Rect world_coords; // where object is in world

  void set_texture(int x, int y, int w, int h);
  void set_texture_and_offset(int x, int y, int w, int h);
};

#endif // SPRITE_HPP
