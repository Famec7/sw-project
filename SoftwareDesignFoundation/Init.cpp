#include "Init.h"

void Init()
{
	InitTime();
	DrawGameBoard();
	ScreenInit();
	playerInit();
	BossInit();
	ItemInit();
	PlayerShowModel();
}