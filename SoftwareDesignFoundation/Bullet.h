#pragma once
#include "gameInfo.h"
#include <list>

typedef struct BulletInfo
{
	COORD curPos;
	int info;
	double speed;
	double time;
} Bullet;

void MakeBullet(int posX, int posY, int info, double speed);
void UpdateBullet();
void DeleteBullet(int arrX, int arrY);