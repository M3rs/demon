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

void register_window(sol::state &lua, sf::RenderWindow &window) {
  std::string title = lua["window"]["title"];
  int winWidth = lua["window"]["width"];
  int winHeight = lua["window"]["height"];
  window.create(sf::VideoMode(winWidth, winHeight), title);

  // TODO(ajm): get fps from lua?
  window.setFramerateLimit(60);
}
