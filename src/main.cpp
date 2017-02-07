#include <iostream>

#include "audioengine.hpp"
//#include <SFML/Graphics.hpp>
#include <sol.hpp>
#include "textures.hpp"
#include "luahelpers.hpp"
#include "player.hpp"

int main(int argc, char* args[]) {

  // load lua
  sol::state lua;
  lua.open_libraries(sol::lib::base, sol::lib::package);
  lua.script_file("settings.lua");
  
  
  AudioEngine m_audioEngine;
  m_audioEngine.initialize(); //TODO: if audio init error, use null implementation

  //sf::RenderWindow window;
  SDL_Window* window(NULL);
  SDL_Surface* screenSurface(NULL);
  const Uint8* keyboardState(NULL);

  // register / initialize w/ lua
  register_fmod(lua, m_audioEngine);
  //register_window_sfml(lua, window);
  register_window_sdl(lua, window, screenSurface);

  Textures tx_cache;

  sf::Color background(17, 13, 42); // 17 13 42 is the background in the gif
 
  Player player(tx_cache, lua);
  // floor
  sf::RectangleShape floor;
  floor.setSize(sf::Vector2f(640, 50));
  floor.setPosition(0, 400);
  floor.setFillColor(sf::Color::White);

  std::cin.get();

  SDL_PumpEvents();
  keyboardState = SDL_GetKeyboardState(NULL);
  char* keyToPoll = "Space";
 
  bool quit = false;
  SDL_Event e;

  while (!quit) {
	  while (SDL_PollEvent(&e) != 0) {
		  //handle inputs
		  if (e.type == SDL_QUIT) {
			  quit = true;
		  }
	  }
	  //update state
	  SDL_UpdateWindowSurface(window);
  }


  /*
  while (window.isOpen()) {

    // handle input
    //sf::Event event;

	  
		  


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
    window.draw(floor);
    window.draw(player.sprite());
    window.display();
  }
  */

  //SDL cleanup
  SDL_DestroyWindow(window);
  window = NULL;
  SDL_Quit();

  return 0;
}
