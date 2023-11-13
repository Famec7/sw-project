#include "Boss.h"
#include "Bullet.h"
#include "player.h"

int main()
{
	RemoveCursor();
	SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y);
	system("mode con:cols=100 lines=50");

	DrawGameBoard();
	ShowBossHpUI();
	InitTime();
	playerInit();
	PlayerShowModel();
	while (1) {
		ProcessKeyInput();
		UpdateTime();
		BossUpdate();
		UpdateBullet();
		Sleep(100);
	}
	getchar();

	return 0;
}