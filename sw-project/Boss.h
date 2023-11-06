#pragma once
#include "gameInfo.h"
#include <string>
#include <iostream>
#include <time.h>

#define BOSS_SIZE_Y 10
#define BOSS_SIZE_X 10

int bossModel[][BOSS_SIZE_Y][BOSS_SIZE_X] = {
	{
	/*첫번째 패턴 모델*/
/*
■■■■■■■■■■
■                ■
■                ■
■   ■      ■   ■
■ ■  ■  ■  ■ ■
■                ■
■                ■
■    ■■■■    ■
■                ■
■■■■■■■■■■
*/
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 1, 0, 0, 1},
	{1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 1, 1, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	},
	/*두번째 패턴 모델*/
/*


    ■■■■■■
    ■        ■
	■●    ●■
	■        ■
	■  ■■  ■
	■■■■■■


*/
	/*두번째 패턴 모델*/ // 1 : ■	2 : ●
	{
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 2, 0, 0, 2, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 0, 1, 1, 0, 1, 0, 0},
	{0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	},
	/*세번째 패턴 모델*/
	{
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 1, 0, 0, 1},
	{1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 1, 1, 1, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 1, 1, 1, 1, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	}
};

#define BOSS_ORIGIN_X 40
#define BOSS_ORIGIN_Y 2

COORD curBossPos = { BOSS_ORIGIN_X, BOSS_ORIGIN_Y };

int curBossPhase = 0;	// 0이 1번째 페이즈
int bossSpeed = 200;
std::string bossHpString = "coding/hagisilda/guichanda/aaaaaaaaaaaaaaaaa";
int curBossHp = bossHpString.length();
/****************보스 스탯 초기화 함수*********************/
void BossInit()
{
	curBossPhase = 0;
	curBossHp = bossHpString.length();
	curBossPos = { BOSS_ORIGIN_X, BOSS_ORIGIN_Y };
}
/****************보스 모델을 띄우는 함수*********************/
void ShowBossModel(int bossModel[][10])
{
	SetCurrentCursorPos(curBossPos.X, curBossPos.Y);
	int arrX = (curBossPos.X - GBOARD_ORIGIN_X) / 2;
	int arrY = curBossPos.Y - GBOARD_ORIGIN_Y;

	for (int y = 0; y < BOSS_SIZE_Y; y++)
	{
		for (int x = 0; x < BOSS_SIZE_X; x++)
		{
			SetCurrentCursorPos(curBossPos.X + (x * 2), curBossPos.Y + y);
			if (bossModel[y][x] == 1)
			{
				printf("■");
				gameBoardInfo[arrY + y][arrX + x] = BOSS;
			}
			else if (bossModel[y][x] == 2)
			{
				printf("●");
				gameBoardInfo[arrY + y][arrX + x] = BOSS;
			}
		}
	}
	SetCurrentCursorPos(curBossPos.X, curBossPos.Y);
}
/****************보스 모델을 삭제하는 함수*********************/
void DeleteBossModel(int bossModel[][10])
{
	SetCurrentCursorPos(curBossPos.X, curBossPos.Y);
	int arrX = (curBossPos.X - GBOARD_ORIGIN_X) / 2;
	int arrY = curBossPos.Y - GBOARD_ORIGIN_Y;

	for (int y = 0; y < BOSS_SIZE_Y; y++)
	{
		for (int x = 0; x < BOSS_SIZE_X; x++)
		{
			SetCurrentCursorPos(curBossPos.X + (x * 2), curBossPos.Y + y);
			if (bossModel[y][x] == 1)
			{
				printf("  ");
				gameBoardInfo[arrY + y][arrX + x] = 0;
			}
		}
	}

	SetCurrentCursorPos(curBossPos.X, curBossPos.Y);
}
/****************보스 HP UI를 띄우는 함수*********************/
void ShowBossHpUI()
{
	//보스의 원래 위치보다 한칸 위에 표시
	SetCurrentCursorPos(BOSS_ORIGIN_X - bossHpString.length() / 2 + BOSS_SIZE_X, BOSS_ORIGIN_Y - 1);
	for (int i = 0; i < curBossHp; i++)
		std::cout << bossHpString[i];
}
/****************보스 체력 한칸 줄이는 함수*********************/
void BossLifeDecrease()
{
	// 현재 체력 한칸 줄이고 다시 UI에 표시
	curBossHp--;
	ShowBossHpUI();
}
/****************보스를 왼쪽으로 이동하는 함수*********************/
void BossShiftLeft()
{
	DeleteBossModel(bossModel[curBossPhase]);
	curBossPos.X -= 2;
	ShowBossModel(bossModel[curBossPhase]);
}
/****************보스를 오른쪽으로 이동하는 함수*********************/
void BossShiftRight()
{
	DeleteBossModel(bossModel[curBossPhase]);
	curBossPos.X += 2;
	ShowBossModel(bossModel[curBossPhase]);
}
/****************보스의 전체적인 움직임*********************/
void BossRandomMove()
{
	srand(time(NULL));
	int direction = rand() % 2;	// 방향 정하기 0 : 오른쪽, 1 : 왼쪽
	int minDistance = 3;	// 최소 이동거리
	int range = 10;	// 이동 범위
	if (direction == 0)
	{
		int right = rand() % range + minDistance;
		for (int i = 0; i < right; i++)
		{
			BossShiftRight();
			Sleep(bossSpeed);
		}
		int left = rand() % range + minDistance;
		for (int i = 0; i < left; i++)
		{
			BossShiftLeft();
			Sleep(bossSpeed);
		}
	}
	else
	{
		int left = rand() % range + minDistance;
		for (int i = 0; i < left; i++)
		{
			BossShiftLeft();
			Sleep(bossSpeed);
		}
		int right = rand() % range + minDistance;
		for (int i = 0; i < right; i++)
		{
			BossShiftRight();
			Sleep(bossSpeed);
		}
	}
}
/****************보스 충돌 함수*********************/
int BossDetectedCollision(int posX, int posY)
{
	int arrX = (posX - GBOARD_ORIGIN_X) / 2;
	int arrY = posY - GBOARD_ORIGIN_Y;

	for (int y = 0; y < BOSS_SIZE_Y; y++)
	{
		for (int x = 0; x < BOSS_SIZE_X; x++)
		{
			if (bossModel[y][x] != 0 && gameBoardInfo[arrY + y][arrX + x] == int(bossHpString[curBossHp]))
				return 1;
		}
	}

	return 1;
}