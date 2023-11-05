#include <stdio.h>
#include "Cursor.h"
#include "Block.h"
#include "Boss.h"

int main()
{
	RemoveCursor();
	SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y);
	ShowBossModel(bossModel[curBossPhase]);
	ShowBossHpUI();
	getchar();

	return 0;
}