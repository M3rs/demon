#include <iostream>

#include "audioengine.hpp"
#include <SFML/Graphics.hpp>

int main() {

  AudioEngine m_audioEngine;

  sf::RenderWindow window(sf::VideoMode(800, 600), "StarCraft!");
  window.setFramerateLimit(60);

  sf::Texture gargTexture;
  if (!gargTexture.loadFromFile("garg.gif")) {
    std::cout << "Could not load garg.gif?!\n";
  }
  sf::Sprite playerSprite(gargTexture);
  playerSprite.setTextureRect(sf::IntRect(0, 32, 32, 50));

  int speed = 2;

  int minerals = 1000;

  std::cout << "Please press the number of the unit you want to build."
            << std::endl;
  std::cout << "1. Ghost" << std::endl;
  std::cout << "2. Thor" << std::endl;
  std::cout << "3. Siege Tank" << std::endl;
  std::cout << "4. Quit application" << std::endl;

  while (window.isOpen()) {
    int input = 0;

    // handle input
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (event.type == sf::Event::KeyReleased) {
        switch (event.key.code) {
        case sf::Keyboard::Num1:
          input = 1;
          break;
        case sf::Keyboard::Num2:
          input = 2;
          break;
        case sf::Keyboard::Num3:
          input = 3;
          break;
        case sf::Keyboard::Num4:
          window.close();
          break;
        default:
          break;
        }
      }
    }

    // update
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      playerSprite.move(speed * -1, 0);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      playerSprite.move(speed, 0);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
      playerSprite.move(0, speed * -1);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
      playerSprite.move(0, speed);
    }
    
    if (input == 1) {
      if (minerals >= 200) {
        m_audioEngine.playOneShot("event:/ghost");
        minerals -= 200;
      } else {
        m_audioEngine.playOneShot("event:/mineralerror");
      }
    }
    if (input == 2) {
      if (minerals >= 400) {
        m_audioEngine.playOneShot("event:/thor");
        minerals -= 400;
      } else {
        m_audioEngine.playOneShot("event:/mineralerror");
      }
    }
    if (input == 3) {
      if (minerals >= 150) {
        m_audioEngine.playOneShot("event:/siegetank");
        minerals -= 150;
      } else {
        m_audioEngine.playOneShot("event:/mineralerror");
      }
    }

    m_audioEngine.update();

    // render
    window.clear();
    window.draw(playerSprite);
    window.display();
  }

  return 0;
}
