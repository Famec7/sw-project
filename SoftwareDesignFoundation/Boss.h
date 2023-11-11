#pragma once
#include "gameInfo.h"
#include <string>
#include <iostream>

#define BOSS_SIZE_Y 10
#define BOSS_SIZE_X 10

#define BOSS_ORIGIN_X 40
#define BOSS_ORIGIN_Y 2

typedef struct _BossInfo
{
	COORD curPos = { BOSS_ORIGIN_X, BOSS_ORIGIN_Y };
	int curPhase = 0;	// 0�� 1��° ������
	int speed = 200;
	std::string hpString[3] = { "012345","asdadafaf", "dsklanfklanfslkgns" };
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

/*���� ������Ʈ �Լ�*/
void BossUpdate();

/****************���� ���� �ʱ�ȭ �Լ�*********************/
void BossInit();
/****************���� ���� ���� �Լ�*********************/
void ShowBossModel();
/****************���� ���� �����ϴ� �Լ�*********************/
void DeleteBossModel();
/****************���� HP UI�� ���� �Լ�*********************/
void ShowBossHpUI();
/****************���� ü�� ��ĭ ���̴� �Լ�*********************/
void BossLifeDecrease();
/****************������ �������� �̵��ϴ� �Լ�*********************/
void BossShiftLeft();
/****************������ ���������� �̵��ϴ� �Լ�*********************/
void BossShiftRight();
/****************������ ��ü���� ������*********************/
void BossRandomMove();
/****************���� �浹 �Լ�*********************/
int BossDetectedCollision(int posX, int posY);

void BossPattern1();