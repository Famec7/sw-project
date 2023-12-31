#pragma once
#include "Cursor.h"
#include <conio.h>
#include <stdio.h>

// ���� ���
#define MAP_BOUNDARY 1
#define PLAYER 2
#define ENEMY 3
#define BULLET 4	// �� �Ѿ�
#define HP_ITEM 5
#define UPGRADE_ITEM 6
#define BOSS 7
#define NORMAL_MOB_1 1000

#define LAZER 20

// �� ũ��
#define GBOARD_HEIGHT 40
#define GBOARD_WIDTH 40

// �� ��ġ
#define GBOARD_ORIGIN_X 8
#define GBOARD_ORIGIN_Y 3

extern int gameBoardInfo[GBOARD_HEIGHT + 1][GBOARD_WIDTH + 2];

void DrawGameBoard(void);
void InitBoard();
int IsAscII(int num);