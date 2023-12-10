#include "Menu.h"
#include <stdio.h>
#include "Cursor.h"
#include "gameInfo.h"
#include "Bullet.h"
#include "Player.h"
#include "Render.h"
#include "Init.h"
#include "GameManager.h"

// text model
extern char strG[5][8] = {
	{0, 1, 1, 1, 1, 1, 1, 0},
	{1, 1, 0, 0, 0, 0, 0, 0},
	{1, 1, 0, 0, 0, 1, 1, 1},
	{1, 1, 0, 0, 0, 0, 1, 1},
	{0, 1, 1, 1, 1, 1, 1, 0}
};
extern char strA[5][7] = {
	{0, 1, 1, 1, 1, 1, 0},
	{1, 1, 0, 0, 0, 1, 1},
	{1, 1, 1, 1, 1, 1, 1},
	{1, 1, 0, 0, 0, 1, 1},
	{1, 1, 0, 0, 0, 1, 1}
};

extern char strM[5][10] = {
	{1, 1, 1, 0, 0, 0, 0, 1, 1, 1},
	{1, 1, 1, 1, 0, 0, 1 ,1 ,1 ,1},
	{1, 1, 0, 1, 1, 1, 1, 0, 1, 1},
	{1, 1, 0, 0, 1, 1, 0, 0, 1, 1},
	{1, 1, 0, 0, 0, 0, 0, 0, 1, 1}
};

extern char strE[5][7] = {
	{1, 1, 1, 1, 1, 1, 1},
	{1, 1, 0, 0, 0, 0, 0},
	{1, 1, 1, 1, 1, 0, 0},
	{1, 1, 0, 0, 0, 0, 0},
	{1, 1, 1, 1, 1, 1, 1}
};

extern char strS[5][7] = {
	{1, 1, 1, 1, 1, 1, 1},
	{1, 1, 0, 0, 0, 0, 0},
	{1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 1, 1},
	{1, 1, 1, 1, 1, 1, 1}
};

extern char strT[5][8] = {
	{1, 1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 1, 1, 0, 0, 0},
	{0, 0, 0, 1, 1, 0, 0, 0},
	{0, 0, 0, 1, 1, 0, 0, 0},
	{0, 0, 0, 1, 1, 0, 0, 0}
};

extern char strR[5][7] = {
	{1, 1, 1, 1, 1, 1, 0},
	{1, 1, 0, 0, 0, 1, 1},
	{1, 1, 1, 1, 1, 1, 0},
	{1, 1, 0, 0, 0, 1, 1},
	{1, 1, 0, 0, 0, 1, 1}
};

//set variable
COORD textPos[9];
char textHpStr[10] = "gamestart";
double textTime = 0;
int textHp = MAX_TEXT_HP;

//set function
int UpdateText() {
	int x;
	BlinkText();
	if (TextDetectedCollision()) {
		textHp--;
		for (x = 1; x < GBOARD_WIDTH + 2; x++) {
			DeleteBullet(x, 20);
		}
	}
	if (textHp == 0) {
		PrintText();
		Sleep(1000);
		system("cls");
		DeleteTextGboard();
		DeleteMoveBox();
		return 0;
	}
	return 1;
}

void InitText() {
	InitTextGBoard();
	InitTextPos();
	textHp = MAX_TEXT_HP;
}

void InitTextGBoard() {
	int i;
	for (i = 1; i < GBOARD_WIDTH + 1; i++) {
		gameBoardInfo[19][i] = 1;
	}
}

void DeleteTextGboard() {
	int i;
	for (i = 1; i < GBOARD_WIDTH + 1; i++) {
		gameBoardInfo[19][i] = 0;
	}
}

void InitTextPos() {
	SetMoveBox();
	COORD gameTextPos, startTextPos;
	gameTextPos.X = 15;
	gameTextPos.Y = 10;
	startTextPos.X = 12;
	startTextPos.Y = 18;

	textPos[0].X = gameTextPos.X;
	textPos[0].Y = gameTextPos.Y;
	textPos[1].X = gameTextPos.X + 17;
	textPos[1].Y = gameTextPos.Y;
	textPos[2].X = gameTextPos.X + 32;
	textPos[2].Y = gameTextPos.Y;
	textPos[3].X = gameTextPos.X + 53;
	textPos[3].Y = gameTextPos.Y;

	textPos[4].X = startTextPos.X;
	textPos[4].Y = startTextPos.Y;
	textPos[5].X = startTextPos.X + 15;
	textPos[5].Y = startTextPos.Y;
	textPos[6].X = startTextPos.X + 32;
	textPos[6].Y = startTextPos.Y;
	textPos[7].X = startTextPos.X + 47;
	textPos[7].Y = startTextPos.Y;
	textPos[8].X = startTextPos.X + 62;
	textPos[8].Y = startTextPos.Y;
}

