#include <iostream>
#include "audioengine.hpp"
#include "textures.hpp"
#include "luahelpers.hpp"
#include "player.hpp"
#include "renderer.hpp"

int main(int argc, char* args[]) {

  // load lua
  sol::state lua;
  lua.open_libraries(sol::lib::base, sol::lib::package);
  lua.script_file("res/scripts/settings.lua"); 
  
  AudioEngine m_audioEngine;
  m_audioEngine.initialize(); //TODO: if audio init error, use null implementation

  Renderer m_renderer;
  if (!(m_renderer.initialize(lua))) {
	  std::cout << "Renderer could not initialize; refer to SDL ErrorCodes.\n";
	  std::cout << "Please resolve and try running again.\n";
	  std::cin.get(); // if you run with Control+F5, you shouldn't need this ;)
  }
  const Uint8* keyboardState(NULL);

  // register / initialize w/ lua
  register_fmod(lua, m_audioEngine);

  Textures tx_cache;
 
  Player player(tx_cache, lua);
  // floor
  /*
  sf::RectangleShape floor;
  floor.setSize(sf::Vector2f(640, 50));
  floor.setPosition(0, 400);
  floor.setFillColor(sf::Color::White);
  */
 
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

	  //draw
	  m_renderer.update();
  }

  return 0;
}
