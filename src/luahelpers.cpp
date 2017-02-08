#include "luahelpers.hpp"

#include "audioengine.hpp"
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

