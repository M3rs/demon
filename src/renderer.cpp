#include "renderer.hpp"

#include <SDL_Image.h>
#include <sol.hpp>
#include <stdio.h>
#include <string>

Renderer::Renderer() : window(NULL), renderer(NULL) {}

Renderer::~Renderer() {

  //tmp
  SDL_DestroyTexture(texture);
    
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

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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

  //SDL_SetRenderDrawColor(renderer, 17, 13, 42, 255);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  SDL_RenderClear(renderer);

  // draw stuff here
  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
  SDL_Rect floor{0, 400, 640, 50};
  SDL_RenderFillRect(renderer, &floor);
   
  //HACK: turned off the draw call here so the BG doesn't draw over the sprite
  //...effectively reversing the draw order from what appears in main
  //Will resolve the order of calls properly once a less hacky Renderer registry
  //is in place

  //SDL_RenderPresent(renderer);
}

SDL_Renderer* Renderer::getRenderer()
{
	return renderer;
}