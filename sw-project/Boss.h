#pragma once
#include <string>
#include <iostream>

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
■    ■■■■    ■
■    ■    ■    ■
■    ■■■■    ■
■■■■■■■■■■
*/
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
	},
	/*두번째 패턴 모델*/
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

int curBossPhase = 0;
int curBossHp = 30;
std::string bossHpString = "coding/hagisilda/guichanda/";

void BossInit()
{
	curBossPhase = 0;
	curBossHp = 30;
	curBossPos = { BOSS_ORIGIN_X, BOSS_ORIGIN_Y };
}

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
		}
	}
	SetCurrentCursorPos(curBossPos.X, curBossPos.Y);
}

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

void ShowBossHpUI()
{
	SetCurrentCursorPos(BOSS_ORIGIN_X, BOSS_ORIGIN_Y - 1);
	for (int i = 0; i < 10; i++)
		std::cout << bossHpString[i];
}

void BossLifeDecrease()
{
	curBossHp--;
}