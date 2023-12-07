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

void dead_page() {
	int x = 25, y = 20;
	system("cls");
	_getch();
	while (1) {
		y = 20;
		SetCurrentCursorPos(x, y++); printf("                                                __               __");
		SetCurrentCursorPos(x, y++); printf("   __  ______  __  __   ____ _________     ____/ /__  ____ _____/ /");
		SetCurrentCursorPos(x, y++); printf("  / / / / __ \\/ / / /  / __ `/ ___/ _ \\   / __  / _ \\/ __ `/ __  / ");
		SetCurrentCursorPos(x, y++); printf(" / /_/ / /_/ / /_/ /  / /_/ / /  /  __/  / /_/ /  __/ /_/ / /_/ /  ");
		SetCurrentCursorPos(x, y++); printf(" \\__, /\\____/\\__,_/   \\__,_/_/   \\___/   \\__,_/\\___/\\__,_/\\__,_/   ");
		SetCurrentCursorPos(x, y++); printf("/____/                                                             ");
		SetCurrentCursorPos(x, y);   printf("                          PREES ANY KEY");
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
		if (_kbhit()) {
			Gamestate = Game;
			break;
		}
	}
	system("cls");
}