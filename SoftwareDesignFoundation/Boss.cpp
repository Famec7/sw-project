#include "Boss.h"
#include "Bullet.h"
#include "gameInfo.h"

int hellBulletModel[40] = { 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2 };

COORD muzzleCurPos = { GBOARD_ORIGIN_X + 2, BOSS_ORIGIN_Y + BOSS_SIZE_Y + 2 };

void ShowMuzzle() {
	SetCurrentCursorPos(muzzleCurPos.X, muzzleCurPos.Y);
	int arrX = (muzzleCurPos.X - GBOARD_ORIGIN_X) / 2;
	int arrY = muzzleCurPos.Y - GBOARD_ORIGIN_Y;
	int num = rand() % 40;

	int start = num - 3;
	int end = num + 2;

	if (start < 0)
	{
		start = 0;
		end = start + 5;
	}
	if (end > 40)
	{
		end = 40;
		start = end - 5;
	}
	for (int i = 0; i < 40; i++)
	{
		SetCurrentCursorPos(muzzleCurPos.X + i * 2, muzzleCurPos.Y);
		gameBoardInfo[arrY][arrX + i] = 1;

		if (i >= start && i <= end)
		{
			hellBulletModel[i] = 1;
			printf("■");
		}
		else
		{
			hellBulletModel[i] = 2;
			printf("▣");
		}
	}

	/*for (int i = 0; i < 40; i++)
	{
		SetCurrentCursorPos(muzzleCurPos.X + i * 2, muzzleCurPos.Y);
		gameBoardInfo[arrY][arrX + i] = 1;
		if (hellBulletModel[i] == 1)
		{
			printf("■");
			hellBulletModel[i] += 1;
		}
		else if (hellBulletModel[i] == 2)
		{
			printf("▣");
			hellBulletModel[i] -= 1;
		}
	}*/
}

void DeleteMuzzle() {
	SetCurrentCursorPos(muzzleCurPos.X, muzzleCurPos.Y);
	int arrX = (muzzleCurPos.X - GBOARD_ORIGIN_X) / 2;
	int arrY = muzzleCurPos.Y - GBOARD_ORIGIN_Y;

	for (int i = 0; i < 40; i++)
	{
		SetCurrentCursorPos(muzzleCurPos.X + i * 2, muzzleCurPos.Y);
		gameBoardInfo[arrY][arrX + i] = 0;
		printf("  ");
	}
}

void FireBullet() {
	srand(time(NULL));
	SetCurrentCursorPos(muzzleCurPos.X, muzzleCurPos.Y);

	for (int i = 0; i < 40; i++)
	{
		SetCurrentCursorPos(muzzleCurPos.X + i * 2, muzzleCurPos.Y + 1);
		if (hellBulletModel[i] == 2)
		{
			double speed = 0.1 + ((double)rand() / RAND_MAX) * 0.2;
			MakeBullet(muzzleCurPos.X + i * 2, muzzleCurPos.Y + 1, 4, speed);
		}
	}
}

int bossModel[][BOSS_SIZE_Y][BOSS_SIZE_X] = {
	{
		/*첫번째 패턴 모델*/
	/*
	■■■■■■■■■■
	■                ■
	■                ■
	■   ■      ■   ■
	■ ■  ■  ■  ■ ■
	■                ■
	■                ■
	■    ■■■■    ■
	■                ■
	■■■■■■■■■■
	*/
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 0, 0, 1, 0, 0, 1},
		{1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 1, 1, 1, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		},
		/*두번째 패턴 모델*/
	/*


		■■■■■■
		■        ■
		■●    ●■
		■        ■
		■  ■■  ■
		■■■■■■


	*/
	/*두번째 패턴 모델*/ // 1 : ■	2 : ●
	{
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 2, 0, 0, 2, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 0, 1, 1, 0, 1, 0, 0},
	{0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	},
	/*세번째 패턴 모델*/
	{
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 1, 0, 0, 1},
	{1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 1, 1, 1, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 1, 1, 1, 1, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	}
};

// 보스의 현재 상태
BossState curState = BossState::Idle;
// 보스 정보
BossInfo boss;
// 보스의 hp를 띄울 위치
COORD hpCurPos = { BOSS_ORIGIN_X - boss.hpString[boss.curPhase].length() / 2 + BOSS_SIZE_X, BOSS_ORIGIN_Y - 2 };

