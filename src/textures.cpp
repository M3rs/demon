#include "textures.hpp"

#include <iostream>

Textures::Textures() : m_cache(std::map<std::string, const sf::Texture>()) {}

const sf::Texture &Textures::get(const std::string &filename) {
  auto it = m_cache.find(filename);
  if (it != m_cache.end()) {
    return it->second;
  }

  sf::Texture tx;
  if (!tx.loadFromFile(filename)) {
    if (!tx.create(32, 32)) {
      std::cout << "Fatal texture error!";
      // broken?
    }
  }

  m_cache.emplace(filename, std::move(tx));
  return m_cache[filename];
}

void Textures::loadTexture(const std::string& filename) {
	sf::Texture texture;
	if (!texture.loadFromFile(filename)) {
		std::cout << "Error loading texture '" << filename << "'" << std::endl;
		return;
	}
	m_cache.emplace(filename, texture);
}

void Textures::unloadTexture(const std::string& filename) {
	m_cache.erase(filename);
}
