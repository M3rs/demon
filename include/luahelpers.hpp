#ifndef LUAHELPERS_HPP
#define LUAHELPERS_HPP

#include <SDL.h>
#include <stdio.h>

// forward declares
namespace sol {
  class state;
}

namespace sf {
  class RenderWindow;
}

class AudioEngine;

void register_fmod(sol::state& lua, AudioEngine& audio);
void register_window_sfml(sol::state& lua, sf::RenderWindow& window);
void register_window_sdl(sol::state& lua, SDL_Window* window, SDL_Surface* screenSurface);

#endif // LUAHELPERS_HPP
