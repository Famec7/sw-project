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

// �� ũ��
#define GBOARD_HEIGHT 100
#define GBOARD_WIDTH 100

// �� ��ġ
#define GBOARD_ORIGIN_X 10
#define GBOARD_ORIGIN_Y 3

extern int gameBoardInfo[GBOARD_HEIGHT + 1][GBOARD_WIDTH + 2];

//gameInfo�� ������ �Լ� �߰�?