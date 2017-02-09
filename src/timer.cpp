#include "timer.hpp"
#include <SDL.h>

Timer::Timer() {
}

void Timer::restartTimer() {
	then = now;
}

void Timer::stopTimer() {
	now = SDL_GetPerformanceCounter();
	deltaTime = 
		(double)((now - then) * 1000) / (double)SDL_GetPerformanceFrequency();
}

const double Timer::getDeltaTime() { return deltaTime; }

