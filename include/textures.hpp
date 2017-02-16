#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include <map>
#include <string>
#include "sdlhelpers.hpp"
#include "SDL.h"

class Texture_T;

class Textures {
public:

  Textures(SDL_Renderer* renderer);

  const Texture_T* get(const std::string& filename);

  void loadTexture(const std::string& filename);

  void unloadTexture(const std::string& filename);

private:

  SDL_Renderer* m_renderer;
  std::map<std::string, const Texture_T*> m_cache;
};

#endif // TEXTURES_HPP
