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
  Player(Textures &textures, sol::state& lua, std::string luafile, std::string luatable, 
	  Sprite* sprite, PhysicsBody* physBody);

  void handle_event(SDL_Keycode keycode);
  void update(double deltaTime);

  bool isAlive();
  const std::string& getId();

  PhysicsBody* m_physicsBody;
  
private:

  bool m_isJumping;
  float m_speed;

  Textures& m_textures;
  Sprite* m_sprite;
  sol::state& m_lua;

  std::string script_file;
  std::string table;

  // obsolete
  std::string m_form;

  // lua helpers
  sol::function supdate;

  // lua funcs
  void setup_lua();
};

#endif // PLAYER_HPP
