#pragma once
#include "gameInfo.h"
#include "player.h"
#include <iostream>
#include <string>

#define BOSS_SIZE_Y 10
#define BOSS_SIZE_X 10

#define BOSS_ORIGIN_X 40
#define BOSS_ORIGIN_Y 4

#define MAX_LAZER_NUM 20

typedef struct _BossInfo {
  COORD curPos = {BOSS_ORIGIN_X, BOSS_ORIGIN_Y};
  int curPhase = 0; // 0이 1번째 페이즈
  double speed = 0.2;
  std::string hpString[3] = {"CodeIsCompileTimeError", "NullReferenceException",
                             "dsklzanfklanfslkgns"};
  int curBossHp = hpString[curPhase].length();
  int isAttack = false;
} BossInfo;

typedef struct LAZERBLOCK {
    int hp;
    double lazerTime;
    COORD pos;
} LAZERBLOCK;

enum BossState {
  Idle,
  HellBullet,
  Blur,
  Summon,
  Lazer,
  GoToDown, // MyAdded
  GoToLeft,
  GoToRight,
  StateCount
};

extern BossInfo boss;

/****************보스 스탯 초기화 함수*********************/
void BossInit();
/*보스 업데이트 함수*/
void UpdateBoss();

void ShowBossHpUI();

// lazer 패턴
void PrintLazerBlock(int idx);
void PrintLazerWall();
void ShootLazer(int idx);
void StopLazer(int idx);
void StartLazerState();
void UpdateLazerState();
void DeleteLazerBlock(int idx);
void DeleteLazerWall();
void InitLazer();