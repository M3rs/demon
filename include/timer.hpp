#ifndef TIMER_HPP
#define TIMER_HPP

#include <SDL.h>

class Timer {
public:
	Timer();

	//returns time in seconds
	const double getDeltaTime();
	void restartTimer();
	void stopTimer();

private:
	Uint64 then;
	Uint64 now;
	double deltaTime;
	//std::chrono::high_resolution_clock Clock;

};

#endif //TIMER_HPP
