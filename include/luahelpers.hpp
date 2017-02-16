#ifndef LUAHELPERS_HPP
#define LUAHELPERS_HPP

#include <SDL.h>
#include <stdio.h>

// forward declares
namespace sol {
  class state;
}

class AudioEngine;

void register_fmod(sol::state& lua, AudioEngine& audio);
void register_window_sdl(sol::state& lua, SDL_Window* window, SDL_Surface* screenSurface);

void register_input(sol::state& lua);
void register_physicsbody(sol::state& lua);
void register_sprite(sol::state& lua);

#endif // LUAHELPERS_HPP