int TextDetectedCollision() {
	int x, y;
	for (x = 1; x < GBOARD_WIDTH+2; x++) {
		if (gameBoardInfo[20][x] != 0) {
			if (gameBoardInfo[20][x] == textHpStr[MAX_TEXT_HP - textHp])
				return 1;
		}
	}
	return 0;
}

void PrintText() {
	if (textHp > 8)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x08);
	else 
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
	PrintG(textPos[0]);
	if (textHp > 7)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x08);
	else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
	PrintA(textPos[1]);
	if (textHp > 6)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x08);
	else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
	PrintM(textPos[2]);
	if (textHp > 5)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x08);
	else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
	PrintE(textPos[3]);
	if (textHp > 4)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x08);
	else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
	PrintS(textPos[4]);
	if (textHp > 3)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x08);
	else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
	PrintT(textPos[5]);
	if (textHp > 2)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x08);
	else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
	PrintA(textPos[6]);
	if (textHp > 1)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x08);
	else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
	PrintR(textPos[7]);
	if (textHp > 0)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x08);
	else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
	PrintT(textPos[8]);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
}

void DeleteText() {
	if (textHp > 8) DeleteG(textPos[0]);
	if (textHp > 7) DeleteA(textPos[1]);
	if (textHp > 6) DeleteM(textPos[2]);
	if (textHp > 5) DeleteE(textPos[3]);
	if (textHp > 4) DeleteS(textPos[4]);
	if (textHp > 3) DeleteT(textPos[5]);
	if (textHp > 2) DeleteA(textPos[6]);
	if (textHp > 1) DeleteR(textPos[7]);
	if (textHp > 0) DeleteT(textPos[8]);
}

void BlinkText() {
	if(textTime<0.3)PrintText();
	else {
		DeleteText();
	}
	textTime += Time.deltaTime;
	if (textTime > 0.6) textTime = 0;
}

void PrintG(COORD pos) {
	int i, j;
	SetCurrentCursorPos(pos.X, pos.Y);
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 8; j++) {
			if (strG[i][j] == 1) printf("■");
			else printf("  ");
		}
		SetCurrentCursorPos(pos.X, pos.Y+i+1);
	}
}

void DeleteG(COORD pos) {
	int i, j;
	SetCurrentCursorPos(pos.X, pos.Y);
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 8; j++) {
			printf("  ");
		}
		SetCurrentCursorPos(pos.X, pos.Y + i + 1);
	}
}

void PrintA(COORD pos) {
	int i, j;
	SetCurrentCursorPos(pos.X, pos.Y);
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 7; j++) {
			if (strA[i][j] == 1) printf("■");
			else printf("  ");
		}
		SetCurrentCursorPos(pos.X, pos.Y + i + 1);
	}
}

void DeleteA(COORD pos) {
	int i, j;
	SetCurrentCursorPos(pos.X, pos.Y);
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 7; j++) {
			printf("  ");
		}
		SetCurrentCursorPos(pos.X, pos.Y + i + 1);
	}
}

void PrintM(COORD pos) {
	int i, j;
	SetCurrentCursorPos(pos.X, pos.Y);
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 10; j++) {
			if (strM[i][j] == 1) printf("■");
			else printf("  ");
		}
		SetCurrentCursorPos(pos.X, pos.Y + i + 1);
	}
}

void DeleteM(COORD pos) {
	int i, j;
	SetCurrentCursorPos(pos.X, pos.Y);
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 10; j++) {
			printf("  ");
		}
		SetCurrentCursorPos(pos.X, pos.Y + i + 1);
	}
}

void PrintE(COORD pos) {
	int i, j;
	SetCurrentCursorPos(pos.X, pos.Y);
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 7; j++) {
			if (strE[i][j] == 1) printf("■");
			else printf("  ");
		}
		SetCurrentCursorPos(pos.X, pos.Y + i + 1);
	}
}

void DeleteE(COORD pos) {
	int i, j;
	SetCurrentCursorPos(pos.X, pos.Y);
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 7; j++) {
			printf("  ");
		}
		SetCurrentCursorPos(pos.X, pos.Y + i + 1);
	}
}

void PrintS(COORD pos) {
	int i, j;
	SetCurrentCursorPos(pos.X, pos.Y);
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 7; j++) {
			if (strS[i][j] == 1) printf("■");
			else printf("  ");
		}
		SetCurrentCursorPos(pos.X, pos.Y + i + 1);
	}
}

