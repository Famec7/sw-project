#include "Boss.h"
#include "Bullet.h"
#include "player.h"

int main()
{
	RemoveCursor();
	SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y);
	system("mode con:cols=100 lines=50");

	ShowBossHpUI();
	InitTime();
	while (1) {
		UpdateTime();
		BossUpdate();
		UpdateBullet();
		Sleep(100);
	}
	getchar();

	return 0;
}