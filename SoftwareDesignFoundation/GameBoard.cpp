#include "GameBoard.h"

void SetGameBoard() {
    for (int y = 0; y < GBOARD_HEIGHT; y++)
    {
        gameBoardInfo[y][0] = 1;
        gameBoardInfo[y][GBOARD_WIDTH + 1] = 1;
    }
    for (int x = 0; x < GBOARD_WIDTH + 2; x++)
    {
        gameBoardInfo[GBOARD_HEIGHT][x] = 1;
    }
}

void AddGameBoard(COORD pos, int element) {
    int arrCurX, arrCurY;
    arrCurX = (pos.X - GBOARD_ORIGIN_X) / 2;
    arrCurY = pos.Y - GBOARD_ORIGIN_Y;
    gameBoardInfo[pos.Y][pos.X] = element;
}