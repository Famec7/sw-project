#include "gameInfo.h"
#include <iostream>

int gameBoardInfo[GBOARD_HEIGHT + 1][GBOARD_WIDTH + 2] = {0, };

void DrawGameBoard(void)
{
    for (int y = 0; y <= GBOARD_HEIGHT; y++)
    {
        SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y);
        if (y == GBOARD_HEIGHT)
        {
            printf("��");
            gameBoardInfo[GBOARD_HEIGHT][0] = MAP_BOUNDARY;
        }
        else if (y == 0) {
            printf("��");
            gameBoardInfo[0][0] = MAP_BOUNDARY;
        }
        else
        {
            printf("��");
            gameBoardInfo[y][0] = MAP_BOUNDARY;
        }
    }
    for (int y = 0; y <= GBOARD_HEIGHT; y++)
    {
        SetCurrentCursorPos(GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2, GBOARD_ORIGIN_Y + y);
        if (y == GBOARD_HEIGHT)
        {
            printf(" �� ");
            gameBoardInfo[GBOARD_HEIGHT][GBOARD_WIDTH + 1] = MAP_BOUNDARY;
        }
        else if (y == 0) {
            printf(" ��");
            gameBoardInfo[0][GBOARD_WIDTH + 1] = MAP_BOUNDARY;
        }
        else
        {
            printf(" ��");
            gameBoardInfo[y][GBOARD_WIDTH + 1] = MAP_BOUNDARY;
        }
    }
    for (int x = 1; x <= GBOARD_WIDTH + 1; x++)
    {
        SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + GBOARD_HEIGHT);
        printf("��");
        gameBoardInfo[GBOARD_HEIGHT][x] = MAP_BOUNDARY;
    }
    for (int x = 1; x <= GBOARD_WIDTH + 1; x++)
    {
        SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y);
        printf("��");
        gameBoardInfo[0][x] = MAP_BOUNDARY;
    }


    SetCurrentCursorPos(GBOARD_ORIGIN_X + GBOARD_WIDTH, 0);
}

void InitBoard()
{
    for (int y = 0; y <= GBOARD_HEIGHT; y++)
    {
        for (int x = 0; x <= GBOARD_WIDTH + 1; x++)
        {
            gameBoardInfo[y][x] = 0;
        }
    }
}

int IsAscII(int num)
{
    if (num >= 65 && num <= 90)
        return 1;
    else if (num >= 97 && num <= 122)
        return 1;
    else
        return 0;
}