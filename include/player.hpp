#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <sol.hpp>
#include "textures.hpp"
#include <SDL.h>
#include <stdio.h>
#include <physicsbody.hpp>
#include <renderer.hpp>

struct Sprite;

class Player {
public:
  Player(Textures& textures, sol::state& lua, Sprite* sprite);

  void handle_event(SDL_Keycode keycode);
  void update(const Uint8* input, double deltaTime);

  bool isKeyPressed(const Uint8 *keyboardState, const char* keyName);
  
private:

  bool m_isJumping;
  //sf::Vector2f m_force;
  float m_speed;

  PhysicsBody			m_physicsBody;
  SDL_Rect				playerSprite;
  SDL_Texture*			texture;
  SDL_Renderer*			sdlRenderer; //dirty hack until we have a render registry
  
  Textures& m_textures;
  Sprite* m_sprite;
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
