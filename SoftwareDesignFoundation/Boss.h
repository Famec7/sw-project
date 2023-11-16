#pragma once
#include "gameInfo.h"
#include <string>
#include <iostream>

#define BOSS_SIZE_Y 10
#define BOSS_SIZE_X 10

#define BOSS_ORIGIN_X 40
#define BOSS_ORIGIN_Y 4

typedef struct _BossInfo
{
	COORD curPos = { BOSS_ORIGIN_X, BOSS_ORIGIN_Y };
	int curPhase = 0;	// 0이 1번째 페이즈
	double speed = 0.2;
	std::string hpString[3] = { "CodeIsCompileTimeError","asdadafaf", "dsklanfklanfslkgns" };
	int curBossHp = hpString[curPhase].length();
	int isAttack = false;
} BossInfo;

enum BossState
{
	Idle,
	Pattern1,
	Pattern2,
	Pattern3
};

extern BossInfo boss;

/*보스 업데이트 함수*/
void BossUpdate();

/****************보스 스탯 초기화 함수*********************/
void BossInit();
/****************보스 모델을 띄우는 함수*********************/
void ShowBossModel();
/****************보스 모델을 삭제하는 함수*********************/
void DeleteBossModel();
/****************보스 HP UI를 띄우는 함수*********************/
void ShowBossHpUI();
/****************보스 체력 한칸 줄이는 함수*********************/
void BossLifeDecrease();
/****************보스의 전체적인 움직임*********************/
void BossRandomMove();
/****************보스 충돌 함수*********************/
int BossCullingCollision(int posX, int posY);
int BossDetectionCollision(int posX, int posY);
void BossPattern1();