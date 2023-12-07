#pragma once
#include "Cursor.h"
#include <conio.h>
#include <stdio.h>
#include <time.h>

// ���� ���
#define MAP_BOUNDARY 1
#define PLAYER 2
#define ENEMY 3
#define BULLET 4	// �� �Ѿ�
#define HP_ITEM 5
#define UPGRADE_ITEM 6
#define BOSS 7
#define NORMAL_MOB_1 8
#define NORMAL_MOB_1 9
#define NORMAL_MOB_1 10
#define NORMAL_MOB_1 11
#define LAZER 20

// �� ũ��
#define GBOARD_HEIGHT 40
#define GBOARD_WIDTH 40

// �� ��ġ
#define GBOARD_ORIGIN_X 8
#define GBOARD_ORIGIN_Y 3

extern int gameBoardInfo[GBOARD_HEIGHT + 1][GBOARD_WIDTH + 2];

struct TimeStruct{
	double time;	// ������ �� �ð� ����
	double deltaTime;
};

extern TimeStruct Time;

//gameInfo�� ������ �Լ� �߰�?
void InitTime();
void UpdateTime();
void DrawGameBoard(void);
void InitBoard();