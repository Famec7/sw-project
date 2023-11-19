#include "Boss.h"
#include "Bullet.h"
#include "player.h"
#include "Item.h"

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
	pos.X = 30;
	pos.Y = 6;
	DropItem(pos);
	while (1) {
		ProcessKeyInput();
		UpdateTime();
		UpdateBullet();
		UpdateItem();
		//BossUpdate();
		PlayerUpdate();
		PlayerStatOutput();
		ManageShield();

		if (IsGameOver()) {
			SetCurrentCursorPos(25, 25);
			printf("GAME OVER!!");
			return 0;
		}
		Sleep(100);
	}
	getchar();

	return 0;
	return 0;
}

/*
int main()
{
	srand(time(NULL));
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
		BossUpdate();
		PlayerUpdate();
		PlayerStatOutput();
		ManageShield();

		if (IsGameOver()) {
			SetCurrentCursorPos(25, 25);
			printf("GAME OVER!!");
			return 0;
		}
		Sleep(100);
	}
	getchar();

	return 0;
}
*/