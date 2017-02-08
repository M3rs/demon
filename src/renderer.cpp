#include "renderer.hpp"

Renderer::Renderer() : window(NULL), screenSurface(NULL), renderer(NULL) {

}

Renderer::~Renderer() {
	//window destroys surface as well
	SDL_DestroyWindow(window);
	window = NULL;

	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	SDL_Quit();
}

bool Renderer::initialize(sol::state& lua) {
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			printf("SDL could not initialize! SDL_Error %s\n", SDL_GetError());
			return false;
		}
		else {
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
			else {
				screenSurface = SDL_GetWindowSurface(window);
				SDL_FillRect(screenSurface, NULL,
					SDL_MapRGB(screenSurface->format, 17, 13, 42));

				//additional initial shapes should render here

				SDL_UpdateWindowSurface(window);
			}
		}
		return true;
}

void Renderer::update() { SDL_UpdateWindowSurface(window); }
