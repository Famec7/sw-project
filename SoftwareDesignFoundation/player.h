#pragma once
#include "Cursor.h"
#include "gameInfo.h"
#include "Block.h"
#include <time.h>
#include <windows.h>
#include <stdio.h>

#define MAX_HP 14		//플레이어의 최대 채력		//player hp is full <= 14글자임
#define MAX_SHIELD	 6	//플레이어의 최대 실드 게이지 //shield <= 6글자임

int HP = MAX_HP;					//HP 초기화
float shield = MAX_SHIELD;		//실드 초기화
COORD playerCurPos;

int countTime1, countTime2;

typedef struct character {
	int ascii;
	int x;
	int y;
}charater;

int bulletNum = 3;			//초알의 개수

int isShield_Flag = 0;		//실드가 사용중인가 0 == 미사용, 1 == 사용중

int playerColor = 7;		//플레이어의 색 7 == gray, 9 == 파란색(실드), 4 == 빨간색(맞았을때)
int playerModel[5][5] = {		//충돌판정은 머리부분 3*3만
	{0, 2, 2, 2, 0},
	{0, 2, 2, 2, 0},
	{2, 2, 2, 2, 2},
	{0, 2, 2, 2, 0},
	{0, 2, 0, 2, 0}
};
//화면에 Player 상태 출력
char hpText[] = { 'P', 'l', 'a', 'y', 'e', 'r',
				'h', 'p',
				'i', 's',
				'f', 'u', 'l', 'l' };
char shieldText[] = { 's', 'h', 'i', 'e', 'l', 'd' };
void playerInit();
void PlayerShowModel();
void PlayerDeleteModel();
int PlayerDetectedCollision(int x, int y);
int PlayerShiftLeft();
int PlayerShiftRight();
int PlayerShiftUp();
int PlayerShiftDown();
void PlayerStatOutput();
void Attack(int input);
void ProcessKeyInput();
void UseShield();
void ManageShield();
void ManageGameboard();