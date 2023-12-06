#include "Boss.h"
#include "Bullet.h"
#include "gameInfo.h"
#include "NormalMob.h"
#include <vector>

int hellBulletModel[40] = { 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2 };
double lazerTime;
LAZERBLOCK lazerBlock[LAZER_NUM];

int fingerUpModel[5][5] = {
	{0, 2, 0, 0, 0},
	{0, 2, 0, 0, 0},
	{0, 2, 2, 2, 0},
	{2, 2, 2, 2, 0},
	{0, 2, 2, 0, 0}
};
int fingerRightModel[5][5] = {
	{0, 0, 0, 0, 0},
	{0, 2, 0, 0, 0},
	{2, 2, 2, 2, 2},
	{2, 2, 2, 0, 0},
	{0, 2, 2, 0, 0}
};
int fingerDownModel[5][5] = {
	{0, 2, 2, 0, 0},
	{2, 2, 2, 2, 0},
	{0, 2, 2, 2, 0},
	{0, 2, 0, 0, 0},
	{0, 2, 0, 0, 0}
};
int fingerLeftModel[5][5] = {
	{0, 0, 0, 0, 0},
	{0, 0, 0, 2, 0},
	{2, 2, 2, 2, 2},
	{0, 0, 2, 2, 2},
	{0, 0, 2, 2, 0}
};

void ShowFinger(int num) {
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			SetCurrentCursorPos(boss.curPos.X + 2 * BOSS_SIZE_X + (x * 2), boss.curPos.Y + BOSS_SIZE_Y / 2 + y);
			if (num == 0) {			//up
				if (fingerUpModel[y][x] == 2) {
					printf("■");
				}
			}
			else if (num == 1) {			//right
				if (fingerRightModel[y][x] == 2) {
					printf("■");
				}
			}
			else if (num == 2) {					//down
				if (fingerDownModel[y][x] == 2) {
					printf("■");
				}
			}
			else if (num == 3) {			//left
				if (fingerLeftModel[y][x] == 2) {
					printf("■");
				}
			}

		}
	}
}
void DeleteFinger() {
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			SetCurrentCursorPos(boss.curPos.X + 2 * BOSS_SIZE_X + (x * 2), boss.curPos.Y + BOSS_SIZE_Y / 2 + y);
			printf("  ");
		}
	}
}

COORD muzzleCurPos = { GBOARD_ORIGIN_X + 2, BOSS_ORIGIN_Y + BOSS_SIZE_Y + 5 };


int start;
int end;
void ShowMuzzle() {
	SetCurrentCursorPos(muzzleCurPos.X, muzzleCurPos.Y);
	int arrX = (muzzleCurPos.X - GBOARD_ORIGIN_X) / 2;
	int arrY = muzzleCurPos.Y - GBOARD_ORIGIN_Y;
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
		// 1 : ■	2 : ●	 3 : ▣
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
	/*




	        ▲▲
		  ◀■▣▶
		  ◀▣■▶
			▼▼


	*/
	{
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 4, 4, 0, 0, 0, 0},
	{0, 0, 0, 7, 1, 3, 5, 0, 0, 0},
	{0, 0, 0, 7, 3, 1, 5, 0, 0, 0},
	{0, 0, 0, 0, 6, 6, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	}
};

// 보스의 현재 상태
BossState curState = BossState::Idle;
// 보스 정보
BossInfo boss;
// 보스의 hp를 띄울 위치
COORD hpCurPos = { BOSS_ORIGIN_X - boss.hpString[boss.curPhase].length() / 2 + BOSS_SIZE_X, BOSS_ORIGIN_Y - 2 };
RECT bossRect = { boss.curPos.X, boss.curPos.Y, boss.curPos.X + BOSS_SIZE_X * 2, boss.curPos.Y + BOSS_SIZE_Y };

