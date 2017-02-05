#ifndef LUAHELPERS_HPP
#define LUAHELPERS_HPP

// forward declares
namespace sol {
  class state;
}

namespace sf {
  class RenderWindow;
}

class AudioEngine;

void register_fmod(sol::state& lua, AudioEngine& audio);
void register_window(sol::state& lua, sf::RenderWindow& window);

#endif // LUAHELPERS_HPP
