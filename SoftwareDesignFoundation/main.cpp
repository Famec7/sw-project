#include <stdio.h>
#include "player.h"
#include "Boss.h"

int main()
{
	RemoveCursor();
	SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y);
	SetCurrentCursorPos(50, 100);
	while (1)
	{
		PlayerShowModel();
		/*ShowBossModel(bossModel[boss.curPhase]);*/
	}
	getchar();


	return 0;
}