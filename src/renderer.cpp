#include "renderer.hpp"

#include <SDL.h>
#include <sol.hpp>
#include <stdio.h>
#include <string>

Renderer::Renderer() : window(NULL), renderer(NULL) {}

Renderer::~Renderer() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

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

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    printf("SDL Window could not be created! SDL_Error %s\n", SDL_GetError());
    return false;
  }

  return true;
}

void Renderer::update() {

  SDL_SetRenderDrawColor(renderer, 17, 13, 42, 255);

  SDL_RenderClear(renderer);

  // draw stuff here
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_Rect floor {0, 400, 640, 50};
  SDL_RenderFillRect(renderer, &floor);
  
  SDL_RenderPresent(renderer);
}
