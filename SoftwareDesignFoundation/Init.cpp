#include "Init.h"

void Init()
{
	InitTime();
	ScreenInit();
	playerInit();
	BossInit();
	ItemInit();
	InitBullet();
	InitNormalMob();
	PlayerShowModel();
}