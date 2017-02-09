#include "textures.hpp"

#include "SDL_image.h"
#include <iostream>

Textures::Textures(SDL_Renderer* renderer) : m_renderer(renderer), m_cache(std::map<std::string, const Texture_ptr>()) {}

const SDL_Texture* const Textures::get(const std::string &filename) {
  auto it = m_cache.find(filename);
  if (it != m_cache.end()) {
    return it->second.get();
  }

  SDL_Surface* img = IMG_Load(filename.c_str());
  if (img == NULL) {
    std::cout << "Error loading " << filename << ": " << IMG_GetError() << std::endl;
    // TODO(ajm): error texture? null?
  }
  // TODO(ajm): add override method with color key param(s)
  SDL_SetColorKey(img, 1, SDL_MapRGB(img->format, 17, 13, 42));
  Texture_ptr tx(SDL_CreateTextureFromSurface(m_renderer, img));
  SDL_FreeSurface(img);

  m_cache.emplace(filename, std::move(tx));
  return m_cache[filename].get();
}

void Textures::loadTexture(const std::string& filename) {
  /*
	sf::Texture texture;
	if (!texture.loadFromFile(filename)) {
		std::cout << "Error loading texture '" << filename << "'" << std::endl;
		return;
	}
	m_cache.emplace(filename, texture);
  */
}

void Textures::unloadTexture(const std::string& filename) {
  //m_cache.erase(filename);
}
