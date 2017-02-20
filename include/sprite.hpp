#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <string>
#include "SDL.h"

class Texture_T;

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

class Sprite {
public:
  SDL_Texture* texture;
  SDL_Rect texture_coords; // texture coords to use (NULL = whole texture)
  Rect world_coords; // where object is in world

  void set_texture(int x, int y, int w, int h);
  void set_texture_and_offset(int x, int y, int w, int h);
  void change_texture(Texture_T* newtexture);
};

#endif // SPRITE_HPP
