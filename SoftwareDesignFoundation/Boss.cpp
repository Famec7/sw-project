#include "Boss.h"
#include "Bullet.h"
#include "gameInfo.h"

int hellBulletModel[40] = { 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2 };

COORD muzzleCurPos = { GBOARD_ORIGIN_X + 1, BOSS_ORIGIN_Y + BOSS_SIZE_Y + 2 };

void ShowMuzzle() {
	SetCurrentCursorPos(muzzleCurPos.X, muzzleCurPos.Y);
	int arrX = (muzzleCurPos.X - GBOARD_ORIGIN_X) / 2;
	int arrY = muzzleCurPos.Y - GBOARD_ORIGIN_Y;
	int num = rand() % 40;

	for (int i = 0; i < 40; i++)
	{
		SetCurrentCursorPos(muzzleCurPos.X + i * 2, muzzleCurPos.Y);
		gameBoardInfo[arrY][arrX + i] = 1;
		

		if (num == i || num == i + 1 || num == i - 1)
		{
			hellBulletModel[i] = 1;
			printf("��");
		}
		else
		{
			hellBulletModel[i] = 2;
			printf("��");
		}
	}

	/*for (int i = 0; i < 40; i++)
	{
		SetCurrentCursorPos(muzzleCurPos.X + i * 2, muzzleCurPos.Y);
		gameBoardInfo[arrY][arrX + i] = 1;
		if (hellBulletModel[i] == 1)
		{
			printf("��");
			hellBulletModel[i] += 1;
		}
		else if (hellBulletModel[i] == 2)
		{
			printf("��");
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
			double speed = 0.1 + ((double)rand() / RAND_MAX) * 0.4;
			MakeBullet(muzzleCurPos.X + i * 2, muzzleCurPos.Y + 1, 4, speed);
		}
	}
}

int bossModel[][BOSS_SIZE_Y][BOSS_SIZE_X] = {
	{
		/*ù��° ���� ��*/
	/*
	�����������
	��                ��
	��                ��
	��   ��      ��   ��
	�� ��  ��  ��  �� ��
	��                ��
	��                ��
	��    �����    ��
	��                ��
	�����������
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
		/*�ι�° ���� ��*/
	/*


		�������
		��        ��
		���    �ܡ�
		��        ��
		��  ���  ��
		�������


	*/
	/*�ι�° ���� ��*/ // 1 : ��	2 : ��
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
	/*����° ���� ��*/
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

// ������ ���� ����
BossState curState = BossState::Idle;
// ���� ����
BossInfo boss;
// ������ hp�� ��� ��ġ
COORD hpCurPos = { BOSS_ORIGIN_X - boss.hpString[boss.curPhase].length() / 2 + BOSS_SIZE_X, BOSS_ORIGIN_Y - 1 };

/****************���� ���� �ʱ�ȭ �Լ�*********************/
void BossInit()
{
	boss.curPhase = 0;
	boss.curBossHp = boss.hpString[boss.curPhase].length();
	boss.curPos = { BOSS_ORIGIN_X, BOSS_ORIGIN_Y };
	int length = boss.hpString[boss.curPhase].length();
	hpCurPos.X = BOSS_ORIGIN_X - length / 2 + BOSS_SIZE_X;
	hpCurPos.Y = BOSS_ORIGIN_Y - 1;
	curState = BossState::Idle;
	boss.isAttack = false;
}
/****************���� ���� ���� �Լ�*********************/
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
				printf("��");
				gameBoardInfo[arrY + y][arrX + x] = BOSS;
			}
			else if (bossModel[boss.curPhase][y][x] == 2)
			{
				printf("��");
				gameBoardInfo[arrY + y][arrX + x] = BOSS;
			}
		}
	}
	SetCurrentCursorPos(boss.curPos.X, boss.curPos.Y);
}
/****************���� ���� �����ϴ� �Լ�*********************/
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
/****************���� HP UI�� ���� �Լ�*********************/
void ShowBossHpUI()
{
	//������ ���� ��ġ���� ��ĭ ���� ǥ��
	SetCurrentCursorPos(hpCurPos.X, hpCurPos.Y);
	int start = boss.hpString[boss.curPhase].length() - boss.curBossHp;
	for (int i = start; i < boss.hpString[boss.curPhase].length(); i++)
		std::cout << boss.hpString[boss.curPhase][i];
}
/****************���� ü�� ��ĭ ���̴� �Լ�*********************/
void BossLifeDecrease()
{
	// ���� ü�� ��ĭ ���̰� �ٽ� UI�� ǥ��
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
/****************������ �������� �̵��ϴ� �Լ�*********************/
void BossShiftLeft()
{
	DeleteBossModel();
	boss.curPos.X -= 2;
	ShowBossModel();
}
/****************������ ���������� �̵��ϴ� �Լ�*********************/
void BossShiftRight()
{
	DeleteBossModel();
	boss.curPos.X += 2;
	ShowBossModel();
}
/****************������ ��ü���� ������*********************/
void BossRandomMove()
{
	srand(time(NULL));
	int direction = rand() % 2;	// ���� ���ϱ� 0 : ������, 1 : ����
	int minDistance = 3;	// �ּ� �̵��Ÿ�
	int range = 10;	// �̵� ����
	if (direction == 0)
	{
		int right = rand() % range + minDistance;
		for (int i = 0; i < right; i++)
		{
			BossShiftRight();
			Sleep(boss.speed);
		}
		int left = rand() % range + minDistance;
		for (int i = 0; i < left; i++)
		{
			BossShiftLeft();
			Sleep(boss.speed);
		}
	}
	else
	{
		int left = rand() % range + minDistance;
		for (int i = 0; i < left; i++)
		{
			BossShiftLeft();
			Sleep(boss.speed);
		}
		int right = rand() % range + minDistance;
		for (int i = 0; i < right; i++)
		{
			BossShiftRight();
			Sleep(boss.speed);
		}
	}
}
/****************���� �浹 �Լ�*********************/
int BossDetectedCollision(int posX, int posY)
{
	int arrX = (posX - GBOARD_ORIGIN_X) / 2;
	int arrY = posY - GBOARD_ORIGIN_Y;

	for (int y = 0; y < BOSS_SIZE_Y; y++)
	{
		for (int x = 0; x < BOSS_SIZE_X; x++)
		{
			if (bossModel[y][x] != 0)
			{
				if (gameBoardInfo[arrY + y][arrX + x] == int(boss.hpString[boss.curPhase][boss.curBossHp - 1]))
					return 1;
				else if (gameBoardInfo[arrY + y][arrX + x] != 0)
					return 2;
			}
		}
	}

	return 0;
}

// 4�ʵ��� �ѱ� ������ 3�ʵ��� ���� �� �Ѿ� ���
void BossPattern1()
{
	if (Time.time > 0)
	{
		if ((int)Time.time % 4 == 0 && boss.isAttack == 0)
		{
			boss.isAttack = 1;
		}
		else if (boss.isAttack == 1) {
			ShowMuzzle();
			boss.isAttack = 2;
		}
		else if (boss.isAttack == 2) {
			FireBullet();
			if ((int)Time.time % 3 == 0)
				boss.isAttack = 0;
		}
	}
}

void BossPattern2()
{

}

void BossPattern3()
{

}

// 6 ~ 7�ʵ��� idle
// 10~13�� ���� pattern
void BossUpdate()
{
	if (BossDetectedCollision(boss.curPos.X, boss.curPos.Y + 1) == 1)
		BossLifeDecrease();

	/*int idleTime = rand() % 2 + 6;*/
	int idleTime = 2;
	if (Time.time > idleTime)
		curState = BossState::Pattern1;

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