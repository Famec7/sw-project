﻿#include "player.h"
#include "Bullet.h"

double imHit = 0;
int CantControl = 0;

int HP = MAX_HP;					//HP 초기화
double shield = MAX_SHIELD;		//실드 초기화
//double playerSpeed = 0.5;

COORD playerCurPos;
int countTime1, countTime2;
int bulletNum = 1;			//초알의 개수
int isShield_Flag = 0; 
int playerColor = 7;

int playerModel[PLAYER_HEIGHT][PLAYER_WIDTH] = {{2}, {2}};

char hpText[] = { 'P', 'l', 'a', 'y', 'e', 'r', 'h',
				 'p', 'i', 's', 'f', 'u', 'l', 'l' };
char shieldText[] = { 's', 'h', 'i', 'e', 'l', 'd' };

void playerInit() {
	playerCurPos.X = 45;
	playerCurPos.Y = 35;
}
void PlayerShowModel() {
	SetCurrentCursorPos(playerCurPos.X, playerCurPos.Y);
	COORD curPos = GetCurrentCursorPos();
	if (imHit != 0 && isShield_Flag == 0)playerColor = 4;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), playerColor);	//gray
	int x, y;
	int arrCurX = (curPos.X - GBOARD_ORIGIN_X) / 2;
	int arrCurY = (curPos.Y - GBOARD_ORIGIN_Y);
	for (y = 0; y < PLAYER_HEIGHT; y++) {
		for (x = 0; x < PLAYER_WIDTH; x++) {
			if (playerModel[y][x] == 2) {
				SetCurrentCursorPos(curPos.X + (x * 2), curPos.Y + y);
				if (y == 0) {
					printf("●");
				}
				else if (y == 1) {
					printf("▲");
				}
				gameBoardInfo[arrCurY + y][arrCurX + x] = 2;
			}
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void PlayerDeleteModel() {
	SetCurrentCursorPos(playerCurPos.X, playerCurPos.Y);
	COORD curPos = GetCurrentCursorPos();
	int x, y;
	int arrCurX = (curPos.X - GBOARD_ORIGIN_X) / 2;
	int arrCurY = (curPos.Y - GBOARD_ORIGIN_Y);
	for (y = 0; y < PLAYER_HEIGHT; y++) {
		for (x = 0; x < PLAYER_WIDTH; x++) {
			SetCurrentCursorPos(curPos.X + (x * 2), curPos.Y + y);
			if (playerModel[y][x] == 2) {
				printf("  ");
				gameBoardInfo[arrCurY + y][arrCurX + x] = 0;
			}
		}
	}
}
int PlayerDetectedCollision(int x, int y) {
	int arrX = (x - GBOARD_ORIGIN_X) / 2;
	int arrY = y - GBOARD_ORIGIN_Y;
	for (int y = 0; y < PLAYER_HEIGHT; y++) {
		for (int x = 0; x < PLAYER_WIDTH; x++) {
			if (isShield_Flag == 0) {
				if (playerModel[y][x] != 0 && gameBoardInfo[arrY + y][arrX + x] == 4) {
					HP--;
					imHit = 1;
					PlayerDeleteModel();
					PlayerShowModel();
					return 1;	//총알 충돌
				}
			}
			if (playerModel[y][x] != 0 && gameBoardInfo[arrY + y][arrX + x] == 1)return 0;	//벽 충돌
			else if (playerModel[y][x] != 0 && gameBoardInfo[arrY + y][arrX + x] == 3)return 0;	//적 충돌
			else if (playerModel[y][x] != 0 && gameBoardInfo[arrY + y][arrX + x] == 5)return 0;	//아이템 충돌
			else if (playerModel[y][x] != 0 && gameBoardInfo[arrY + y][arrX + x] == 6)return 0;	//아이템 충돌
			else if (playerModel[y][x] != 0 && gameBoardInfo[arrY + y][arrX + x] == 7)return 0;	//보스 충돌
		}
	}
	return 1;
}
int PlayerShiftLeft() {
	if (!PlayerDetectedCollision(playerCurPos.X - 2, playerCurPos.Y))
		return 0;
	PlayerDeleteModel();
	playerCurPos.X -= 2;
	SetCurrentCursorPos(playerCurPos.X, playerCurPos.Y);
	PlayerShowModel();
	return 1;
}
int PlayerShiftRight() {
	if (!PlayerDetectedCollision(playerCurPos.X + 2, playerCurPos.Y))
		return 0;
	PlayerDeleteModel();
	playerCurPos.X += 2;
	SetCurrentCursorPos(playerCurPos.X, playerCurPos.Y);
	PlayerShowModel();
	return 1;
}
int PlayerShiftUp() {
	if (!PlayerDetectedCollision(playerCurPos.X, playerCurPos.Y - 1))
		return 0;
	PlayerDeleteModel();
	playerCurPos.Y -= 1;
	SetCurrentCursorPos(playerCurPos.X, playerCurPos.Y);
	PlayerShowModel();
	return 1;
}
int PlayerShiftDown() {
	if (!PlayerDetectedCollision(playerCurPos.X, playerCurPos.Y + 1))
		return 0;
	PlayerDeleteModel();
	playerCurPos.Y += 1;
	SetCurrentCursorPos(playerCurPos.X, playerCurPos.Y);
	PlayerShowModel();
	return 1;
}
void PlayerStatOutput() {
	SetCurrentCursorPos(10, 45);
	printf("                 ");
	SetCurrentCursorPos(10, 45);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	for (int i = 0; i < 14; i++) {
		if (i == HP)
			break;
		if (i == 6 || i == 8 || i == 10)
			printf(" ");
		printf("%c", hpText[i]);
	}
	SetCurrentCursorPos(10, 46);
	printf("                 ");
	SetCurrentCursorPos(10, 46);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	for (int i = 0; i < 6; i++) {
		if (i == (int)shield)
			break;
		printf("%c", shieldText[i]);
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void ProcessKeyInput() { // GetAsyncKeyState
	//if (playerSpeed > 0)return;
	if (CantControl == 1)return;
	if (_kbhit() == 0)
		return;
	if (GetAsyncKeyState(VK_LEFT)) {
		PlayerShiftLeft();
	}
	if (GetAsyncKeyState(VK_RIGHT)) {
		PlayerShiftRight();
	}
	if (GetAsyncKeyState(VK_DOWN)) {
		PlayerShiftDown();
	}
	if (GetAsyncKeyState(VK_UP)) {
		PlayerShiftUp();
	}
	if (GetAsyncKeyState(VK_RETURN))
		UseShield();

	for (int i = 0; i <= 'z' - 'a'; i++) {
		if (GetAsyncKeyState(0x41 + i)) {
			if (bulletNum == 1) {
				MakeBullet(playerCurPos.X, playerCurPos.Y - 2, 'a' + i, 0.01f);
			}
			else if (bulletNum == 2) {
				MakeBullet(playerCurPos.X + 1, playerCurPos.Y - 2, 'a' + i, 0.01f);
				MakeBullet(playerCurPos.X - 1, playerCurPos.Y - 2, 'a' + i, 0.01f);
			}
			else if (bulletNum == 3) {
				MakeBullet(playerCurPos.X + 2, playerCurPos.Y - 2, 'a' + i, 0.01f);
				MakeBullet(playerCurPos.X, playerCurPos.Y - 2, 'a' + i, 0.01f);
				MakeBullet(playerCurPos.X - 2, playerCurPos.Y - 2, 'a' + i, 0.01f);
			}
			else if (bulletNum == 4) {
				MakeBullet(playerCurPos.X + 3, playerCurPos.Y - 2, 'a' + i, 0.01f);
				MakeBullet(playerCurPos.X + 1, playerCurPos.Y - 2, 'a' + i, 0.01f);
				MakeBullet(playerCurPos.X - 1, playerCurPos.Y - 2, 'a' + i, 0.01f);
				MakeBullet(playerCurPos.X - 3, playerCurPos.Y - 2, 'a' + i, 0.01f);
			}
			else if (bulletNum == 5) {
				MakeBullet(playerCurPos.X + 4, playerCurPos.Y - 2, 'a' + i, 0.01f);
				MakeBullet(playerCurPos.X + 2, playerCurPos.Y - 2, 'a' + i, 0.01f);
				MakeBullet(playerCurPos.X, playerCurPos.Y - 2, 'a' + i, 0.01f);
				MakeBullet(playerCurPos.X - 2, playerCurPos.Y - 2, 'a' + i, 0.01f);
				MakeBullet(playerCurPos.X - 4, playerCurPos.Y - 2, 'a' + i, 0.01f);
			}
		}
	}
	//playerSpeed += 0.5;
	Sleep(50);
}
void UseShield() {
	if (shield >= 6.0f) {
		isShield_Flag = 1;		//실드 사용중
		playerColor = 9;		//플레이어의 색은 파란색
		PlayerDeleteModel();
		PlayerShowModel();
	}
}
void ManageShield() {
	if (isShield_Flag == 1) {
		shield -= Time.deltaTime;
		if (shield <= 0) {
			isShield_Flag = 0;
			shield = 0;
			playerColor = 7;
		}
	}
	else {
		if (shield >= MAX_SHIELD)
			return;
		shield += Time.deltaTime;
		if (shield >= MAX_SHIELD)
			shield = MAX_SHIELD;
	}
}
void PlayerUpdate() {
	PlayerDetectedCollision(playerCurPos.X, playerCurPos.Y - 1);
	PlayerDeleteModel();
	PlayerShowModel();
	if (imHit <= 0) {
		imHit = 0;
		if (isShield_Flag == 0) {
			playerColor = 7;
		}
		if (isShield_Flag == 1) {
			playerColor = 9;
		}
	}
	else {
		imHit -= Time.deltaTime;
	}
}
int IsGameOver() {
	if (HP <= 0)
		return 1;
	else
		return 0;
}
