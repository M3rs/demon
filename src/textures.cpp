#include "textures.hpp"
#include "texture_t.hpp"
#include "SDL_image.h"
#include <iostream>

Textures::Textures(SDL_Renderer* renderer) : m_renderer(renderer), 
			m_cache(std::map<std::string, Texture_T>()) {}

Texture_T* Textures::get(const std::string &filename) {
  auto it = m_cache.find(filename);
  if (it != m_cache.end()) {
    std::cout << "get texture: " << filename << std::endl;
	return &it->second; 

  }

  SDL_Surface* img = IMG_Load(filename.c_str());
  if (img == NULL) {
    std::cout << "Error loading " << filename << ": " << IMG_GetError() << std::endl;
    // TODO(ajm): error texture? null?
  }
  // TODO(ajm): add override method with color key param(s)
  SDL_SetColorKey(img, 1, SDL_MapRGB(img->format, 17, 13, 42));
  m_cache.emplace(filename, Texture_T(m_renderer, img));
  SDL_FreeSurface(img);
  return &m_cache[filename];
}

void Textures::loadTexture(const std::string& filename) {
  SDL_Surface* img = IMG_Load(filename.c_str());
  if (img == NULL) {
    std::cout << "Error loading " << filename << ": " << IMG_GetError() << std::endl;
    // TODO(ajm): error texture? null?
  }
  // TODO(ajm): add override method with color key param(s)
  SDL_SetColorKey(img, 1, SDL_MapRGB(img->format, 17, 13, 42));
  m_cache.emplace(filename, Texture_T(m_renderer, img));
  SDL_FreeSurface(img);

}

void Textures::unloadTexture(const std::string& filename) {
  m_cache.erase(filename);
}
