#include "sprite.hpp"
#include <SDL_image.h>
#include <iostream>
#include <physicsbody.hpp>
#include <player.hpp>

Player::Player(Textures &textures, sol::state &lua, Sprite *sprite)
    : m_textures(textures), m_speed(150), m_isJumping(false), m_lua(lua),
      m_form("normal"), m_sprite(sprite) {

  // now we can change the player texture, yay!!
  m_sprite->texture = textures.get("res/images/garg.gif");
  m_sprite->texture_coords = SDL_Rect{0, 38, 32, 42};
  m_sprite->world_coords = SDL_Rect{100, 100, 32, 42};

  m_physicsBody = PhysicsBody(&m_sprite->world_coords);

  setup_lua();
}

void Player::setup_lua() {
  m_lua.script_file("res/scripts/player.lua");
  // test
  set_events();

  sol::table player_t = m_lua["player"];
  player_t.set_function("set_texture_rect", &Player::set_texture, this);
  player_t.set_function("change_texture", &Player::change_texture, this);
  player_t.set_function("move_sprite", &Player::move_sprite, this);
  player_t.set_function("set_texture_and_offset",
                        &Player::set_texture_and_offset, this);
}

void Player::set_events() {
  onJump = m_lua["player"][m_form]["onJump"];
  onLand = m_lua["player"][m_form]["onLand"];
  supdate = m_lua["player"]["update"];
}

void Player::handle_event(SDL_Keycode keycode) {

  switch (keycode) {
  case SDLK_SPACE:
    m_isJumping = true;
    // m_force = sf::Vector2f(0, -14);
    // m_force = sf::Vector2f(0, m_lua["player"][m_form]["jump"]);
    onJump();
    break;
  case SDLK_r:
    // reload player script
    std::cout << "Reloading player.lua\n";
    setup_lua();
    break;
  case SDLK_t:
    if (m_form == "normal") {
      m_form = "big";
    } else if (m_form == "big") {
      m_form = "normal";
    }
    set_events();
    m_lua["player"][m_form]["onTransform"]();
    break;
  default:
    break;
  }
}

void Player::update(const Uint8 *input, double deltaTime) {
  // reset x velocity to 0 (could not and have accel/deccel (more complicated)
  m_physicsBody.vel_x = 0;

  supdate(deltaTime);
  
  /*
    // moved input to lua
  if (isKeyPressed(input, "A")) {
    m_physicsBody.vel_x = m_speed * -1.0F * deltaTime;
  } else if (isKeyPressed(input, "D")) {
    m_physicsBody.vel_x = m_speed * deltaTime;
  }
  */

  // m_sprite.move(sf::Vector2f(0, 3)); // extra gravity

  if (m_isJumping) {
    // m_force.y += 1;
    // m_sprite.move(sf::Vector2f(0, 3)); // extra gravity
  }

  m_physicsBody.vel_x = m_lua["player"]["velx"];
  m_physicsBody.vel_y = m_lua["player"]["vely"];
  m_physicsBody.updateMotion();

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

bool Player::isKeyPressed(const Uint8 *input, const char *keyName) {
  return input[SDL_GetScancodeFromName(keyName)] == 1;
}
