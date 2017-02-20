#include "sprite.hpp"
#include <SDL_image.h>
#include <iostream>
#include <algorithm> // std::swap?
#include <physicsbody.hpp>
#include <player.hpp>
#include "texture_t.hpp"

// TODO(ajm): move this somewhere else
namespace {
SDL_Rect getRectFromTable(sol::table t) {
  SDL_Rect r;
  r.x = t["x"];
  r.y = t["y"];
  r.w = t["w"];
  r.h = t["h"];

  return r;
}

Rect getFloatRectFromTable(sol::table t) {
	Rect r;
	r.x = t["x"];
	r.y = t["y"];
	r.w = t["w"];
	r.h = t["h"];

	return r;
}
}

Player::Player(Textures &textures, sol::state &lua, std::string luafile,
               std::string luatable, Sprite *sprite, PhysicsBody *physBody)
    : m_textures(textures), m_speed(150), m_isJumping(false), m_lua(lua),
      m_form("normal"), m_sprite(sprite), script_file(luafile),
      table(luatable) {

  setup_lua();

  sol::table sprite_t = m_lua[table]["sprite"];
  Texture_T* text_t = textures.get(sprite_t["texture_file"]);
  m_sprite->texture = text_t->get();
  //m_sprite->texture = textures.get(sprite_t["texture_file"]);
  m_sprite->texture_coords = getRectFromTable(sprite_t["texture_coords"]);
  m_sprite->world_coords = getFloatRectFromTable(sprite_t["world_coords"]);

  m_physicsBody = physBody;

  m_lua[table]["body"] = physBody;
  m_lua[table]["mysprite"] = m_sprite;
}

void Player::setup_lua() {
  m_lua.script_file(script_file);

  sol::table player_t = m_lua[table];
  
  supdate = player_t["update"];
 }

void Player::handle_event(SDL_Keycode keycode) {

  switch (keycode) {
  case SDLK_r:
    // reload player script
    std::cout << "Reloading player.lua\n";
    setup_lua();
    break;
  default:
    break;
  }
}

void Player::update(double deltaTime) {
	//entities decide their own response to input in lua, then give values to physBody	
	supdate(deltaTime);
}

bool Player::isAlive()
{
  return true;
}

const std::string& Player::getId()
{
  return table;
}


