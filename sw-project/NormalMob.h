#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "gameInfo.h"
#include "Cursor.h"
#define BULLET 4	// 적 총알
// 맵 크기




#define NORMAL_MOB_HP_DATASET_CNT  3
#define NORMAL_MOB 1 // 일반 몹을 맵에 표시하기 위한 (임의)숫자

typedef struct NormalMobInfo {
	COORD pos;
	char hp[10];
	NormalMobInfo* next; // 연결리스트로 구현하기 위함
}NormalMobInfo;


void CreateNormalMob();
void RemoveNormalMob(NormalMobInfo* deadNormalMob);
void PrintNormalMob(NormalMobInfo* printingNormalMob);
void DeletePrintedNormalMob(NormalMobInfo* normalMob);
void ShowNormalMob();
void ShowOneNormalMob(NormalMobInfo* normalMob);
void DeleteNormalMob();
void DeleteOneNormalMob(NormalMobInfo* normalMob);
void MoveNormalMob(); // 랜덤하게 좌, 우로 움직이는 함수
void ShiftLeft(NormalMobInfo* normalMob);
void ShiftRight(NormalMobInfo* normalMob);
void ShiftDown(NormalMobInfo* normalMob);
void NormalMobShoot();
NormalMobInfo* DecreaseNormalMobHp();
int NormalMobDetectedCollision(int posX, int posY);
COORD MakeNormalMobPos();
void SetCurrentCursorPos(int x, int y);
void RemoveCursor(void);