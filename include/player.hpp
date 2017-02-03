#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

#include "audioengine.hpp"

class Player {
public:
  Player(const sf::Texture& texture, AudioEngine& audio);

  void handle_event(const sf::Event& event);
  void update();

  const sf::Sprite& sprite() const;
  
private:

  sf::Sprite m_sprite;
  bool m_isJumping;
  sf::Vector2f m_force;

  int m_speed;
  
  AudioEngine& m_audio;
};

#endif // PLAYER_HPP
