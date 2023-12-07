#include "Init.h"
#include "Update.h"

void Update() {
	if (Gamestate == Game) {
		UpdateTime();
		UpdateBullet();
		UpdateItem();
		NormalMobUpdate();
		UpdateBoss();
		UpdateItem();
		ProcessKeyInput();
		PlayerUpdate();
		ManageShield();
	}

	if (IsGameOver()) {
		SetCurrentCursorPos(25, 25);
		printf("GAME OVER!!");
		Gamestate = GameOver;
		Init();
		// 게임 오버 메뉴
	}
	else if (IsBossCleared()) {
		Gamestate = GameClear;
		Init();
		// 게임 클리어 메뉴
	}

	if (Gamestate == Menu)
	{
		Gamestate = Game;
		// UpdateMenu();
	}
}