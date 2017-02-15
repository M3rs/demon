#include "sprite.hpp"
#include <SDL_image.h>
#include <iostream>
#include <algorithm> // std::swap?
#include <physicsbody.hpp>
#include <player.hpp>

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
}

Player::Player(Textures &textures, sol::state &lua, std::string luafile,
               std::string luatable, Sprite *sprite, PhysicsBody *physBody)
    : m_textures(textures), m_speed(150), m_isJumping(false), m_lua(lua),
      m_form("normal"), m_sprite(sprite), script_file(luafile),
      table(luatable) {

  setup_lua();

  sol::table sprite_t = m_lua[table]["sprite"];
  
  m_sprite->texture = textures.get(sprite_t["texture_file"]);
  m_sprite->texture_coords = getRectFromTable(sprite_t["texture_coords"]);
  m_sprite->world_coords = getRectFromTable(sprite_t["world_coords"]);

  m_physicsBody = physBody;
}

void Player::setup_lua() {
  m_lua.script_file(script_file);

  sol::table player_t = m_lua[table];
  
  supdate = player_t["update"];
  player_t.set_function("set_texture_rect", &Player::set_texture, this);
  player_t.set_function("change_texture", &Player::change_texture, this);
  player_t.set_function("move_sprite", &Player::move_sprite, this);
  player_t.set_function("set_texture_and_offset",
                        &Player::set_texture_and_offset, this);
  player_t.set_function("apply_jump", &Player::apply_jump, this);
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
	m_physicsBody->updateInputs(m_lua[table]["velx"], m_lua[table]["vely"]);

  // hack: player specific
  //m_physicsBody.vel_x = m_lua[table]["velx"];
  // m_physicsBody.vel_y = m_lua["player"]["vely"];
  //m_physicsBody.updateMotion(m_sprite); //new physicsengine updates in main

  /*
  if (m_force.y >= 0) {
  auto aabb = m_sprite.getGlobalBounds();

  // if (m_sprite.getPosition().y >= 400 && m_isJumping) {
  // if ((aabb.top + aabb.height) >= 400 && m_isJumping) {
  if ((aabb.top + aabb.height) >= 400) {
    //m_sprite.setPosition(aabb.left, 400 - aabb.height);
    //m_force.y = 0;
    if (m_isJumping) {
      m_isJumping = false;
      onLand();
    }
  }
  }
  */
}

void Player::set_texture(int x, int y, int w, int h) {
  m_sprite->texture_coords.x = x;
  m_sprite->texture_coords.y = y;
  m_sprite->texture_coords.w = w;
  m_sprite->texture_coords.h = h;

  m_sprite->world_coords.w = w;
  m_sprite->world_coords.h = h;
}

void Player::change_texture(const std::string &txname) {
  m_sprite->texture = m_textures.get(txname);
}

void Player::move_sprite(float x, float y) {
  // m_sprite.move(x, y);
}

void Player::set_texture_and_offset(int x, int y, int w, int h) {
  // shortcut for setTexture and moveSprite
  // adjusts so as to keep bottom plane consistent

  auto old_height = m_sprite->texture_coords.h;
  set_texture(x, y, w, h);
  m_sprite->world_coords.y += (old_height - h);
}

void Player::apply_jump(int force)
{
  m_physicsBody->vel_y = force;
  m_physicsBody->airborne = true;
}

bool Player::isAlive()
{
  return true;
}

const std::string& Player::getId()
{
  return table;
}
