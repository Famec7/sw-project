#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "gameInfo.h"
#include "Cursor.h"
#include "Bullet.h"
#include "player.h"
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
	int type; //type == 1 일반 몹, type == 2 폭탄
	int isExplosion = 0; // 이동x 폭파 직전 상태
	double explosionTime = 0.2; // 시간 이후 폭파
	double mobIdleTime = 2;
	double moveTime = 1;
	double attackTime = 0.2;
	double tempIdleTime = 0.25; // 이동, 공격 사이의 딜레이시간
	//double delayAfterExplosionTime = 0.1;
	int state; // move == 0, attack == 1, idle == 2, tempIdle == 3, explosion == 4
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
void MoveNormalMob(NormalMobInfo* normalMob); // 랜덤하게 좌, 우로 움직이는 함수
void PrintingExplosion(NormalMobInfo* normalMob);
void ShiftLeft(NormalMobInfo* normalMob);
void ShiftRight(NormalMobInfo* normalMob);
void ShiftDown(NormalMobInfo* normalMob);
void ShiftUp(NormalMobInfo* normalMob);
void NormalMobShoot(NormalMobInfo* normalMob);
NormalMobInfo* DecreaseNormalMobHp(NormalMobInfo* normalMob);
void ShowNormalMobHp(NormalMobInfo* normalMob);
void NormalMobUpdate();
int NormalMobDetectedBulletCollision(NormalMobInfo* normalMob);
int NormalMobDetectedCollision(int posX, int posY, int numbering);
COORD MakeNormalMobPos();

int GetNormalMobCount();
int EmptyNormalMob();