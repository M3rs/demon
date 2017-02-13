#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <map>
#include <string>
#include "sprite.hpp"
#include <SDL.h>

// fwd decl
class SDL_Window;
class SDL_Renderer;
namespace sol {
  class state;
}

//tmp
class SDL_Texture;

class Renderer {
public:
  Renderer();
  ~Renderer();

  void update();
  bool initialize(sol::state &lua);
  SDL_Renderer* getRenderer();

  /** Add sprite to render list */
  Sprite* add_sprite(const std::string& key);
  void remove_sprite(const std::string& key);

private:
  SDL_Window *window;
  SDL_Renderer *renderer;

  std::map<std::string, Sprite> m_drawlist;
};

#endif // RENDERER_HPP
