#pragma once
#include "Cursor.h"
#include "gameInfo.h"
#include "Block.h"
#include <time.h>
#include <windows.h>
#include <stdio.h>

#define MAX_HP 14		//플레이어의 최대 채력		//player hp is full <= 14글자임
#define MAX_SHIELD	 6	//플레이어의 최대 실드 게이지 //shield <= 6글자임

void playerInit();
void PlayerShowModel();
void PlayerDeleteModel();
int PlayerDetectedCollision(int x, int y);
int PlayerShiftLeft();
int PlayerShiftRight();
int PlayerShiftUp();
int PlayerShiftDown();
void PlayerStatOutput();
void Attack(int input);
void ProcessKeyInput();
void UseShield();
void ManageShield();
void ManageGameboard();

int IsGameOver();
