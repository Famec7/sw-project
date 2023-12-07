#include "Bullet.h"
#include <iostream>

std::list<Bullet> bullets;

void PrintBullet(int info)
{
	if (info == BULLET)
		printf("▼");
	else
		printf("%c ", (char)info);
}

void InitBullet()
{
	bullets.clear();
}

void MakeBullet(int posX, int posY, int info, double speed)
{
	/*총알 정보를 리스트에 추가*/
	Bullet newBulelt;
	newBulelt.curPos.X = posX;
	newBulelt.curPos.Y = posY;
	newBulelt.info = info;
	newBulelt.speed = speed;
	newBulelt.time = newBulelt.speed;

	bullets.push_back(newBulelt);

	/*화면에 출력*/
	SetCurrentCursorPos(posX, posY);
	PrintBullet(info);

	/*게임 보드판에 업데이트*/
	int arrX = (posX - GBOARD_ORIGIN_X) / 2;
	int arrY = posY - GBOARD_ORIGIN_Y;
	gameBoardInfo[arrY][arrX] = info;
}

int BulletDetectedCollision(int posX, int posY, int info) {
	int arrX = (posX - GBOARD_ORIGIN_X) / 2;
	int arrY = posY - GBOARD_ORIGIN_Y;

	if (gameBoardInfo[arrY][arrX] != 0)
		return 0;

	return 1;
}

void DeleteBullet(int arrX, int arrY)
{
	for (auto itr = bullets.begin(); itr != bullets.end(); itr++)
	{
		int arrX2 = ((*itr).curPos.X - GBOARD_ORIGIN_X) / 2;
		int arrY2 = (*itr).curPos.Y - GBOARD_ORIGIN_Y;
		if (arrX == arrX2 && arrY == arrY2)
		{
			SetCurrentCursorPos((*itr).curPos.X, (*itr).curPos.Y);
			printf("  ");
			gameBoardInfo[arrY][arrX] = 0;
			itr = bullets.erase(itr);
			break;
		}
	}
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
			if ((*itr).info == BULLET)
				(*itr).curPos.Y += 1;
			else
				(*itr).curPos.Y -= 1;

			if (!BulletDetectedCollision((*itr).curPos.X, (*itr).curPos.Y, (*itr).info)) {
				itr = bullets.erase(itr);
				continue;
			}
			if ((*itr).info == BULLET)
				gameBoardInfo[arrY + 1][arrX] = (*itr).info;
			else
				gameBoardInfo[arrY - 1][arrX] = (*itr).info;

			SetCurrentCursorPos((*itr).curPos.X, (*itr).curPos.Y);
			PrintBullet((*itr).info);
			(*itr).time = (*itr).speed;
		}
		itr++;
	}
}