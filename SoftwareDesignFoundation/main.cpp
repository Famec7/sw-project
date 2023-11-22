#include "Boss.h"
#include "Bullet.h"
#include "Item.h"
#include "NormalMob.h"
#include "Render.h"
#include "player.h"

int main() {
	srand(time(NULL));
	int key;
	COORD pos;
	ItemInit();
	RemoveCursor();
	SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y);
	system("mode con:cols=100 lines=50");

	ShowBossHpUI();
	InitTime();
	playerInit();
	PlayerShowModel();
	DrawGameBoard();
	while (1) {
		ProcessKeyInput();
		UpdateTime();
		UpdateBullet();
		UpdateItem();
		NormalMobUpdate();
		BossUpdate();
		UpdateItem();
		PlayerUpdate();
		PlayerStatOutput();
		ManageShield();

		if (IsGameOver()) {
			SetCurrentCursorPos(25, 25);
			printf("GAME OVER!!");
			return 0;
		}
	}
	getchar();

	return 0;
	return 0;
}