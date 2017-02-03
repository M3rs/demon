#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

#include "audioengine.hpp"

class Player {
public:
  Player(const sf::Texture& texture, const AudioEngine& audio);

  void hande_event(const sf::Event& event);
  void update();

  const sf::Sprite& sprite() const;
  
private:

  sf::Sprite m_sprite;
  bool m_isJumping;
  sf::Vector2i force;

  int m_speed;
  
  const AudioEngine& m_audio;
};

#endif // PLAYER_HPP
