#include "Boss.h"
#include "Bullet.h"
#include "gameInfo.h"
#include "NormalMob.h"

int hellBulletModel[40] = { 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2 };

COORD muzzleCurPos = { GBOARD_ORIGIN_X + 2, BOSS_ORIGIN_Y + BOSS_SIZE_Y + 5 };

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
			double speed = 0.01 + ((double)rand() / RAND_MAX) * 0.05;
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
RECT bossRect = { boss.curPos.X, boss.curPos.Y, boss.curPos.X + BOSS_SIZE_X * 2, boss.curPos.Y + BOSS_SIZE_Y };

/****************보스 스탯 초기화 함수*********************/
void BossInit()
{
	boss.curPhase = 0;
	boss.curBossHp = boss.hpString[boss.curPhase].length();
	boss.curPos = { BOSS_ORIGIN_X, BOSS_ORIGIN_Y };
	boss.speed = 0.2;
	int length = boss.hpString[boss.curPhase].length();
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
void ChangePhase()
{
	DeleteBossModel();
	BossInit();
	boss.curPhase += 1;
	ShowBossModel();
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
		ChangePhase();
	ShowBossHpUI();
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
			if (bossModel[y][x] != 0 && gameBoardInfo[arrY + y][arrX + x] != BOSS)
			{
				if (gameBoardInfo[arrY + y][arrX + x] != 0)
				{
					if (gameBoardInfo[arrY + y][arrX + x] != MAP_BOUNDARY)
					{
						SetCurrentCursorPos(posX + x * 2, posY + y);
						printf("  ");
						gameBoardInfo[arrY + y][arrX + x] = 0;
					}
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
/****************보스를 왼쪽으로 이동하는 함수*********************/
void BossShiftLeft()
{
	if (BossCullingCollision(boss.curPos.X - 2, boss.curPos.Y))
		return;
	DeleteBossModel();
	boss.curPos.X -= 2;
	ShowBossModel();
}
/****************보스를 오른쪽으로 이동하는 함수*********************/
void BossShiftRight()
{
	if (BossCullingCollision(boss.curPos.X + 2, boss.curPos.Y))
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
}

void SummonNormalMob()
{
	int count = rand() % 4 + 1;
	for (int i = 0; i < count; i++)
		CreateNormalMob();
}

/****************보스의 패턴*********************/
void ChangeState(BossState next);
// 보스가 단순히 움직이는 상태
void StartIdleState();
void UpdateIdleState();
// 보스가 탄막을 쏘는 상태
void StartHellBulletState();
void UpdateHellBulletState();
// 보스가 블러CC기를 사용하는 상태
void StartBlurState();
void UpdateBlurState();
// 보스가 일반 몬스터를 소환하는 상태
void StartSummonState();
void UpdateSummonState();

void UpdateBoss();

void ChangeState(BossState next)
{
	curState = next;

	switch (curState)
	{
	case BossState::Idle:
		StartIdleState();
		break;
	case BossState::HellBullet:
		StartHellBulletState();
		break;
	case BossState::Blur:
		StartBlurState();
		break;
	case BossState::Summon:
		StartSummonState();
		break;
	default:
		break;
	}
}

void UpdateBoss()
{
	if (BossDetectionCollision(boss.curPos.X, boss.curPos.Y + 1) == 1)
		BossLifeDecrease();

	switch (curState)
	{
	case Idle:
		UpdateIdleState();
		break;
	case HellBullet:
		UpdateHellBulletState();
		break;
	case Blur:
		UpdateBlurState();
		break;
	case Summon:
		UpdateSummonState();
		break;
	default:
		break;
	}
}

void StartIdleState()
{
	curState = BossState::Idle;
}
void UpdateIdleState()
{
	static double idleTime = rand() % 2 + 6;

	if (idleTime < 0)
	{
		idleTime = rand() % 2 + 6;
		BossState nextState = (enum BossState)((int)(Time.time * 100) % ((int)BossState::StateCount- 1) + 1);
		ChangeState(nextState);
	}
	else
	{
		BossRandomMove();
		idleTime -= Time.deltaTime;
	}
}

double showMuzzleTime = 4;
double fireBulletTime = 3;
double fireCycleTime = 0.5;
void StartHellBulletState()
{
		curState = BossState::HellBullet;
		showMuzzleTime = 4;
		fireBulletTime = 3;
		fireCycleTime = 0.2;
}
void UpdateHellBulletState()
{
	if (showMuzzleTime > 0)
	{
		showMuzzleTime -= Time.deltaTime;
		ShowMuzzle();
	}
	else if (showMuzzleTime < 0) {
		fireCycleTime -= Time.deltaTime;
		if (fireCycleTime < 0)
		{
			FireBullet();
			fireCycleTime = 0.2;
		}
		fireBulletTime -= Time.deltaTime;
		if (fireBulletTime < 0)
		{
			showMuzzleTime = 4;
			fireBulletTime = 3;
			fireCycleTime = 0.2;
			DeleteMuzzle();
			ChangeState(BossState::Idle);
		}
	}
}

void StartBlurState()
{
	curState = BossState::Blur;
}
void UpdateBlurState()
{
	ChangeState(BossState::Idle);
}
void StartSummonState()
{
	curState = BossState::Summon;
	SummonNormalMob();
}
void UpdateSummonState()
{
	if(EmptyNormalMob())
		ChangeState(BossState::Idle);
	BossRandomMove();
}