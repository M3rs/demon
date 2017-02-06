#include "player.hpp"

#include <iostream>

Player::Player(Textures &textures, sol::state &lua)
    : m_textures(textures), m_speed(2), m_isJumping(false), m_lua(lua),
      m_form("normal") {

  m_sprite.setTexture(m_textures.get("garg.gif"));
  m_sprite.setTextureRect(sf::IntRect(0, 38, 32, 42));
  // m_sprite.setTextureRect(sf::IntRect(0, 32, 32, 50));
  m_sprite.setPosition(300, 400);

  setup_lua();
}

void Player::setup_lua() {
  m_lua.script_file("player.lua");
  set_events();

  sol::table player_t = m_lua["player"];
  player_t.set_function("set_texture_rect", &Player::set_texture, this);
  player_t.set_function("change_texture", &Player::change_texture, this);
  player_t.set_function("move_sprite", &Player::move_sprite, this);
}

void Player::set_events() {
  onJump = m_lua["player"][m_form]["onJump"];
  onLand = m_lua["player"][m_form]["onLand"];
}

void Player::handle_event(const sf::Event &event) {
  if (event.type == sf::Event::KeyReleased) {
    switch (event.key.code) {
    case sf::Keyboard::Space:
      m_isJumping = true;
      //m_force = sf::Vector2f(0, -14);
      m_force = sf::Vector2f(0, m_lua["player"][m_form]["jump"]);
      onJump();
      break;
    case sf::Keyboard::R:
      // reload player script
      std::cout << "Reloading player.lua\n";
      setup_lua();

      break;
    case sf::Keyboard::T:

      if (m_form == "normal") {
        m_form = "big";
        set_events();
      } else if (m_form == "big") {
        m_form = "normal";
        set_events();
      }
      m_lua["player"][m_form]["onTransform"]();

      break;
    default:
      break;
    }
  }
}

void Player::update() {
  // reset x velocity to 0 (could not and have accel/deccel (more complicated)
  m_force.x = 0;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    m_force.x = m_speed * -1;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    m_force.x = m_speed;
  }

  m_sprite.move(m_force);
  m_sprite.move(sf::Vector2f(0, 3)); // extra gravity

  if (m_isJumping) {
    m_force.y += 1;
    // m_sprite.move(sf::Vector2f(0, 3)); // extra gravity
  }

  if (m_force.y >= 0) {
  auto aabb = m_sprite.getGlobalBounds();

  // if (m_sprite.getPosition().y >= 400 && m_isJumping) {
  // if ((aabb.top + aabb.height) >= 400 && m_isJumping) {
  if ((aabb.top + aabb.height) >= 400) {
    m_sprite.setPosition(aabb.left, 400 - aabb.height);
    m_force.y = 0;
    if (m_isJumping) {
      m_isJumping = false;
      onLand();
    }
  }
  }
}

const sf::Sprite &Player::sprite() const { return m_sprite; }

void Player::set_texture(int x, int y, int w, int h) {
  m_sprite.setTextureRect(sf::IntRect(x, y, w, h));
}

void Player::change_texture(const std::string &txname) {
  m_sprite.setTexture(m_textures.get(txname));
}

void Player::move_sprite(float x, float y) { m_sprite.move(x, y); }
