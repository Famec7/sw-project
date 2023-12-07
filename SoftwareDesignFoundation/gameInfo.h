#pragma once
#include "Cursor.h"
#include <conio.h>
#include <stdio.h>
#include <time.h>

// 게임 요소
#define MAP_BOUNDARY 1
#define PLAYER 2
#define ENEMY 3
#define BULLET 4	// 적 총알
#define HP_ITEM 5
#define UPGRADE_ITEM 6
#define BOSS 7
#define NORMAL_MOB_1 8
#define NORMAL_MOB_1 9
#define NORMAL_MOB_1 10
#define NORMAL_MOB_1 11
#define LAZER 20

// 맵 크기
#define GBOARD_HEIGHT 40
#define GBOARD_WIDTH 40

// 맵 위치
#define GBOARD_ORIGIN_X 8
#define GBOARD_ORIGIN_Y 3

extern int gameBoardInfo[GBOARD_HEIGHT + 1][GBOARD_WIDTH + 2];

struct TimeStruct{
	double time;	// 게임의 총 시간 저장
	double deltaTime;
};

extern TimeStruct Time;

//gameInfo를 갱신할 함수 추가?
void InitTime();
void UpdateTime();
void DrawGameBoard(void);
void InitBoard();