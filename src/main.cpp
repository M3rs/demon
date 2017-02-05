#include <iostream>

#include "audioengine.hpp"
#include <SFML/Graphics.hpp>
#include <sol.hpp>
#include "textures.hpp"
#include "luahelpers.hpp"
#include "player.hpp"

int main() {

  // load lua
  sol::state lua;
  lua.open_libraries(sol::lib::base, sol::lib::package);
  lua.script_file("settings.lua");
  
  
  AudioEngine m_audioEngine;
  m_audioEngine.initialize(); //TODO: if audio init error, use null implementation

  sf::RenderWindow window;

  // register / initialize w/ lua
  register_fmod(lua, m_audioEngine);
  register_window(lua, window);

  Textures tx_cache;

  sf::Color background(17, 13, 42); // 17 13 42 is the background in the gif
 
  Player player(tx_cache, m_audioEngine, lua);


  while (window.isOpen()) {

    // handle input
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (event.type == sf::Event::KeyReleased) {
        switch (event.key.code) {
        case sf::Keyboard::Escape:
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
    m_audioEngine.update();


    // render
    window.clear(background);
    window.draw(player.sprite());
    window.display();
  }

  return 0;
}
