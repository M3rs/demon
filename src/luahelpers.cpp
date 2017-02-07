#include "luahelpers.hpp"

#include "audioengine.hpp"
#include <SFML/Graphics.hpp>
#include <sol.hpp>

void register_fmod(sol::state &lua, AudioEngine &audio) {
  sol::table fmod = lua.create_table("fmod");
  fmod.set_function(
      "playOneShot",             // function name
      &AudioEngine::playOneShot, // class function address
      &audio); // instance of class (since it is a member function)
  fmod.set_function("playOneShotWithParameter",
                    &AudioEngine::playOneShotWithParameter, &audio);
}

void register_window_sfml(sol::state &lua, sf::RenderWindow &window) {
  std::string title = lua["window"]["title"];
  int winWidth = lua["window"]["width"];
  int winHeight = lua["window"]["height"];
  window.create(sf::VideoMode(winWidth, winHeight), title);

  // TODO(ajm): get fps from lua?
  window.setFramerateLimit(60);
}

void register_window_sdl(sol::state &lua, SDL_Window  *window, 
						SDL_Surface *screenSurface) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error %s\n", SDL_GetError());
	}
	else {
		std::string title = lua["window"]["title"];
		int winWidth = lua["window"]["width"];
		int winHeight = lua["window"]["height"];
		window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, 
								SDL_WINDOWPOS_UNDEFINED, winWidth, winHeight,
								SDL_WINDOW_SHOWN);
		if (window == NULL)
			printf("SDL Window could not be created! SDL_Error %s\n", SDL_GetError());
		else {
			screenSurface = SDL_GetWindowSurface(window);
			SDL_FillRect(screenSurface, NULL,
						SDL_MapRGB(screenSurface->format, 17, 13, 42));

			//additional initial shapes should render here

			SDL_UpdateWindowSurface(window);
			//SDL_Delay(4000); //debug purposes only
		}
	}

}

