#include "Time.h"
#include <time.h>

clock_t clock_tick;

TimeStruct Time;

#define DELTA_TIME_MAX (0.05)

void InitTime()
{
	clock_tick = clock();
	Time.time = 0;
	Time.deltaTime = 0;
}

void UpdateTime()
{
	clock_t now_clock_tick = clock();
	clock_t delta = now_clock_tick - clock_tick;
	clock_tick = now_clock_tick;
	double deltaTime = (double)delta / CLOCKS_PER_SEC;

	Time.time += deltaTime;
	Time.deltaTime = deltaTime < DELTA_TIME_MAX ? deltaTime : DELTA_TIME_MAX;
}