void DeleteS(COORD pos) {
	int i, j;
	SetCurrentCursorPos(pos.X, pos.Y);
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 7; j++) {
			printf("  ");
		}
		SetCurrentCursorPos(pos.X, pos.Y + i + 1);
	}
}

void PrintT(COORD pos) {
	int i, j;
	SetCurrentCursorPos(pos.X, pos.Y);
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 8; j++) {
			if (strT[i][j] == 1) printf("■");
			else printf("  ");
		}
		SetCurrentCursorPos(pos.X, pos.Y + i + 1);
	}
}

void DeleteT(COORD pos) {
	int i, j;
	SetCurrentCursorPos(pos.X, pos.Y);
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			printf("  ");
		}
		SetCurrentCursorPos(pos.X, pos.Y + i + 1);
	}
}

void PrintR(COORD pos) {
	int i, j;
	SetCurrentCursorPos(pos.X, pos.Y);
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 7; j++) {
			if (strR[i][j] == 1) printf("■");
			else printf("  ");
		}
		SetCurrentCursorPos(pos.X, pos.Y + i + 1);
	}
}

void DeleteR(COORD pos) {
	int i, j;
	SetCurrentCursorPos(pos.X, pos.Y);
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 7; j++) {
			printf("  ");
		}
		SetCurrentCursorPos(pos.X, pos.Y + i + 1);
	}
}

void SetMoveBox() {
	for (int y = 0; y <= GBOARD_HEIGHT; y++)
	{
		if (y == GBOARD_HEIGHT)
		{
			gameBoardInfo[GBOARD_HEIGHT][0] = MAP_BOUNDARY;
		}
		else if (y == 0) {
			gameBoardInfo[0][0] = MAP_BOUNDARY;
		}
		else
		{
			gameBoardInfo[y][0] = MAP_BOUNDARY;
		}
	}
	for (int y = 0; y <= GBOARD_HEIGHT; y++)
	{
		if (y == GBOARD_HEIGHT)
		{
			gameBoardInfo[GBOARD_HEIGHT][GBOARD_WIDTH + 1] = MAP_BOUNDARY;
		}
		else if (y == 0) {
			gameBoardInfo[0][GBOARD_WIDTH + 1] = MAP_BOUNDARY;
		}
		else
		{
			gameBoardInfo[y][GBOARD_WIDTH + 1] = MAP_BOUNDARY;
		}
	}
	for (int x = 1; x <= GBOARD_WIDTH + 1; x++)
	{
		gameBoardInfo[GBOARD_HEIGHT][x] = MAP_BOUNDARY;
	}
	for (int x = 1; x <= GBOARD_WIDTH + 1; x++)
	{
		gameBoardInfo[0][x] = MAP_BOUNDARY;
	}
}

void DeleteMoveBox() {
	for (int y = 0; y <= GBOARD_HEIGHT; y++)
	{
		if (y == GBOARD_HEIGHT)
		{
			gameBoardInfo[GBOARD_HEIGHT][0] = 0;
		}
		else if (y == 0) {
			gameBoardInfo[0][0] = 0;
		}
		else
		{
			gameBoardInfo[y][0] = 0;
		}
	}
	for (int y = 0; y <= GBOARD_HEIGHT; y++)
	{
		if (y == GBOARD_HEIGHT)
		{
			gameBoardInfo[GBOARD_HEIGHT][GBOARD_WIDTH + 1] = 0;
		}
		else if (y == 0) {
			gameBoardInfo[0][GBOARD_WIDTH + 1] = 0;
		}
		else
		{
			gameBoardInfo[y][GBOARD_WIDTH + 1] = 0;
		}
	}
	for (int x = 1; x <= GBOARD_WIDTH + 1; x++)
	{
		gameBoardInfo[GBOARD_HEIGHT][x] = 0;
	}
	for (int x = 1; x <= GBOARD_WIDTH + 1; x++)
	{
		gameBoardInfo[0][x] = 0;
	}
}

void UpdateMenu()
{
	Render();
	ProcessKeyInput();
	UpdateTime();
	UpdateBullet();
	PlayerUpdate();
	int isStartPage = UpdateText();
	if (isStartPage == 0)
	{
		Init();
		SceneChange(Game);
	}
	if (isStartPage == -1) {
		SceneChange(Exit);
		return;
	}
}

void InitMenu()
{
	InitTime();
	playerInit();
	PlayerShowModel();
	ScreenInit();
	InitText();
}