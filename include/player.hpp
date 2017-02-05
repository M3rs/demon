#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <sol.hpp>
#include "audioengine.hpp"
#include "textures.hpp"

class Player {
public:
  Player(Textures& textures, const AudioEngine& audio, sol::state& lua);

  void handle_event(const sf::Event& event);
  void update();

  const sf::Sprite& sprite() const;
  
private:

  sf::Sprite m_sprite;
  bool m_isJumping;
  sf::Vector2f m_force;

  int m_speed;
  
  Textures& m_textures;
  const AudioEngine& m_audio;
  sol::state& m_lua;

  std::string m_form;

  // "events"
  sol::function onJump;
  sol::function onLand;

  // lua funcs
  void setup_lua();
  void set_events();
  void set_texture(int x, int y, int w, int h);
  void change_texture(const std::string& txname);
};

#endif // PLAYER_HPP
