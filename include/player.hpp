#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <sol.hpp>
#include "textures.hpp"

class Player {
public:
  Player(Textures& textures, sol::state& lua);

  void handle_event(const sf::Event& event);
  void update();

  const sf::Sprite& sprite() const;
  
private:

  sf::Sprite m_sprite;
  bool m_isJumping;
  sf::Vector2f m_force;

  int m_speed;
  
  Textures& m_textures;
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
  void move_sprite(float x, float y);
};

#endif // PLAYER_HPP
