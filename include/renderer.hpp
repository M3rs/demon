#ifndef RENDERER_HPP
#define RENDERER_HPP

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
  SDL_Texture *texture;

private:
  SDL_Window *window;
  SDL_Renderer *renderer;
};

#endif // RENDERER_HPP
