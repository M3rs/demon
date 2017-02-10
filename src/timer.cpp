#include "timer.hpp"


Timer::Timer() {
}

void Timer::restartTimer() {
	then = now;
}

void Timer::stopTimer() {
	now = SDL_GetPerformanceCounter();
	deltaTime = 
		(double)(now - then) / (double)SDL_GetPerformanceFrequency();
}

const double Timer::getDeltaTime() { return deltaTime; }

