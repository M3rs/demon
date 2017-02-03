#include "player.hpp"

Player::Player(const sf::Texture &texture, const AudioEngine &audio)
  : m_sprite(texture), m_audio(audio), m_speed(2) {
  m_sprite.setTextureRect(sf::IntRect(0, 32, 32, 50));

  m_sprite.setPosition(300, 400);
}

void Player::hande_event(const sf::Event &event) {}

void Player::update() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    m_sprite.move(m_speed * -1, 0);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    m_sprite.move(m_speed, 0);
  }
}

const sf::Sprite &Player::sprite() const { return m_sprite; }
