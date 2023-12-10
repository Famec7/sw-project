#include "Init.h"
#include "Update.h"
#include "Menu.h"
#include <stdlib.h>

void Update() {
	if (Gamestate == Game) {
		DrawGameBoard();
		UpdateTime();
		UpdateBullet();
		UpdateItem();
		NormalMobUpdate();
		UpdateBoss();
		UpdateItem();
		ProcessKeyInput();
		PlayerUpdate();
		ManageShield();

		if(IsBossCleared())
			SceneChange(GameClear);
		if(IsGameOver())
			SceneChange(GameOver);
	}

	if (Gamestate == GameOver) {
		dead_page();
		// 게임 오버 메뉴
	}
	if (Gamestate == GameClear) {
		clear_page();
		// 게임 클리어 메뉴
	}

	if (Gamestate == Menu)
	{
		UpdateMenu();
	}
}

void dead_page() {
	int x = 18, y = 20;
	system("cls");
	PlaySound(TEXT("./Sound/game_over.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	_getch();
	do {
		y = 20;
		SetCurrentCursorPos(x, y++); printf("                                                __               __");
		SetCurrentCursorPos(x, y++); printf("   __  ______  __  __   ____ _________     ____/ /__  ____ _____/ /");
		SetCurrentCursorPos(x, y++); printf("  / / / / __ \\/ / / /  / __ `/ ___/ _ \\   / __  / _ \\/ __ `/ __  / ");
		SetCurrentCursorPos(x, y++); printf(" / /_/ / /_/ / /_/ /  / /_/ / /  /  __/  / /_/ /  __/ /_/ / /_/ /  ");
		SetCurrentCursorPos(x, y++); printf(" \\__, /\\____/\\__,_/   \\__,_/_/   \\___/   \\__,_/\\___/\\__,_/\\__,_/   ");
		SetCurrentCursorPos(x, y++); printf("/____/                                                             ");
		SetCurrentCursorPos(x, y);   printf("                          PREES ENTER KEY");
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

	system("cls");
	SceneChange(Menu);
}

void clear_page() {
	int x = 34, y = 20;
	PlaySound(TEXT("./Sound/clear.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	system("cls");
	while (!GetAsyncKeyState(VK_RETURN)) {
		y = 20;
		SetCurrentCursorPos(x, y++); printf("   ________    _________    ____ ");
		SetCurrentCursorPos(x, y++); printf("  / ____/ /   / ____/   |  / __ \\");
		SetCurrentCursorPos(x, y++); printf(" / /   / /   / __/ / /| | / /_/ /");
		SetCurrentCursorPos(x, y++); printf("/ /___/ /___/ /___/ ___ |/ _, _/ ");
		SetCurrentCursorPos(x, y++); printf("\\____/_____/_____/_/  |_/_/ |_|  ");
		SetCurrentCursorPos(x, y++); printf("         PRESS ENTER KEY");
		Sleep(250);

		y = 20;
		SetCurrentCursorPos(x, y++); printf("                                  ");
		SetCurrentCursorPos(x, y++); printf("                                  ");
		SetCurrentCursorPos(x, y++); printf("                                  ");
		SetCurrentCursorPos(x, y++); printf("                                  ");
		SetCurrentCursorPos(x, y++); printf("                                  ");
		SetCurrentCursorPos(x, y++); printf("                                  ");
		SetCurrentCursorPos(x, y++); printf("                                  ");
		Sleep(250);
	}
	_getch();
	system("cls");
	SceneChange(Menu);
}