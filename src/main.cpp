#include "audioengine.hpp"
#include "luahelpers.hpp"
#include "physicsengine.hpp"
#include "player.hpp"
#include "renderer.hpp"
#include "sprite.hpp"
#include "textures.hpp"
#include "timer.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *args[]) {

  // load lua
  sol::state lua;
  lua.open_libraries(sol::lib::base, sol::lib::package);
  lua.script_file("res/scripts/settings.lua");

  AudioEngine m_audioEngine;
  m_audioEngine
      .initialize(); // TODO: if audio init error, use null implementation

  Renderer m_renderer;
  if (!(m_renderer.initialize(lua))) {
    std::cout << "Renderer could not initialize; refer to SDL ErrorCodes.\n";
    std::cout << "Please resolve and try running again.\n";
    std::cin.get(); // if you run with Control+F5, you shouldn't need this ;)
  }

  // register / initialize w/ lua
  register_fmod(lua, m_audioEngine);
  register_input(lua);
  register_physicsbody(lua);
  register_sprite(lua);

  Textures tx_cache(m_renderer.getRenderer());
  tx_cache.loadTexture("res/images/garg.gif");
  tx_cache.loadTexture("res/images/big.gif");

  PhysicsEngine m_physicsEngine;

  // entity composition
  Sprite *player_sprite = m_renderer.add_sprite("player");
  PhysicsBody *player_pb =
      m_physicsEngine.create_physBody("player", player_sprite);
  Player player(tx_cache, lua, "res/scripts/player.lua", "player",
                player_sprite, player_pb);

  Sprite *floor_sprite = m_renderer.add_sprite("floor");
  PhysicsBody *floor_pb =
      m_physicsEngine.create_physBody("floor", floor_sprite);
  Player floor(tx_cache, lua, "res/scripts/floor.lua", "floor", floor_sprite,
               floor_pb);

  Sprite *box_sprite = m_renderer.add_sprite("box");
  PhysicsBody *box_pb = m_physicsEngine.create_physBody("box", box_sprite);
  Player box(tx_cache, lua, "res/scripts/box.lua", "box", box_sprite, box_pb);

  Timer timer = Timer();

  bool quit = false;
  SDL_Event e;

  std::cout << "before loop";

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
        player.handle_event(e.key.keysym.sym);
      }
    }

    // -- update
    // update all entity / things
    auto dt = timer.getDeltaTime();
    player.update(dt);

    // check physics
    m_physicsEngine.update();

    // update subsystems
    m_audioEngine.update();

    // -- end update

    // draw
    m_renderer.update();

    timer.stopTimer();

    // std::cout << "\rFrame time was: " << timer.getDeltaTime();
  }

  return 0;
}
