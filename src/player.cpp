#include "player.hpp"

Player::Player(const sf::Texture &texture, const AudioEngine &audio)
    : m_sprite(texture), m_audio(audio), m_speed(2), m_isJumping(false) {

  m_sprite.setTextureRect(sf::IntRect(0, 32, 32, 50));
  m_sprite.setPosition(300, 400);
}

void Player::handle_event(const sf::Event &event) {
  if (event.type == sf::Event::KeyReleased) {
    switch (event.key.code) {
    case sf::Keyboard::Space:
      m_isJumping = true;
      m_sprite.setTextureRect(sf::IntRect(48, 110, 30, 58));
      m_force = sf::Vector2f(0, -14);
      break;
    default: break;
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
  if (m_sprite.getPosition().y >= 400) {
    m_isJumping = false;
    m_sprite.setTextureRect(sf::IntRect(0, 32, 32, 50));
  }
}

const sf::Sprite &Player::sprite() const { return m_sprite; }
