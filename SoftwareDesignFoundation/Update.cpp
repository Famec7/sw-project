#include "Init.h"
#include "Update.h"
#include <stdlib.h>

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
		/*SetCurrentCursorPos(25, 25);
		printf("GAME OVER!!");*/
		Gamestate = GameOver;
		dead_page();
		Init();
		// ���� ���� �޴�
	}
	else if (IsBossCleared()) {
		Gamestate = GameClear;
		Init();
		InitBoard();
		// ���� Ŭ���� �޴�
	}

	if (Gamestate == Menu)
	{
		Gamestate = Game;
		// UpdateMenu();
	}
}

void dead_page() {
	int x = 25, y = 20;
	system("cls");
	_getch();
	do {
		y = 20;
		SetCurrentCursorPos(x, y++); printf("                                                __               __");
		SetCurrentCursorPos(x, y++); printf("   __  ______  __  __   ____ _________     ____/ /__  ____ _____/ /");
		SetCurrentCursorPos(x, y++); printf("  / / / / __ \\/ / / /  / __ `/ ___/ _ \\   / __  / _ \\/ __ `/ __  / ");
		SetCurrentCursorPos(x, y++); printf(" / /_/ / /_/ / /_/ /  / /_/ / /  /  __/  / /_/ /  __/ /_/ / /_/ /  ");
		SetCurrentCursorPos(x, y++); printf(" \\__, /\\____/\\__,_/   \\__,_/_/   \\___/   \\__,_/\\___/\\__,_/\\__,_/   ");
		SetCurrentCursorPos(x, y++); printf("/____/                                                             ");
		SetCurrentCursorPos(x, y);   printf("                          PREES Enter KEY");
		Sleep(250);
		y = 20;
		SetCurrentCursorPos(x, y++); printf("                                                                   ");
		SetCurrentCursorPos(x, y++); printf("                                                                   ");
		SetCurrentCursorPos(x, y++); printf("                                                                   ");
		SetCurrentCursorPos(x, y++); printf("                                                                   ");
		SetCurrentCursorPos(x, y++); printf("                                                                   ");
		SetCurrentCursorPos(x, y++); printf("                                                                   ");
		SetCurrentCursorPos(x, y);   printf("                                                                   ");
		Sleep(250);
	} while (!GetAsyncKeyState(VK_RETURN));

	Gamestate = Game;
	system("cls");
}