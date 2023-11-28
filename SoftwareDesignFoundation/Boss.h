#pragma once
#include "gameInfo.h"
#include <string>
#include <iostream>

#define BOSS_SIZE_Y 10
#define BOSS_SIZE_X 10

#define BOSS_ORIGIN_X 40
#define BOSS_ORIGIN_Y 4

#define LAZER_NUM 5

typedef struct _BossInfo
{
	COORD curPos = { BOSS_ORIGIN_X, BOSS_ORIGIN_Y };
	int curPhase = 0;	// 0�� 1��° ������
	double speed = 0.2;
	std::string hpString[3] = { "CodeIsCompileTimeError","NullReferenceException", "dsklzanfklanfslkgns" };
	int curBossHp = hpString[curPhase].length();
	int isAttack = false;
} BossInfo;

typedef struct LAZERBLOCK {
	COORD pos;
}LAZERBLOCK;

enum BossState
{
	Idle,
	HellBullet,
	Blur,
	Summon,
	Lazer,

	StateCount
};

extern BossInfo boss;

/****************���� ���� �ʱ�ȭ �Լ�*********************/
void BossInit();
/*���� ������Ʈ �Լ�*/
void UpdateBoss();

void ShowBossHpUI();


//lazer ����
void PrintLazerBlock();
void PrintLazerWall();
void ShootLazer();
void StopLazer();
void StartLazerState();
void UpdateLazerState();
void DeleteLazerBlock();
void DeleteLazerWall();