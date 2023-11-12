#include "gameInfo.h"
#include <iostream>

int gameBoardInfo[GBOARD_HEIGHT + 1][GBOARD_WIDTH + 2] = {0, };

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

void DrawGameBoard(void)
{
    for (int y = 0; y <= GBOARD_HEIGHT; y++)
    {
        SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y);
        if (y == GBOARD_HEIGHT)
        {
            printf("¦¦");
        }
        else if (y == 0) {
            printf("¦£");
        }
        else
        {
            printf("¦¢");
        }
    }
    for (int y = 0; y <= GBOARD_HEIGHT; y++)
    {
        SetCurrentCursorPos(GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2, GBOARD_ORIGIN_Y + y);
        if (y == GBOARD_HEIGHT)
        {
            printf(" ¦¥ ");
        }
        else if (y == 0) {
            printf(" ¦¤");
        }
        else
        {
            printf(" ¦¢");
        }
    }
    for (int x = 1; x <= GBOARD_WIDTH + 1; x++)
    {
        SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + GBOARD_HEIGHT);
        printf("¦¡");
    }
    for (int x = 1; x <= GBOARD_WIDTH + 1; x++)
    {
        SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y);
        printf("¦¡");
    }


    SetCurrentCursorPos(GBOARD_ORIGIN_X + GBOARD_WIDTH, 0);
}