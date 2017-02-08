#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <sol.hpp>
#include "textures.hpp"
#include <SDL.h>
#include <stdio.h>

class Player {
public:
  Player(Textures& textures, sol::state& lua);

  void handle_event(SDL_Keycode keycode);
  void update(const Uint8* input);

  //const sf::Sprite& sprite() const;

  bool isKeyPressed(const Uint8 *keyboardState, char* keyName);
  
private:

  //sf::Sprite m_sprite;
  bool m_isJumping;
  //sf::Vector2f m_force;

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
  void set_texture_and_offset(int x, int y, int w, int h);
  
};

#endif // PLAYER_HPP
