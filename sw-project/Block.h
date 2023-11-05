#pragma once
#include <stdio.h>
#include "Cursor.h"
#include "gameInfo.h"

void ShowBlock(char blockInfo[][10], int xSize, int ySize, int info)
{
	COORD curPos = GetCurrentCursorPos();
	int arrX = (curPos.X - GBOARD_ORIGIN_X) / 2;
	int arrY = curPos.Y - GBOARD_ORIGIN_Y;

	for (int y = 0; y < ySize; y++)
	{
		for (int x = 0; x < xSize; x++)
		{
			SetCurrentCursorPos(curPos.X + (x * 2), curPos.Y + y);
			if (blockInfo[y][x] != ' ') {
				printf("%c", blockInfo[y][x]);
				gameBoardInfo[arrY + y][arrX + x] = info;
			}
		}
	}
	SetCurrentCursorPos(curPos.X, curPos.Y);
}

void DeleteBlock(char blockInfo[][10], int xSize, int ySize)
{
	COORD curPos = GetCurrentCursorPos();
	int arrX = (curPos.X - GBOARD_ORIGIN_X) / 2;
	int arrY = curPos.Y - GBOARD_ORIGIN_Y;

	for (int y = 0; y < ySize; y++)
	{
		for (int x = 0; x < xSize; x++)
		{
			SetCurrentCursorPos(curPos.X + (x * 2), curPos.Y + y);
			if (blockInfo[y][x] != ' ')
			{
				printf("  ");
				gameBoardInfo[arrY + y][arrX + x] = 0;
			}
		}
	}
	SetCurrentCursorPos(curPos.X, curPos.Y);
}