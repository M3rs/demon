#include "sprite.hpp"
#include "texture_t.hpp"

void Sprite::set_texture(int x, int y, int w, int h)
{
  texture_coords.x = x;
  texture_coords.y = y;
  texture_coords.w = w;
  texture_coords.h = h;

  world_coords.w = w;
  world_coords.h = h;
}

void Sprite::set_texture_and_offset(int x, int y, int w, int h)
{
  auto old_height = texture_coords.h;
  set_texture(x, y, w, h);
  world_coords.y += (old_height - h);
}

void Sprite::change_texture(Texture_T* newtexture)
{
  texture = newtexture->get();
}
