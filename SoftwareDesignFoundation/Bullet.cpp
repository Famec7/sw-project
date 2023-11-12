#include "Bullet.h"
#include <iostream>

std::list<Bullet> bullets;

void PrintBullet(int info)
{
	if (info == BULLET)
		printf("��");
	else
		std::cout << (char)info;
}

void MakeBullet(int posX, int posY, int info, double speed)
{
	/*�Ѿ� ������ ����Ʈ�� �߰�*/
	Bullet newBulelt;
	newBulelt.curPos.X = posX;
	newBulelt.curPos.Y = posY;
	newBulelt.info = info;
	newBulelt.speed = speed;
	newBulelt.time = newBulelt.speed;

	bullets.push_back(newBulelt);

	/*ȭ�鿡 ���*/
	SetCurrentCursorPos(posX, posY);
	PrintBullet(info);

	/*���� �����ǿ� ������Ʈ*/
	int arrX = (posX - GBOARD_ORIGIN_X) / 2;
	int arrY = posY - GBOARD_ORIGIN_Y;
	gameBoardInfo[arrY][arrX] = info;
}

int BulletDetectedCollision(int posX, int posY, int info) {
	int arrX = (posX - GBOARD_ORIGIN_X) / 2;
	int arrY = posY - GBOARD_ORIGIN_Y;

	if (info != BULLET)
	{
		if (gameBoardInfo[arrY][arrX] != 0)
			return 0;
	}

	return 1;
}

void UpdateBullet()
{
	auto itr = bullets.begin();
	while (itr != bullets.end())
	{
		(*itr).time -= Time.deltaTime;
		if ((*itr).time < 0)
		{
			int arrX = ((*itr).curPos.X - GBOARD_ORIGIN_X) / 2;
			int arrY = (*itr).curPos.Y - GBOARD_ORIGIN_Y;
			SetCurrentCursorPos((*itr).curPos.X, (*itr).curPos.Y);
			printf("  ");
			gameBoardInfo[arrY][arrX] = 0;
			(*itr).curPos.Y += 1;
			if ((*itr).info == BULLET)
				(*itr).curPos.Y += 1;
			else
				(*itr).curPos.Y -= 1;
			SetCurrentCursorPos((*itr).curPos.X, (*itr).curPos.Y);
			if (!BulletDetectedCollision((*itr).curPos.X, (*itr).curPos.Y, (*itr).info)) {
				itr = bullets.erase(itr);
				continue;
			}
			gameBoardInfo[arrY][arrX] = (*itr).info;
			PrintBullet((*itr).info);
			(*itr).time = (*itr).speed;
		}
		itr++;
	}
}