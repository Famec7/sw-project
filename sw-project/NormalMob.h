#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "gameInfo.h"
#include "Cursor.h"
#define BULLET 4	// �� �Ѿ�
// �� ũ��




#define NORMAL_MOB_HP_DATASET_CNT  3
#define NORMAL_MOB 1 // �Ϲ� ���� �ʿ� ǥ���ϱ� ���� (����)����

typedef struct NormalMobInfo {
	COORD pos;
	char hp[10];
	NormalMobInfo* next; // ���Ḯ��Ʈ�� �����ϱ� ����
}NormalMobInfo;


void CreateNormalMob();
void RemoveNormalMob(NormalMobInfo* deadNormalMob);
void PrintNormalMob(NormalMobInfo* printingNormalMob);
void DeletePrintedNormalMob(NormalMobInfo* normalMob);
void ShowNormalMob();
void ShowOneNormalMob(NormalMobInfo* normalMob);
void DeleteNormalMob();
void DeleteOneNormalMob(NormalMobInfo* normalMob);
void MoveNormalMob(); // �����ϰ� ��, ��� �����̴� �Լ�
void ShiftLeft(NormalMobInfo* normalMob);
void ShiftRight(NormalMobInfo* normalMob);
void ShiftDown(NormalMobInfo* normalMob);
void NormalMobShoot();
NormalMobInfo* DecreaseNormalMobHp();
int NormalMobDetectedCollision(int posX, int posY);
COORD MakeNormalMobPos();
void SetCurrentCursorPos(int x, int y);
void RemoveCursor(void);