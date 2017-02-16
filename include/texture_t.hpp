#ifndef TEXTURE_T_HPP
#define TEXTURE_T_HPP

#include <SDL.h>

class Texture_T {
public:
	Texture_T(SDL_Renderer* renderer, SDL_Surface* surface);
	~Texture_T();

	SDL_Texture* get();

private:
	SDL_Texture* sdl_text;
};

#endif //TEXTURE_T_HPP