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
  Player(Textures& textures, sol::state& lua, std::string luafile, std::string luatable, Sprite* sprite);

  void handle_event(SDL_Keycode keycode);
  void update(double deltaTime);
  
private:

  bool m_isJumping;
  float m_speed;

  PhysicsBody			m_physicsBody;
  
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
  void set_texture(int x, int y, int w, int h);
  void change_texture(const std::string& txname);
  void move_sprite(float x, float y);
  void set_texture_and_offset(int x, int y, int w, int h);

  void apply_jump(int force);
};

#endif // PLAYER_HPP
