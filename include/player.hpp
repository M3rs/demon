#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <sol.hpp>
#include "audioengine.hpp"

class Player {
public:
  Player(const sf::Texture& texture, const AudioEngine& audio, sol::state& lua);

  void handle_event(const sf::Event& event);
  void update();

  const sf::Sprite& sprite() const;
  
private:

  sf::Sprite m_sprite;
  bool m_isJumping;
  sf::Vector2f m_force;

  int m_speed;
  
  const AudioEngine& m_audio;
  sol::state& m_lua;
  sol::function updater;
};

#endif // PLAYER_HPP
