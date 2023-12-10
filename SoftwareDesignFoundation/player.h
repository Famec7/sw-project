#pragma once
#include "Cursor.h"
#include "gameInfo.h"
#include <time.h>
#include <windows.h>
#include <stdio.h>

//sound
#include<mmsystem.h>
#pragma comment(lib, "winmm.lib")
//sound

#define MAX_HP 14		//플레이어의 최대 채력		//player hp is full <= 14글자임
#define MAX_SHIELD 6	//플레이어의 최대 실드 게이지 //shield <= 6글자임
#define MAX_BULLET 5

#define PLAYER_HEIGHT 2
#define PLAYER_WIDTH 1

extern int HP;
extern int bulletNum;
extern int CantControl;
extern COORD playerCurPos;

void playerInit();
void PlayerShowModel();
void PlayerDeleteModel();
int PlayerDetectedLazer(int x, int y);
int PlayerDetectedCollision(int x, int y);
int PlayerShiftLeft();
int PlayerShiftRight();
int PlayerShiftUp();
int PlayerShiftDown();
void PlayerStatOutput();
void ProcessKeyInput();
void UseShield();
void ManageShield();
void ManageGameboard();
void PlayerUpdate();

int IsGameOver();

COORD GetPlayerPos();
void AttackedPlayerProcessing(int n); // 플레이어 피격처리 n은 감소 수치