int isCleared = 0;
int IsBossCleared()
{
	return isCleared;
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
			if (bossModel[boss.curPhase][y][x] != 0)
			{
				if (bossModel[boss.curPhase][y][x] == 1)
					printf("■");
				else if (bossModel[boss.curPhase][y][x] == 2)
					printf("●");
				else if (bossModel[boss.curPhase][y][x] == 3)
					printf("▣");
				else if(bossModel[boss.curPhase][y][x] == 4)
					printf("▲");
				else if (bossModel[boss.curPhase][y][x] == 5)
					printf("▶");
				else if (bossModel[boss.curPhase][y][x] == 6)
					printf("▼");
				else if (bossModel[boss.curPhase][y][x] == 7)
					printf("◀");
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
int isBlur = 0;
std::vector<int> blurPos;
void InitBlur()
{
	isBlur = 0;
	int phase = 4 - boss.curPhase;
	blurPos.clear();
	blurPos.push_back(rand() % phase);
	for (int i = 0; i < boss.hpString[boss.curPhase].length(); i++)
	{
		if (i > 0)
			if (blurPos[i - 1] == 1)
				blurPos.push_back(0);
			else
				blurPos.push_back(rand() % phase);
	}
}

/****************보스 HP UI를 띄우는 함수*********************/
void ShowBossHpUI()
{
	//보스의 원래 위치보다 한칸 위에 표시
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	SetCurrentCursorPos(hpCurPos.X, hpCurPos.Y);
	int start = boss.hpString[boss.curPhase].length() - boss.curBossHp;
	for (int i = start; i < boss.hpString[boss.curPhase].length(); i++)
	{
		if (isBlur)
		{
			if (blurPos[i] == 1)
				std::cout << "■";
			else
				std::cout << boss.hpString[boss.curPhase][i];
		}
		else
			std::cout << boss.hpString[boss.curPhase][i];
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void ChangePhase()
{
	DeleteBossModel();
	BossInit();
	boss.curPhase += 1;
	if (boss.curPhase == 3)
	{
		isCleared = 1;
	}
	//난이도 변수
	ShowBossModel();
}
/****************보스 체력 한칸 줄이는 함수*********************/
void BossLifeDecrease()
{
	// 현재 체력 한칸 줄이고 다시 UI에 표시
	for (int i = 0; i < boss.hpString[boss.curPhase].length() * 2; i++)
	{
		SetCurrentCursorPos(hpCurPos.X + i, hpCurPos.Y);
		printf("  ");
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
	ShowBossHpUI();
	InitBlur();
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

void StartGoToDown();															//ImAdded
void StartGoToLeft();															//ImAdded
void StartGoToRight();															//ImAdded
void UpdateGoTo();
void StartLazerState();
void UpdateLazerState();

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
	case BossState::GoToDown:				
		StartGoToDown();
		break;
	case BossState::GoToLeft:			
		StartGoToLeft();
		break;
	case BossState::GoToRight:			
		StartGoToRight();
		break;
	case BossState::Lazer:
		StartLazerState();
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
	case Summon:
		UpdateSummonState();
		break;
	case GoToDown:
		UpdateGoTo();
		break;
	case GoToLeft:
		UpdateGoTo();
		break;
	case GoToRight:
		UpdateGoTo();
		break;
	case Lazer:
		UpdateLazerState();
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
	static double idleTime = rand() % 2 + 2;

	if (idleTime < 0)
	{
		idleTime = rand() % 2 + 2;
		BossState nextState = (enum BossState)((int)(Time.time * 100) % ((int)BossState::StateCount - 3) + 3);
		ChangeState(BossState::GoToDown);
	}
	else
	{
		BossRandomMove();
		idleTime -= Time.deltaTime;
	}
}

double showMuzzleTime;
double fireBulletTime;
double fireCycleTime;

void SetMuzzleState(int s, int e)
{
	start = s;
	end = e;
	if (start < 1)
	{
		start = 1;
		end = start + 5;
	}
	if (end > 39)
	{
		end = 39;
		start = end - 5;
	}
}

void InitHellBulletState()
{
	if (boss.curPhase == 0)
	{
		showMuzzleTime = 0.5;
		fireBulletTime = 1;
		fireCycleTime = 0.5;
	}
	else if (boss.curPhase == 1)
	{
		showMuzzleTime = 0.3;
		fireBulletTime = 1;
		fireCycleTime = 0.5;
	}
	else if (boss.curPhase == 2)
	{
		showMuzzleTime = 0.1;
		fireBulletTime = 1;
		fireCycleTime = 0.5;
	}

	int num = rand() % 2;
	if (start < 6)
		num = 1;
	else if (end > 34)
		num = 0;

	if (num == 0)
		SetMuzzleState(start - 5, end - 5);
	else
		SetMuzzleState(start + 5, end + 5);
}
void StartHellBulletState()
{
	curState = BossState::HellBullet;
	InitHellBulletState();
	int num = rand() % 40;
	SetMuzzleState(num - 3, num + 2);
	ShowMuzzle();
}
void UpdateHellBulletState()
{
	static int count = 0;

	if (showMuzzleTime > 0)
	{
		showMuzzleTime -= Time.deltaTime;
	}
	else
	{
		fireCycleTime -= Time.deltaTime;
		if (fireCycleTime < 0)
		{
			FireBullet();
			fireCycleTime = 0.2;
		}
		fireBulletTime -= Time.deltaTime;
		if (fireBulletTime < 0)
		{
			InitHellBulletState();
			ShowMuzzle();
			count++;
		}
	}

	if (count == 3 + boss.curPhase)
	{
		DeleteMuzzle();
		count = 0;
		ChangeState(BossState::Idle);
	}
}

double blurTime = 3;

void StartBlurState()
{
	if (boss.curPhase == 0)
	{
		ChangeState(BossState::Idle);
		return;
	}
	curState = BossState::Blur;
	blurTime = 3;
	if (isBlur)
		ChangeState(BossState::Idle);
	else
		InitBlur();
	isBlur = 1;
	ShowBossHpUI();
	ChangeState(BossState::Idle);
}
void UpdateBlurState()
{
	/*if (blurTime > 0 && isBlur)
	{
		blurTime -= Time.deltaTime;
		BossRandomMove();
	}
	else if (blurTime < 0 && isBlur)
	{
		isBlur = 0;
		for (int i = 0; i < boss.hpString[boss.curPhase].length() * 2; i++)
		{
			SetCurrentCursorPos(hpCurPos.X + i, hpCurPos.Y);
			printf("  ");
		}
		ShowBossHpUI();
		ChangeState(BossState::Idle);
	}*/
	ChangeState(BossState::Idle);
}
void StartSummonState()
{
	curState = BossState::Summon;
	SummonNormalMob();
}
void UpdateSummonState()
{
	if (EmptyNormalMob())
		ChangeState(BossState::Idle);
	BossRandomMove();
}

int dx = 0, dy = 0;
void StartGoToDown() {
	ShowFinger(0);
	Sleep(100);
	DeleteFinger();
	CantControl = 1;
	ShowFinger(2);
	curState = BossState::GoToDown;
	dx = 0, dy = 1;
}
void StartGoToLeft() {
	ShowFinger(1);
	Sleep(100);
	DeleteFinger();
	CantControl = 1;
	ShowFinger(3);
	curState = BossState::GoToLeft;
	dx = -2, dy = 0;
}
void StartGoToRight() {
	ShowFinger(3);
	Sleep(100);
	DeleteFinger();
	CantControl = 1;
	ShowFinger(1);
	curState = BossState::GoToRight;
	dx = 2, dy = 1;
}
void UpdateGoTo() {
	static double time = 0.25;

	if (!PlayerDetectedCollision(playerCurPos.X + dx, playerCurPos.Y + dy)) {
		//벽에 충돌한 효과음 추가
		DeleteFinger();
		CantControl = 0;
		time = 0.025;
		BossState nextState = (enum BossState)((int)(Time.time * 100) % ((int)BossState::StateCount - 4) + 1);
		if (curState == BossState::GoToDown)
		{
			int random = rand() % 2;
			if (random == 0)
				nextState = BossState::Lazer;
			else
				nextState = BossState::HellBullet;
		}
		ChangeState(nextState);
	}
	else if (time > 0) {
		time -= Time.deltaTime;
	}
	else
	{
		switch (curState)
		{
		case BossState::GoToDown:
			PlayerShiftDown();
			break;
		case BossState::GoToLeft:
			PlayerShiftLeft();
			break;
		case BossState::GoToRight:
			PlayerShiftRight();
			break;
		default:
			break;
		}
		time = 0.025;
	}
}

// lazer패턴 구현

void StartLazerState() {
	lazerTime = 8;
	PrintLazerWall();
	PrintLazerBlock();
}

void UpdateLazerState() {
	if (lazerTime < 0) {
		StopLazer();
		DeleteLazerBlock();
		DeleteLazerWall();
		ChangeState(BossState::Idle);
	}
	else if (lazerTime < 5) ShootLazer();
	lazerTime -= Time.deltaTime;
}

void PrintLazerWall() {
	int x;
	for (x = GBOARD_ORIGIN_X + 2; x <= GBOARD_ORIGIN_X + GBOARD_WIDTH * 2 + 1; x += 2) {
		SetCurrentCursorPos(x, 19);
		printf("□");
		gameBoardInfo[19 - GBOARD_ORIGIN_Y][(x - GBOARD_ORIGIN_X) / 2] = 1;
	}
}

void DeleteLazerWall() {
	int x;
	for (x = GBOARD_ORIGIN_X + 2; x <= GBOARD_ORIGIN_X + GBOARD_WIDTH * 2 + 1; x += 2) {
		SetCurrentCursorPos(x, 19);
		printf("  ");
		gameBoardInfo[19 - GBOARD_ORIGIN_Y][(x - GBOARD_ORIGIN_X) / 2] = 0;
	}
}


void PrintLazerBlock() {
	int i, j, k = 0, x, y;
	for (i = 0; i < LAZER_NUM; i++) {
		while (1) {
			k = 0;
			lazerBlock[i].pos.X = (rand() % (GBOARD_WIDTH * 2 - 2) + GBOARD_ORIGIN_X + 2) / 2;
			lazerBlock[i].pos.X *= 2;
			lazerBlock[i].pos.Y = rand() % (GBOARD_HEIGHT - 19) + GBOARD_ORIGIN_Y + 18;
			if (i == 0)lazerBlock[i].pos.Y = GBOARD_ORIGIN_Y + 18;
			for (j = 0; j < i; j++) {
				if (lazerBlock[i].pos.X - lazerBlock[j].pos.X >= -1 && lazerBlock[i].pos.X - lazerBlock[j].pos.X <= 1) {
					k = 1;
					continue;
				}
				if (lazerBlock[i].pos.Y == lazerBlock[j].pos.Y) {
					k = 1;
					continue;
				}
			}
			if (k == 0) break;
		}
		SetCurrentCursorPos(lazerBlock[i].pos.X + 1, lazerBlock[i].pos.Y);
		printf("□");
		gameBoardInfo[lazerBlock[i].pos.Y - GBOARD_ORIGIN_Y][(lazerBlock[i].pos.X - GBOARD_ORIGIN_X) / 2] = 1;
	}
}

void ShootLazer() {
	int i, x, y, j;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED);
	for (i = 0; i < LAZER_NUM; i++) {
		for (x = GBOARD_ORIGIN_X + 2; x <= (GBOARD_WIDTH) * 2 + GBOARD_ORIGIN_X; x++) {
			SetCurrentCursorPos(x, lazerBlock[i].pos.Y);
			if (!(x - lazerBlock[i].pos.X <= 1 && x - lazerBlock[i].pos.X > 0)) {
				printf(" ");
				gameBoardInfo[lazerBlock[i].pos.Y - GBOARD_ORIGIN_Y][(x - GBOARD_ORIGIN_X) / 2] = LAZER;
			}
		}
		for (y = 20; y < GBOARD_HEIGHT + GBOARD_ORIGIN_Y; y++) {
			SetCurrentCursorPos(lazerBlock[i].pos.X + 1, y);
			if (y != lazerBlock[i].pos.Y) {
				printf("  ");
				gameBoardInfo[y - GBOARD_ORIGIN_Y][(lazerBlock[i].pos.X - GBOARD_ORIGIN_X + 1) / 2] = LAZER;
			}
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007);
}

void StopLazer() {
	int i, x, y, j;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007);
	for (i = 0; i < LAZER_NUM; i++) {
		for (x = GBOARD_ORIGIN_X + 2; x <= (GBOARD_WIDTH) * 2 + GBOARD_ORIGIN_X; x++) {
			SetCurrentCursorPos(x, lazerBlock[i].pos.Y);
			if (!(x - lazerBlock[i].pos.X <= 1 && x - lazerBlock[i].pos.X > 0)) {
				printf(" ");
				gameBoardInfo[lazerBlock[i].pos.Y - GBOARD_ORIGIN_Y][(x - GBOARD_ORIGIN_X) / 2] = 0;
			}
		}
		for (y = 20; y < GBOARD_HEIGHT + GBOARD_ORIGIN_Y; y++) {
			SetCurrentCursorPos(lazerBlock[i].pos.X + 1, y);
			if (y != lazerBlock[i].pos.Y) {
				printf("  ");
				gameBoardInfo[y - GBOARD_ORIGIN_Y][(lazerBlock[i].pos.X - GBOARD_ORIGIN_X + 1) / 2] = 0;
			}
		}
	}
}

void DeleteLazerBlock() {
	int i, j;
	for (i = 0; i < LAZER_NUM; i++) {
		SetCurrentCursorPos(lazerBlock[i].pos.X + 1, lazerBlock[i].pos.Y);
		printf("  ");
		gameBoardInfo[lazerBlock[i].pos.Y - GBOARD_ORIGIN_Y][(lazerBlock[i].pos.X - GBOARD_ORIGIN_X) / 2] = 0;
	}
}