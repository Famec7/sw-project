#pragma once
#include <stdio.h>
#include "Cursor.h"

void ShowBlock(int blockInfo[4][4])
{
	COORD curPos = GetCurrentCursorPos();

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			SetCurrentCursorPos(curPos.X + (x * 2), curPos.Y + y);
			if (blockInfo[y][x] == 1)
				printf("бс");
		}
	}
	SetCurrentCursorPos(curPos.X, curPos.Y);
}