#include <iostream>

#include "audioengine.hpp"
#include <SFML/Graphics.hpp>

int main() {

  AudioEngine m_audioEngine;

  sf::RenderWindow window(sf::VideoMode(800, 600), "StarCraft!");

  sf::Texture factoryTexture;
  if (!factoryTexture.loadFromFile("Factory.png")) {
    std::cout << "Could not load Factory.png?!\n";
  }
  auto factorySprite = sf::Sprite(factoryTexture);

  int minerals = 1000;

  std::cout << "Please press the number of the unit you want to build."
            << std::endl;
  std::cout << "1. Ghost" << std::endl;
  std::cout << "2. Thor" << std::endl;
  std::cout << "3. Siege Tank" << std::endl;
  std::cout << "4. Quit application" << std::endl;

  while (window.isOpen()) {
    int input = 0;
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

    window.clear();
    window.draw(factorySprite);
    window.display();
  }

  return 0;
}
