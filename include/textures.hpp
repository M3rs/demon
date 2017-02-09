#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include <map>
#include <string>
#include "sdlhelpers.hpp"
#include "SDL.h"

class Textures {
public:

  Textures(SDL_Renderer* renderer);

  const SDL_Texture* const get(const std::string& filename);

  void loadTexture(const std::string& filename);

  void unloadTexture(const std::string& filename);

private:

  SDL_Renderer* m_renderer;
  std::map<std::string, const Texture_ptr> m_cache;
};

#endif // TEXTURES_HPP
