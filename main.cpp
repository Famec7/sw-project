#include "Boss.h"
#include "Bullet.h"
#include "player.h"
#include "Item.h"

int main() {
	srand(time(NULL));
	int key;
	COORD pos;
	ItemInit();
	while (1) {
		if (!_kbhit()) {
			key = _getch();
			if (key == 'i') {
				pos.X = rand() % 40 + 8;
				pos.Y = rand() % 40 + 3;
				DropItem(pos);
			}
			if (key == 'q') {
				break;
			}
		}
	}
	getchar();

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