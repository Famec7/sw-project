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
		// ���� ���� �޴�
	}
	else if (IsBossCleared()) {
		Gamestate = GameClear;
		Init();
		// ���� Ŭ���� �޴�
	}

	if (Gamestate == Menu)
	{
		Gamestate = Game;
		// UpdateMenu();
	}
}