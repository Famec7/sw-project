#include "Boss.h"
#include "Bullet.h"
#include "Item.h"
#include "NormalMob.h"
#include "Render.h"
#include "player.h"

int main() {
	double t = 5;
	srand(time(NULL));
	int key, k=0;
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
	ScreenInit();
	StartLazerState();
	while (1) {
		if(t<0 && k==0) ShootLazer();
		if(k==0)t -= Time.deltaTime;
		if (HP < 5) {
			k = 1;
			HP = 10;
			StopLazer();
			DeleteLazerBlock();
			DeleteLazerWall();
		}
		Render();
		ProcessKeyInput();
		UpdateTime();
		UpdateBullet();
		UpdateItem();
		NormalMobUpdate();
		//UpdateBoss();
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
}