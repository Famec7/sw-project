#include "Boss.h"
#include "Bullet.h"
#include "Item.h"
#include "NormalMob.h"
#include "Render.h"
#include "player.h"
#include "StartPage.h"

int main() {
	double t = 5;
	srand(time(NULL));
	int key, isStartPage;
	COORD pos;
	ItemInit();
	RemoveCursor();
	SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y);
	system("mode con:cols=100 lines=50");

	InitTime();
	playerInit();
	PlayerShowModel();
	ScreenInit();
	InitText();
	while (1) {
		isStartPage = UpdateText();
		if (isStartPage == 0) break;
		Render();
		ProcessKeyInput();
		UpdateTime();
		UpdateBullet();
		PlayerUpdate();
	}

	ShowBossHpUI();
	InitTime();
	playerInit();
	PlayerShowModel();
	DrawGameBoard();
	ScreenInit();

	while (1) {
		HP = 10;
		Render();
		ProcessKeyInput();
		UpdateTime();
		UpdateBullet();
		UpdateItem();
		NormalMobUpdate();
		UpdateBoss();
		UpdateItem();
		PlayerUpdate();
		//PlayerStatOutput();
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



//int main() {
//	double t = 5;
//	srand(time(NULL));
//	int key, k=0;
//	COORD pos;
//	ItemInit();
//	RemoveCursor();
//	SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y);
//	system("mode con:cols=100 lines=50");
//
//	ShowBossHpUI();
//	InitTime();
//	playerInit();
//	PlayerShowModel();
//	DrawGameBoard();
//	ScreenInit();
//	while (1) {
//		Render();
//		ProcessKeyInput();
//		UpdateTime();
//		UpdateBullet();
//		UpdateItem();
//		NormalMobUpdate();
//		UpdateBoss();
//		UpdateItem();
//		PlayerUpdate();
//		//PlayerStatOutput();
//		ManageShield();
//
//		if (IsGameOver()) {
//			SetCurrentCursorPos(25, 25);
//			printf("GAME OVER!!");
//			return 0;
//		}
//	}
//	getchar();
//
//	return 0;
//}