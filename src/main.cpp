#include "audioengine.hpp"
#include "luahelpers.hpp"
#include "player.hpp"
#include "renderer.hpp"
#include "sprite.hpp"
#include "textures.hpp"
#include "timer.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// hack for proper player/entity manager

int main(int argc, char *args[]) {

  // load lua
  sol::state lua;
  lua.open_libraries(sol::lib::base, sol::lib::package);
  lua.script_file("res/scripts/settings.lua");

  AudioEngine m_audioEngine;
  m_audioEngine.initialize(); // TODO: if audio init error, use null implementation

  Renderer m_renderer;
  if (!(m_renderer.initialize(lua))) {
    std::cout << "Renderer could not initialize; refer to SDL ErrorCodes.\n";
    std::cout << "Please resolve and try running again.\n";
    std::cin.get(); // if you run with Control+F5, you shouldn't need this ;)
  }
  
  // register / initialize w/ lua
  register_fmod(lua, m_audioEngine);
  register_input(lua);

  Textures tx_cache(m_renderer.getRenderer());
  tx_cache.loadTexture("res/images/garg.gif");
  tx_cache.loadTexture("res/images/big.gif");

  std::vector<Player> entities;

  Sprite* player_sprite = m_renderer.add_sprite("player");
  //Player player(tx_cache, lua, "res/scripts/player.lua", "player", player_sprite);
  entities.push_back(Player{tx_cache, lua, "res/scripts/player.lua", "player", player_sprite});

  //obviously a hack, but our floor 'player' will not input update
  Sprite* floor_sprite = m_renderer.add_sprite("floor");
  //Player floor(tx_cache, lua, "res/scripts/floor.lua", "floor", floor_sprite);
  entities.push_back(Player{tx_cache, lua, "res/scripts/floor.lua", "floor", floor_sprite});

  Sprite* box_sprite = m_renderer.add_sprite("box");
  //Player box(tx_cache, lua, "res/scripts/box.lua", "box", box_sprite);
  entities.push_back(Player{tx_cache, lua, "res/scripts/box.lua", "box", box_sprite});

  Timer timer = Timer();

  bool quit = false;
  SDL_Event e;

  while (!quit) {
    timer.restartTimer();
    while (SDL_PollEvent(&e) != 0) {
      // manually X'ing out the window
      if (e.type == SDL_QUIT) {
        quit = true;
      } else if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_ESCAPE) {
          quit = true;
        }
        // handle discrete inputs
        //player.handle_event(e.key.keysym.sym);
	for (auto& en : entities) {
	  en.handle_event(e.key.keysym.sym);
	}
      }
    }

    // -- update
    // update all entity / things
    auto dt = timer.getDeltaTime();
    for (auto& e : entities) {
      e.update(dt);
    }

    // check physics

    // update subsystems
    m_audioEngine.update();

    // check if any entity is dead, remove
    auto cleanup_iter = std::remove_if(entities.begin(),
				       entities.end(),
				       [&](auto& e) { return !e.isAlive(); });
    
    for (auto& it = cleanup_iter; it != entities.end(); it++) {
      m_renderer.remove_sprite(it->getId());
    }
    entities.erase(cleanup_iter);


    // -- end update

    // draw
    m_renderer.update();

    timer.stopTimer();

    // std::cout << "\rFrame time was: " << timer.getDeltaTime();
  }

  return 0;
}
