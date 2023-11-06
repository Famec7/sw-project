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

COORD curBossPos = { BOSS_ORIGIN_X, BOSS_ORIGIN_Y };

int curBossPhase = 0;	// 0�� 1��° ������
int bossSpeed = 200;
std::string bossHpString = "coding/hagisilda/guichanda/aaaaaaaaaaaaaaaaa";
int curBossHp = bossHpString.length();
/****************���� ���� �ʱ�ȭ �Լ�*********************/
void BossInit()
{
	curBossPhase = 0;
	curBossHp = bossHpString.length();
	curBossPos = { BOSS_ORIGIN_X, BOSS_ORIGIN_Y };
}
/****************���� ���� ���� �Լ�*********************/
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
	SetCurrentCursorPos(curBossPos.X, curBossPos.Y);
}
/****************���� ���� �����ϴ� �Լ�*********************/
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
/****************���� HP UI�� ���� �Լ�*********************/
void ShowBossHpUI()
{
	//������ ���� ��ġ���� ��ĭ ���� ǥ��
	SetCurrentCursorPos(BOSS_ORIGIN_X - bossHpString.length() / 2 + BOSS_SIZE_X, BOSS_ORIGIN_Y - 1);
	for (int i = 0; i < curBossHp; i++)
		std::cout << bossHpString[i];
}
/****************���� ü�� ��ĭ ���̴� �Լ�*********************/
void BossLifeDecrease()
{
	// ���� ü�� ��ĭ ���̰� �ٽ� UI�� ǥ��
	curBossHp--;
	ShowBossHpUI();
}
/****************������ �������� �̵��ϴ� �Լ�*********************/
void BossShiftLeft()
{
	DeleteBossModel(bossModel[curBossPhase]);
	curBossPos.X -= 2;
	ShowBossModel(bossModel[curBossPhase]);
}
/****************������ ���������� �̵��ϴ� �Լ�*********************/
void BossShiftRight()
{
	DeleteBossModel(bossModel[curBossPhase]);
	curBossPos.X += 2;
	ShowBossModel(bossModel[curBossPhase]);
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
/****************���� �浹 �Լ�*********************/
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