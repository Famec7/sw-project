#pragma once
#include "gameInfo.h"
#include <string>
#include <iostream>
#include <time.h>

#define BOSS_SIZE_Y 10
#define BOSS_SIZE_X 10

int bossModel[][BOSS_SIZE_Y][BOSS_SIZE_X] = {
	{
		/*ù��° ���� ��*/
	/*
	�����������
	��                ��
	��                ��
	��   ��      ��   ��
	�� ��  ��  ��  �� ��
	��                ��
	��                ��
	��    �����    ��
	��                ��
	�����������
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
		/*�ι�° ���� ��*/
	/*


		�������
		��        ��
		���    �ܡ�
		��        ��
		��  ���  ��
		�������


	*/
	/*�ι�° ���� ��*/ // 1 : ��	2 : ��
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
	/*����° ���� ��*/
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

typedef struct _BossInfo
{
	COORD curPos = { BOSS_ORIGIN_X, BOSS_ORIGIN_Y };
	int curPhase = 0;	// 0�� 1��° ������
	int speed = 200;
	std::string hpString[3] = { "012345","asdadafaf", "dsklanfklanfslkgns" };
	int curBossHp = hpString[curPhase].length();
} BossInfo;

BossInfo boss;
COORD hpCurPos = { BOSS_ORIGIN_X - boss.hpString[boss.curPhase].length() / 2 + BOSS_SIZE_X, BOSS_ORIGIN_Y - 1 };

/****************���� ���� �ʱ�ȭ �Լ�*********************/
void BossInit()
{
	boss.curPhase = 0;
	boss.curBossHp = boss.hpString[boss.curPhase].length();
	boss.curPos = { BOSS_ORIGIN_X, BOSS_ORIGIN_Y };
	int length = boss.hpString[boss.curPhase].length();
	hpCurPos.X = BOSS_ORIGIN_X - length / 2 + BOSS_SIZE_X;
	hpCurPos.Y = BOSS_ORIGIN_Y - 1;
}
/****************���� ���� ���� �Լ�*********************/
void ShowBossModel(int bossModel[][10])
{
	SetCurrentCursorPos(boss.curPos.X, boss.curPos.Y);
	int arrX = (boss.curPos.X - GBOARD_ORIGIN_X) / 2;
	int arrY = boss.curPos.Y - GBOARD_ORIGIN_Y;

	for (int y = 0; y < BOSS_SIZE_Y; y++)
	{
		for (int x = 0; x < BOSS_SIZE_X; x++)
		{
			SetCurrentCursorPos(boss.curPos.X + (x * 2), boss.curPos.Y + y);
			if (bossModel[y][x] == 1)
			{
				printf("��");
				gameBoardInfo[arrY + y][arrX + x] = BOSS;
			}
			else if (bossModel[y][x] == 2)
			{
				printf("��");
				gameBoardInfo[arrY + y][arrX + x] = BOSS;
			}
		}
	}
	SetCurrentCursorPos(boss.curPos.X, boss.curPos.Y);
}
/****************���� ���� �����ϴ� �Լ�*********************/
void DeleteBossModel(int bossModel[][10])
{
	SetCurrentCursorPos(boss.curPos.X, boss.curPos.Y);
	int arrX = (boss.curPos.X - GBOARD_ORIGIN_X) / 2;
	int arrY = boss.curPos.Y - GBOARD_ORIGIN_Y;

	for (int y = 0; y < BOSS_SIZE_Y; y++)
	{
		for (int x = 0; x < BOSS_SIZE_X; x++)
		{
			SetCurrentCursorPos(boss.curPos.X + (x * 2), boss.curPos.Y + y);
			if (bossModel[y][x] != 0)
			{
				printf("  ");
				gameBoardInfo[arrY + y][arrX + x] = 0;
			}
		}
	}

	SetCurrentCursorPos(boss.curPos.X, boss.curPos.Y);
}
/****************���� HP UI�� ���� �Լ�*********************/
void ShowBossHpUI()
{
	//������ ���� ��ġ���� ��ĭ ���� ǥ��
	SetCurrentCursorPos(hpCurPos.X, hpCurPos.Y);
	for (int i = 0; i < boss.curBossHp; i++)
		std::cout << boss.hpString[boss.curPhase][i];
}
/****************���� ü�� ��ĭ ���̴� �Լ�*********************/
void BossLifeDecrease()
{
	// ���� ü�� ��ĭ ���̰� �ٽ� UI�� ǥ��
	SetCurrentCursorPos(hpCurPos.X, hpCurPos.Y);
	printf(" ");
	boss.curBossHp--;
	hpCurPos.X += 1;
}
/****************������ �������� �̵��ϴ� �Լ�*********************/
void BossShiftLeft()
{
	DeleteBossModel(bossModel[boss.curPhase]);
	boss.curPos.X -= 2;
	ShowBossModel(bossModel[boss.curPhase]);
}
/****************������ ���������� �̵��ϴ� �Լ�*********************/
void BossShiftRight()
{
	DeleteBossModel(bossModel[boss.curPhase]);
	boss.curPos.X += 2;
	ShowBossModel(bossModel[boss.curPhase]);
}
/****************������ ��ü���� ������*********************/
void BossRandomMove()
{
	srand(time(NULL));
	int direction = rand() % 2;	// ���� ���ϱ� 0 : ������, 1 : ����
	int minDistance = 3;	// �ּ� �̵��Ÿ�
	int range = 10;	// �̵� ����
	if (direction == 0)
	{
		int right = rand() % range + minDistance;
		for (int i = 0; i < right; i++)
		{
			BossShiftRight();
			Sleep(boss.speed);
		}
		int left = rand() % range + minDistance;
		for (int i = 0; i < left; i++)
		{
			BossShiftLeft();
			Sleep(boss.speed);
		}
	}
	else
	{
		int left = rand() % range + minDistance;
		for (int i = 0; i < left; i++)
		{
			BossShiftLeft();
			Sleep(boss.speed);
		}
		int right = rand() % range + minDistance;
		for (int i = 0; i < right; i++)
		{
			BossShiftRight();
			Sleep(boss.speed);
		}
	}
}
/****************���� �浹 �Լ�*********************/
int BossDetectedCollision(int posX, int posY)
{
	int arrX = (posX - GBOARD_ORIGIN_X) / 2;
	int arrY = posY - GBOARD_ORIGIN_Y;

	for (int y = 0; y < BOSS_SIZE_Y; y++)
	{
		for (int x = 0; x < BOSS_SIZE_X; x++)
		{
			if (bossModel[y][x] != 0)
			{
				if (gameBoardInfo[arrY + y][arrX + x] == int(boss.hpString[boss.curPhase][boss.curBossHp - 1]))
					return 1;
				else if (gameBoardInfo[arrY + y][arrX + x] != 0)
					return 2;
			}
		}
	}

	return 0;
}