/****************보스 스탯 초기화 함수*********************/
void BossInit()
{
	boss.curPhase = 0;
	boss.curBossHp = boss.hpString[boss.curPhase].length();
	boss.curPos = { BOSS_ORIGIN_X, BOSS_ORIGIN_Y };
	boss.speed = 0.2;
	int length = boss.hpString[boss.curPhase].length();
	hpCurPos.X = BOSS_ORIGIN_X - length / 2 + BOSS_SIZE_X;
	hpCurPos.Y = BOSS_ORIGIN_Y - 1;
	curState = BossState::Idle;
	boss.isAttack = false;
}
/****************보스 모델을 띄우는 함수*********************/
void ShowBossModel()
{
	SetCurrentCursorPos(boss.curPos.X, boss.curPos.Y);
	int arrX = (boss.curPos.X - GBOARD_ORIGIN_X) / 2;
	int arrY = boss.curPos.Y - GBOARD_ORIGIN_Y;

	for (int y = 0; y < BOSS_SIZE_Y; y++)
	{
		for (int x = 0; x < BOSS_SIZE_X; x++)
		{
			SetCurrentCursorPos(boss.curPos.X + (x * 2), boss.curPos.Y + y);
			if (bossModel[boss.curPhase][y][x] == 1)
			{
				printf("■");
				gameBoardInfo[arrY + y][arrX + x] = BOSS;
			}
			else if (bossModel[boss.curPhase][y][x] == 2)
			{
				printf("●");
				gameBoardInfo[arrY + y][arrX + x] = BOSS;
			}
		}
	}
	SetCurrentCursorPos(boss.curPos.X, boss.curPos.Y);
}
/****************보스 모델을 삭제하는 함수*********************/
void DeleteBossModel()
{
	SetCurrentCursorPos(boss.curPos.X, boss.curPos.Y);
	int arrX = (boss.curPos.X - GBOARD_ORIGIN_X) / 2;
	int arrY = boss.curPos.Y - GBOARD_ORIGIN_Y;

	for (int y = 0; y < BOSS_SIZE_Y; y++)
	{
		for (int x = 0; x < BOSS_SIZE_X; x++)
		{
			SetCurrentCursorPos(boss.curPos.X + (x * 2), boss.curPos.Y + y);
			if (bossModel[boss.curPhase][y][x] != 0)
			{
				printf("  ");
				gameBoardInfo[arrY + y][arrX + x] = 0;
			}
		}
	}

	SetCurrentCursorPos(boss.curPos.X, boss.curPos.Y);
}
/****************보스 HP UI를 띄우는 함수*********************/
void ShowBossHpUI()
{
	//보스의 원래 위치보다 한칸 위에 표시
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	SetCurrentCursorPos(hpCurPos.X, hpCurPos.Y);
	int start = boss.hpString[boss.curPhase].length() - boss.curBossHp;
	for (int i = start; i < boss.hpString[boss.curPhase].length(); i++)
		std::cout << boss.hpString[boss.curPhase][i];
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
/****************보스 체력 한칸 줄이는 함수*********************/
void BossLifeDecrease()
{
	// 현재 체력 한칸 줄이고 다시 UI에 표시
	for (int i = 0; i < boss.hpString[boss.curPhase].length(); i++)
	{
		SetCurrentCursorPos(hpCurPos.X + i, hpCurPos.Y);
		printf(" ");
	}
	boss.curBossHp--;
	if (boss.curBossHp == 0)
		boss.curPhase += 1;
	ShowBossHpUI();
}
/****************보스를 왼쪽으로 이동하는 함수*********************/
void BossShiftLeft()
{
	if (!BossCullingCollision(boss.curPos.X - 2, boss.curPos.Y))
		return;
	DeleteBossModel();
	boss.curPos.X -= 2;
	ShowBossModel();
}
/****************보스를 오른쪽으로 이동하는 함수*********************/
void BossShiftRight()
{
	if (!BossCullingCollision(boss.curPos.X + 2, boss.curPos.Y))
		return;
	DeleteBossModel();
	boss.curPos.X += 2;
	ShowBossModel();
}

double curSpeed = boss.speed;
/****************보스의 전체적인 움직임*********************/
void BossRandomMove()
{
	srand(time(NULL));
	int direction = rand() % 2;	// 방향 정하기 0 : 오른쪽, 1 : 왼쪽
	curSpeed -= Time.deltaTime;
	if (curSpeed < 0)
	{
		if (direction == 0)
			BossShiftRight();
		else
			BossShiftLeft();
		curSpeed = boss.speed;
	}
	//int minDistance = 3;	// 최소 이동거리
	//int range = 10;	// 이동 범위
	//static int right = rand() % range + minDistance;
	//static int left = rand() % range + minDistance;
	//static int curSpeed = boss.speed;
	//if (direction == 0)
	//{
	//	for (int i = 0; i < right; i++)
	//		BossShiftRight();
	//	if(right == 0)
	//		BossShiftLeft();
	//}
	//else
	//{
	//	for (int i = 0; i < left; i++)
	//	{
	//		BossShiftLeft();
	//		Sleep(boss.speed);
	//	}
	//	for (int i = 0; i < right; i++)
	//	{
	//		BossShiftRight();
	//		Sleep(boss.speed);
	//	}
	//}
}
/****************보스 충돌 함수*********************/
int BossCullingCollision(int posX, int posY)
{
	int arrX = (posX - GBOARD_ORIGIN_X) / 2;
	int arrY = posY - GBOARD_ORIGIN_Y;

	int length = boss.hpString[boss.curPhase].length();
	for (int y = 0; y < BOSS_SIZE_Y; y++)
	{
		for (int x = 0; x < BOSS_SIZE_X; x++)
		{
			if (bossModel[y][x] != 0)
			{
				if (gameBoardInfo[arrY + y][arrX + x] != 0)
				{
					if (gameBoardInfo[arrY + y][arrX + x] != MAP_BOUNDARY)
					{
						SetCurrentCursorPos(posX + x, posY + y);
						printf("  ");
						gameBoardInfo[arrY + y][arrX + x] = 0;
					}	// 더블 버퍼링을 쓰는 방식 고민
					return 1;
				}
			}
		}
	}
	return 0;
}
int BossDetectionCollision(int posX, int posY)
{
	int arrX = (posX - GBOARD_ORIGIN_X) / 2;
	int arrY = posY - GBOARD_ORIGIN_Y;

	int length = boss.hpString[boss.curPhase].length();
	for (int y = 0; y < BOSS_SIZE_Y; y++)
	{
		for (int x = 0; x < BOSS_SIZE_X; x++)
		{
			if (bossModel[y][x] != 0)
			{
				if (gameBoardInfo[arrY + y][arrX + x] == int(boss.hpString[boss.curPhase][length - boss.curBossHp]) ||
					gameBoardInfo[arrY + y][arrX + x] - 32 == int(boss.hpString[boss.curPhase][length - boss.curBossHp]))
					return 1;
			}
		}
	}
	return 0;
}


// 4초동안 총구 돌리고 3초동안 멈출 때 총알 쏘기
// isAttack = 1 -> 총구 보이기, isAttack = 2 -> 총알 쏘기
void BossPattern1()
{
	static double showMuzzleTime = 4;
	static double fireBulletTime = 3;
	static double fireCycleTime = 0.01;

	showMuzzleTime -= Time.deltaTime;
	if (showMuzzleTime > 0 && boss.isAttack == 0)
		ShowMuzzle();
	else if (showMuzzleTime < 0 && boss.isAttack == 0)
		boss.isAttack = 1;
	else if (boss.isAttack == 1) {
		fireCycleTime -= Time.deltaTime;
		if (fireCycleTime < 0)
		{
			FireBullet();
			fireCycleTime = 1;
		}
		fireBulletTime -= Time.deltaTime;
		if (fireBulletTime < 0)
		{
			boss.isAttack = 0;
			showMuzzleTime = 4;
			fireBulletTime = 3;
			fireCycleTime = 0.01;
		}
	}
}

void BossPattern2()
{

}

void BossPattern3()
{

}

// 6 ~ 7초동안 idle
// 10~11초 동안 pattern

double idleTime = rand() % 2 + 6;
double patternOneTime = rand() % 2 + 14;

void BossUpdate()
{
	if (BossDetectionCollision(boss.curPos.X, boss.curPos.Y + 1) == 1)
		BossLifeDecrease();

	if (idleTime > 0 && curState == BossState::Idle)
		idleTime -= Time.deltaTime;
	else if (idleTime < 0) {
		curState = BossState::Pattern1;
		idleTime = rand() % 2 + 6;
	}

	if (curState == BossState::Pattern1 && patternOneTime > 0)
		patternOneTime -= Time.deltaTime;
	else if (patternOneTime < 0) {
		curState = BossState::Idle;
		patternOneTime = rand() % 2 + 10;
		DeleteMuzzle();
	}

	ShowBossModel();
	switch (curState)
	{
	case Idle:
		BossRandomMove();
		break;
	case Pattern1:
		BossPattern1();
		break;
	case Pattern2:
		BossPattern2();
		break;
	case Pattern3:
		BossPattern3();
		break;
	default:
		break;
	}
}