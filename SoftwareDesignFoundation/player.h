#pragma once
#include "Cursor.h"
#include <time.h>
#include <windows.h>
#define MAX_HP 14		//플레이어의 최대 채력		//player hp is full <= 14글자임
#define MAX_SHIELD	 6	//플레이어의 최대 실드 게이지 //shield <= 6글자임

int HP = MAX_HP;					//HP 초기화
float shield = MAX_SHIELD;		//실드 초기화
int curPosX = 10;
int curPosY = 10;
COORD playerCurPos;

void playerInit() {
	playerCurPos.X = 20;
	playerCurPos.Y = 20;
}

int bulletNum = 1;			//초알의 개수

int isShield_Flag = 0;		//실드가 사용중인가 0 == 미사용, 1 == 사용중

int playerColor = 7;		//플레이어의 색 7 == gray, 9 == 파란색(실드), 4 == 빨간색(맞았을때)
int playerModel[5][5] = {		//충돌판정은 머리부분 3*3만
	{0, 2, 2, 2, 0},
	{0, 2, 2, 2, 0},
	{2, 2, 2, 2, 2},
	{0, 2, 2, 2, 0},
	{0, 2, 0, 2, 0}
};

void PlayerShowModel() {
	SetCurrentCursorPos(playerCurPos.X, playerCurPos.Y);
	COORD curPos = GetCurrentCursorPos();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), playerColor);	//gray
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			SetCurrentCursorPos(curPos.X + (x * 2), curPos.Y + y);
			if (playerModel[y][x] == 2)printf("■");
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	//커서 색 초기화
}
void PlayerDeleteModel() {
	SetCurrentCursorPos(playerCurPos.X, playerCurPos.Y);
	COORD curPos = GetCurrentCursorPos();
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			SetCurrentCursorPos(curPos.X + (x * 2), curPos.Y + y);
			if (playerModel[y][x] == 2)printf("  ");
		}
	}
}
int PlayerDetectedCollision(int x, int y) {
	//충돌판정 구현 예정 ㅠㅠ
	int arrX = (x - GBOARD_ORIGIN_X) / 2;
	int arrY = y - GBOARD_ORIGIN_Y;
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			if (playerModel[y][x] != 0 && gameBoardInfo[arrY + y][arrX + x]
				== 4) {
				HP--;
				return 1;	//총알 충돌
			}
			else if (playerModel[y][x] != 0 && gameBoardInfo[arrY + y][arrX + x]
				== 1)return 0;	//벽 충돌
		}
	}
	return 1;
}
int PlayerShiftLeft() {
	if (!PlayerDetectedCollision(playerCurPos.X - 2, playerCurPos.Y))return 0;
	PlayerDeleteModel();
	playerCurPos.X -= 2;
	SetCurrentCursorPos(playerCurPos.X, playerCurPos.Y);
	PlayerShowModel();
	return 1;
}
int PlayerShiftRight() {
	if (!PlayerDetectedCollision(playerCurPos.X + 2, playerCurPos.Y))return 0;
	PlayerDeleteModel();
	playerCurPos.X += 2;
	SetCurrentCursorPos(playerCurPos.X, playerCurPos.Y);
	PlayerShowModel();
	return 1;
}
int PlayerShiftUp() {
	if (!PlayerDetectedCollision(playerCurPos.X, playerCurPos.Y - 1))return 0;
	PlayerDeleteModel();
	playerCurPos.Y -= 1;
	SetCurrentCursorPos(playerCurPos.X, playerCurPos.Y);
	PlayerShowModel();
	return 1;
}
int PlayerShiftDown() {
	if (!PlayerDetectedCollision(playerCurPos.X, playerCurPos.Y + 1))return 0;
	PlayerDeleteModel();
	playerCurPos.Y += 1;
	SetCurrentCursorPos(playerCurPos.X, playerCurPos.Y);
	PlayerShowModel();
	return 1;
}
//화면에 Player 상태 출력
char hpText[] = { 'P', 'l', 'a', 'y', 'e', 'r',
				'h', 'p',
				'i', 's',
				'f', 'u', 'l', 'l' };
char shieldText[] = { 's', 'h', 'i', 'e', 'l', 'd' };
void PlayerStatOutput() {
	SetCurrentCursorPos(10, 10);
	printf("                 ");
	SetCurrentCursorPos(10, 10);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	for (int i = 0; i < 14; i++) {
		if (i == HP)break;	//HP가 2이면 pl만 출력, i가 2이면 a를 출력하게되, 이를 못하게 막음
		if (i == 6 || i == 8 || i == 10) printf(" ");
		printf("%c", hpText[i]);
	}
	SetCurrentCursorPos(10, 16);
	printf("                 ");
	SetCurrentCursorPos(10, 16);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	for (int i = 0; i < 6; i++) {
		if (i == (int)shield)break;
		printf("%c", shieldText[i]);
	}
}
void ProcessKeyInput() {	//GetAsyncKeyState
	int key;
	if (_kbhit() != 0) {
		key = _getch();
		switch (key) {
		case 75:
			PlayerShiftLeft();
			break;
		case 77:
			PlayerShiftRight();
			break;
		case 72:
			PlayerShiftUp();
			break;
		case 80:
			PlayerShiftDown();
			break;
		case 13:		//enter
			//UseShield();
			break;
		default:
			//Attack(key);
			break;
		}
	}
}
void UseShield() {
	if (shield >= 6.0f) {
		isShield_Flag = 1;		//실드 사용중
		playerColor = 9;		//플레이어의 색은 파란색
	}
}
void ManageShield() {
	if (isShield_Flag == 1) {
		//시간을 제면서 실드지속시간을 계산함
		//실드 지속시간이 0에 수렴하게 되면 isShield_Flag = 0
	}
	else {
		//isShield_Flag == 0이면 시간에 제면서 실드를 재충전함
		//실드 충전량이 6초내지 5초를 넘지않도록함

	}
}
void Attack(int input) {
	COORD pos = GetCurrentCursorPos();

}

