#include "Init.h"

void Init()
{
	DrawGameBoard();
	InitTime();
	ScreenInit();
	playerInit();
	BossInit();
	ItemInit();
	InitBullet();
	InitNormalMob();
	PlayerShowModel();
}