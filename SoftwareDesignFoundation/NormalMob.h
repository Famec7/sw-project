#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "gameInfo.h"
#include "Cursor.h"
#include "Bullet.h"
#define BULLET 4	// 적 총알
// 맵 크기

#define NORMALMOB_SIZE_Y 2
#define NORMALMOB_SIZE_X 5


#define NORMAL_MOB_HP_DATASET_CNT  3

typedef struct NormalMobInfo {
	COORD pos;
	char hp[10];
	int mobHp;
	int numberingMob; //몹의 충돌에서 몹을 구분하기 위함
	double mobIdleTime = 10;
	double moveTime = 2;
	double attackTime = 0.5;
	int state; // move == 0, attack == 1, idle == 2
	NormalMobInfo* next; // 연결리스트로 구현하기 위함
}NormalMobInfo;


void CreateNormalMob();
NormalMobInfo* RemoveNormalMob(NormalMobInfo* deadNormalMob);
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
void NormalMobShoot(NormalMobInfo* normalMob);
NormalMobInfo* DecreaseNormalMobHp(NormalMobInfo* normalMob);
void ShowNormalMobHp(NormalMobInfo* normalMob);
void NormalMobUpdate();
int NormalMobDetectedBulletCollision(NormalMobInfo* normalMob);
int NormalMobDetectedCollision(int posX, int posY, int numbering);
COORD MakeNormalMobPos();

int GetNormalMobCount();
int EmptyNormalMob();
