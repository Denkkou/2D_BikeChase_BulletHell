#ifndef anFPSDelayFile
#define anFPSDelayFile

#include <iostream>
#include <SDL.h>

class FPSDelayTimer {
public:
	FPSDelayTimer();

	void resetTicks();
	int getTicks();
private:
	int startTicks;
};

#endif