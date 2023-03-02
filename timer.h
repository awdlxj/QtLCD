#pragma once

class timer
{
public:
	double gettimerfreq();
	bool starttimer();
	double getthroughtime();
	double endtimer();
	timer();

private:
	double timerfreq;//µ¥Î»£ºHz
	long long startcycle;
};

bool cls();