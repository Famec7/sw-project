#include "Boss.h"
#include "player.h"

int main()
{
	RemoveCursor();
	SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y);
	system("mode con:cols=100 lines=50");

	ShowBossHpUI();
	while (1) {
		PlayerStatOutput();
		ShowBossModel();
		PlayerShowModel();
	}
	getchar();


	return 0;
}