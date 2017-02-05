#include "player.hpp"

Player::Player(const sf::Texture &texture, const AudioEngine &audio,
               sol::state &lua)
    : m_sprite(texture), m_audio(audio), m_speed(2), m_isJumping(false),
      m_lua(lua) {

  m_sprite.setTextureRect(sf::IntRect(0, 32, 32, 50));
  m_sprite.setPosition(300, 400);

  setup_lua();
}

void Player::setup_lua() {
  m_lua.script_file("player.lua");
  onJump = m_lua["player"]["normal"]["onJump"];
  onLand = m_lua["player"]["normal"]["onLand"];

  sol::table player_t = m_lua["player"];
  player_t.set_function("set_texture_rect", &Player::set_texture, this);
}

void Player::handle_event(const sf::Event &event) {
  if (event.type == sf::Event::KeyReleased) {
    switch (event.key.code) {
    case sf::Keyboard::Space:
      m_isJumping = true;
      m_force = sf::Vector2f(0, -14);
      onJump();
      break;
    case sf::Keyboard::R:
      // reload player script
      std::cout << "Reloading player.lua\n";
      setup_lua();

      break;
    default:
      break;
    }
  }
}

void Player::update() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    m_sprite.move(m_speed * -1, 0);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    m_sprite.move(m_speed, 0);
  }

  if (m_isJumping) {
    m_sprite.move(m_force);
    m_force.y += 1;
    m_sprite.move(sf::Vector2f(0, 3));
  }
  if (m_sprite.getPosition().y >= 400 && m_isJumping) {
    m_isJumping = false;
    onLand();
  }
}

const sf::Sprite &Player::sprite() const { return m_sprite; }

void Player::set_texture(int x, int y, int w, int h) {
  m_sprite.setTextureRect(sf::IntRect(x, y, w, h));
}
