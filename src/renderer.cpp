#include "renderer.hpp"

#include <SDL_Image.h>
#include <sol.hpp>
#include <stdio.h>
#include <string>
#include <iostream>
#include "physicsbody.hpp"

Renderer::Renderer() : window(NULL), renderer(NULL),
		       m_drawlist(std::map<std::string, Sprite>{}) {}

Renderer::~Renderer() {

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  IMG_Quit();

  SDL_Quit();
}

bool Renderer::initialize(sol::state &lua) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error %s\n", SDL_GetError());
    return false;
  }
  std::string title = lua["window"]["title"];
  int winWidth = lua["window"]["width"];
  int winHeight = lua["window"]["height"];
  window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, winWidth, winHeight,
                            SDL_WINDOW_SHOWN);
  if (window == NULL) {
    printf("SDL Window could not be created! SDL_Error %s\n", SDL_GetError());
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                                SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL) {
    printf("SDL Window could not be created! SDL_Error %s\n", SDL_GetError());
    return false;
  }

  // copied from img docs
  // load support for the JPG and PNG image formats
  int flags = IMG_INIT_JPG | IMG_INIT_PNG;
  int initted = IMG_Init(flags);
  if ((initted & flags) != flags) {
    printf("IMG_Init: Failed to init required jpg and png support!\n");
    printf("IMG_Init: %s\n", IMG_GetError());
    return false;
  }

  return true;
}

void Renderer::update() {

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  SDL_RenderClear(renderer);

  // draw stuff here

  // TODO(ajm): add method o create this texture
  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

  for (auto& draw : m_drawlist) {
    auto& sprite = draw.second;
    SDL_RenderCopy(renderer, sprite.texture, &sprite.texture_coords, &sprite.world_coords);
  }

   SDL_RenderPresent(renderer);
}

SDL_Renderer *Renderer::getRenderer() { return renderer; }


Sprite* Renderer::add_sprite(const std::string& key)
{
  auto it = m_drawlist.find(key);
  if (it != m_drawlist.end()) {
    std::cout << "Drawlist already contains " << key << std::endl;
    return &m_drawlist[key];
  }

  m_drawlist.emplace(key, Sprite());

  return &m_drawlist[key];
}

void Renderer::remove_sprite(const std::string& key)
{
  m_drawlist.erase(key);
}
