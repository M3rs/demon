#ifndef SDLHELPERS_HPP
#define SDLHELPERS_HPP

#include <SDL.h>
#include <memory>

struct SDL_Deleter{void operator()(SDL_Texture *t)
                       const {
    if (t) {
      SDL_DestroyTexture(t);
    }
  }
};

using Texture_ptr = std::unique_ptr<SDL_Texture, SDL_Deleter>;

#endif // SDLHELPERS_HPP
