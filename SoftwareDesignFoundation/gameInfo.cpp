#include "gameInfo.h"
#include <iostream>

int gameBoardInfo[GBOARD_HEIGHT + 1][GBOARD_WIDTH + 2];

clock_t clock_tick;

TimeStruct Time;

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
	Time.deltaTime = deltaTime;
}