#include <iostream>

#include "audioengine.hpp"
#include <SFML/Graphics.hpp>
#include <sol.hpp>

#include "player.hpp"

int main() {

  // load lua
  sol::state lua;
  lua.open_libraries(sol::lib::base, sol::lib::package);
  lua.script_file("settings.lua");
  
  
  AudioEngine m_audioEngine;

  //TODO: if audio init error, use null implementation
  m_audioEngine.initialize();

  // register
  lua["fmod"] = &m_audioEngine;
  lua["playOneShot"] = &AudioEngine::playOneShot;

  std::string title = lua["window"]["title"];
  int winWidth = lua["window"]["width"];
  int winHeight = lua["window"]["height"];
  
  sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), title);
  window.setFramerateLimit(60);

  sf::Texture gargTexture;
  if (!gargTexture.loadFromFile("garg.gif")) {
    std::cout << "Could not load garg.gif?!\n";
  }
  sf::Color background(17, 13, 42); // 17 13 42 is the background in the gif
 
  Player player(gargTexture, m_audioEngine, lua);

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

	player.handle_event(event);
      }
    }

    // update
    player.update();
    
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
    window.clear(background);
    //window.draw(playerSprite);
    window.draw(player.sprite());
    window.display();
  }

  return 0;
}
