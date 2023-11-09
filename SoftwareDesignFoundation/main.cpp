#include <stdio.h>
#include "Cursor.h"
#include "Block.h"
#include "player.h"
#include "gameInfo.h"
#include "Boss.h"

int main()
{
	RemoveCursor();
	SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y);
	system("mode con:cols=100 lines=50");

	while (1) {
		ShowBossModel(bossModel[boss.curPhase]);
		PlayerShowModel();
	}
	getchar();


	return 0;
}