#pragma once
#include "Cursor.h"
#include "Block.h"
#include <conio.h>

// 게임 요소
#define MAP_BOUNDARY 1
#define PLAUER 2
#define ENEMY 3
#define BULLET 4	// 적 총알
#define HP_ITEM 5
#define UPGRADE_ITEM 6
#define BOSS 7

// 맵 크기
#define GBOARD_HEIGHT 100
#define GBOARD_WIDTH 100

// 맵 위치
#define GBOARD_ORIGIN_X 10
#define GBOARD_ORIGIN_Y 3

int gameBoardInfo[GBOARD_HEIGHT + 1][GBOARD_WIDTH + 2];

//gameInfo를 갱신할 함수 추가?