#include <iostream>

#include "audioengine.hpp"
#include <sol.hpp>
#include "textures.hpp"
#include "luahelpers.hpp"
#include "player.hpp"

int main(int argc, char* args[]) {

  // load lua
  sol::state lua;
  lua.open_libraries(sol::lib::base, sol::lib::package);
  lua.script_file("res/scripts/settings.lua"); 
  
  AudioEngine m_audioEngine;
  m_audioEngine.initialize(); //TODO: if audio init error, use null implementation

  //sf::RenderWindow window;
  SDL_Window* window(NULL);
  SDL_Surface* screenSurface(NULL);
  const Uint8* keyboardState(NULL);

  // register / initialize w/ lua
  register_fmod(lua, m_audioEngine);
  register_window_sdl(lua, window, screenSurface);

  Textures tx_cache;

  //sf::Color background(17, 13, 42); // 17 13 42 is the background in the gif
 
  Player player(tx_cache, lua);
  // floor
  /*
  sf::RectangleShape floor;
  floor.setSize(sf::Vector2f(640, 50));
  floor.setPosition(0, 400);
  floor.setFillColor(sf::Color::White);
  */

  //SDL_PumpEvents();
  
  //char* keyToPoll = "Space";
 
  bool quit = false;
  SDL_Event e;

  while (!quit) {
	  while (SDL_PollEvent(&e) != 0) {
		  //manually X'ing out the window
		  if (e.type == SDL_QUIT) {
			  quit = true;
		  }
		  else if (e.type == SDL_KEYDOWN) {
			  if (e.key.keysym.sym == SDLK_ESCAPE) {
				  quit = true;
			  }
			  //handle discrete inputs
			  player.handle_event(e.key.keysym.sym);
		  }
	  }
	  //handle continuous inputs
	  keyboardState = SDL_GetKeyboardState(NULL);
	  player.update(keyboardState);

	  //update subsystems
	  m_audioEngine.update();

	  //update window
	  SDL_UpdateWindowSurface(window);
  }

  //SDL cleanup
  SDL_DestroyWindow(window);
  window = NULL;
  SDL_Quit();

  return 0;
}
