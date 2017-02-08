#ifndef RENDERER_HPP
#define RENDERER_HPP

// fwd decl
class SDL_Window;
class SDL_Renderer;
namespace sol {
  class state;
}

class Renderer {
public:
  Renderer();
  ~Renderer();

  void update();
  bool initialize(sol::state &lua);

private:
  SDL_Window *window;
  SDL_Renderer *renderer;
};

#endif // RENDERER_HPP
