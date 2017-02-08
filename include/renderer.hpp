#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SDL.h>
#include <stdio.h>
#include <string>
#include <sol.hpp>

class Renderer {
public:
	Renderer();
	~Renderer();

	void update();
	bool initialize(sol::state& lua);

private:
	SDL_Window*		window;
	SDL_Surface*	screenSurface;
	SDL_Renderer*	renderer;
};



#endif //RENDERER_HPP
