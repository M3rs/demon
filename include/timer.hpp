#ifndef TIMER_HPP
#define TIMER_HPP

class Timer {
public:
	Timer();

	//returns time in ms
	const double getDeltaTime();
	void restartTimer();
	void stopTimer();

	Uint64 then;
	Uint64 now;
	double deltaTime;

private:

	//std::chrono::high_resolution_clock Clock;

};

#endif //TIMER_HPP
