#include "gameInfo.h"
#include <iostream>

int gameBoardInfo[GBOARD_HEIGHT + 1][GBOARD_WIDTH + 2] = {0, };

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

void DrawGameBoard(void)
{
    for (int y = 0; y <= GBOARD_HEIGHT; y++)
    {
        SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y);
        if (y == GBOARD_HEIGHT)
        {
            printf("¦¦");
            gameBoardInfo[GBOARD_HEIGHT][0] = MAP_BOUNDARY;
        }
        else if (y == 0) {
            printf("¦£");
            gameBoardInfo[0][0] = MAP_BOUNDARY;
        }
        else
        {
            printf("¦¢");
            gameBoardInfo[y][0] = MAP_BOUNDARY;
        }
    }
    for (int y = 0; y <= GBOARD_HEIGHT; y++)
    {
        SetCurrentCursorPos(GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2, GBOARD_ORIGIN_Y + y);
        if (y == GBOARD_HEIGHT)
        {
            printf(" ¦¥ ");
            gameBoardInfo[GBOARD_HEIGHT][GBOARD_WIDTH + 1] = MAP_BOUNDARY;
        }
        else if (y == 0) {
            printf(" ¦¤");
            gameBoardInfo[0][GBOARD_WIDTH + 1] = MAP_BOUNDARY;
        }
        else
        {
            printf(" ¦¢");
            gameBoardInfo[y][GBOARD_WIDTH + 1] = MAP_BOUNDARY;
        }
    }
    for (int x = 1; x <= GBOARD_WIDTH + 1; x++)
    {
        SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + GBOARD_HEIGHT);
        printf("¦¡");
        gameBoardInfo[GBOARD_HEIGHT][x] = MAP_BOUNDARY;
    }
    for (int x = 1; x <= GBOARD_WIDTH + 1; x++)
    {
        SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y);
        printf("¦¡");
        gameBoardInfo[0][x] = MAP_BOUNDARY;
    }


    SetCurrentCursorPos(GBOARD_ORIGIN_X + GBOARD_WIDTH, 0);
}