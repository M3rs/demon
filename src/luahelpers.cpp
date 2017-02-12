#include "luahelpers.hpp"

#include "audioengine.hpp"
#include <sol.hpp>

namespace {
  bool KeyPressed(const std::string& key_name)
  {
    auto input = SDL_GetKeyboardState(NULL);
    return input[SDL_GetScancodeFromName(key_name.c_str())];
  }
}

void register_fmod(sol::state &lua, AudioEngine &audio) {
  sol::table fmod = lua.create_table("fmod");
  fmod.set_function(
      "playOneShot",             // function name
      &AudioEngine::playOneShot, // class function address
      &audio); // instance of class (since it is a member function)
  fmod.set_function("playOneShotWithParameter",
                    &AudioEngine::playOneShotWithParameter, &audio);
  fmod.set_function("playEvent", &AudioEngine::playEvent, &audio);
  fmod.set_function("stopEvent", &AudioEngine::stopEvent, &audio);
}

void register_input(sol::state& lua)
{
  sol::table key = lua.create_table("kbd");
  key.set_function("isPressed", &KeyPressed);
}
