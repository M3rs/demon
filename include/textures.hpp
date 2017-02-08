#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include <map>
#include <string>
//#include <SFML/Graphics.hpp>

class Textures {
public:

  Textures();

  //const sf::Texture& get(const std::string& filename);
  // Remove method?

  void loadTexture(const std::string& filename);

  void unloadTexture(const std::string& filename);

private:

  //std::map<std::string, const sf::Texture> m_cache;
};

#endif // TEXTURES_HPP
