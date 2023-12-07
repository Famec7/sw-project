#define _CRT_SECURE_NO_WARNINGS 
#include "NormalMob.h"
#include "Item.h"

NormalMobInfo* normalMobListHead = NULL;
int mobCount = 0;

char NORMAL_MOB_MODEL[2][5] = {
	{1,0,0,0,1},
	{1,1,1,1,1}
};

char NORMAL_MOB_HP_DATASET[3][10] = {
	{"scanf"},
	{"printf"},
	{"include"}
};

void CreateNormalMob(int _type, COORD pos) {
	NormalMobInfo* normalMob = (NormalMobInfo*)malloc(sizeof(NormalMobInfo));
	strcpy(normalMob->hp, NORMAL_MOB_HP_DATASET[rand() % 3]);

	

	normalMob->pos = pos;
	normalMob->mobHp = strlen(normalMob->hp);
	normalMob->state = rand() % 2;
	normalMob->next = NULL;
	normalMob->isExplosion = 0;
	normalMob->type = _type;
	normalMob->isExpired = 0;
	normalMob->onceExplosion = 0;
	normalMob->explosionTime = 1; //시간 이후 폭파
	normalMob->mobIdleTime = 0.2;
	normalMob->attackMobIdleTime = 0.4;
	normalMob->moveTime = 2;
	normalMob->attackTime = 0.2;
	normalMob->delayExplosion = 0.05;

	mobCount++;

	if (normalMob->type == 2) normalMob->state = 0;

	int cnt = 1;

	if (normalMobListHead == NULL) {
		normalMob->numberingMob = cnt;
		normalMobListHead = normalMob;
		return;
	}

	NormalMobInfo* lastNormalMob = normalMobListHead;
	cnt++;
	while (lastNormalMob->next != NULL) {
		lastNormalMob = lastNormalMob->next;
		cnt++;
	}

	normalMob->numberingMob = cnt;
	lastNormalMob->next = normalMob;
	
}
NormalMobInfo* RemoveNormalMob(NormalMobInfo* deadNormalMob) {
	NormalMobInfo* normalMob = normalMobListHead;
	NormalMobInfo* prev = NULL;

	if(mobCount > 0)
		mobCount--;

	while (normalMob != deadNormalMob) { // 소멸하는 노말 몹 찾기
		prev = normalMob;
		normalMob = normalMob->next;
	}
	if (prev == NULL) { //Head에 있는 몹을 제거하는 경우, 몹이 1마리인 경우
		normalMobListHead = deadNormalMob->next;
		free(deadNormalMob);
		return normalMobListHead;
	}
	prev->next = deadNormalMob->next;
	free(deadNormalMob);
	return prev->next;


}
void PrintNormalMob(NormalMobInfo* printingNormalMob) {
	int normalMob_x = printingNormalMob->pos.X;
	int normalMob_y = printingNormalMob->pos.Y;
	int arrX = (normalMob_x - GBOARD_ORIGIN_X) / 2;
	int arrY = normalMob_y - GBOARD_ORIGIN_Y;

	ShowNormalMobHp(printingNormalMob);

	for (int y = 0; y < 2; y++) {
		for (int x = 0; x < 5; x++) {

			if (NORMAL_MOB_MODEL[y][x] == 1) {
				SetCurrentCursorPos(normalMob_x + (x * 2), normalMob_y + y);
				if (printingNormalMob->type == 2 && printingNormalMob->isExplosion == 0)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				else if ((printingNormalMob->type == 2 && printingNormalMob->isExplosion == 1) || printingNormalMob->isExpired == 1)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("◆");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				gameBoardInfo[arrY + y][arrX + x] = NORMAL_MOB_1 + printingNormalMob->numberingMob - 1;
			}

		}
	}
	SetCurrentCursorPos(normalMob_x, normalMob_y);

}
void ShowNormalMob() {
	NormalMobInfo* normalMob = normalMobListHead;
	while (normalMob != NULL) {
		ShowOneNormalMob(normalMob);
		normalMob = normalMob->next;
	}

}
void ShowOneNormalMob(NormalMobInfo* normalMob) {
	SetCurrentCursorPos(normalMob->pos.X, normalMob->pos.Y);
	PrintNormalMob(normalMob);
}
void DeletePrintedNormalMob(NormalMobInfo* normalMob) {
	int normalMob_x = normalMob->pos.X;
	int normalMob_y = normalMob->pos.Y;
	int arrX = (normalMob_x - GBOARD_ORIGIN_X) / 2;
	int arrY = normalMob_y - GBOARD_ORIGIN_Y;

	for (int x = 0; x < normalMob->mobHp; x++) {
		SetCurrentCursorPos(normalMob_x + x, normalMob_y - 1);
		printf(" ");
	}

	for (int y = 0; y < 2; y++) {
		for (int x = 0; x < 5; x++) {

			if (NORMAL_MOB_MODEL[y][x] == 1) {
				SetCurrentCursorPos(normalMob_x + (x * 2), normalMob_y + y);
				printf("  ");
				gameBoardInfo[arrY + y][arrX + x] = 0;
			}

		}
	}
	SetCurrentCursorPos(normalMob_x, normalMob_y);
}
void DeleteOneNormalMob(NormalMobInfo* normalMob) {
	SetCurrentCursorPos(normalMob->pos.X, normalMob->pos.Y);
	DeletePrintedNormalMob(normalMob);
}
void DeleteNormalMob() {
	NormalMobInfo* normalMob = normalMobListHead;
	while (normalMob != NULL) {
		DeletePrintedNormalMob(normalMob);
		normalMob = normalMob->next;
	}
}
void ShiftLeft(NormalMobInfo* normalMob) {
	if (NormalMobDetectedCollision(normalMob->pos.X - 2, normalMob->pos.Y, normalMob->numberingMob) == 1)
		return;
	DeleteOneNormalMob(normalMob);
	normalMob->pos.X -= 2;
	ShowOneNormalMob(normalMob);
}
void ShiftRight(NormalMobInfo* normalMob) {
	if (NormalMobDetectedCollision(normalMob->pos.X + 2, normalMob->pos.Y, normalMob->numberingMob) == 1)
		return;
	DeleteOneNormalMob(normalMob);
	normalMob->pos.X += 2;
	ShowOneNormalMob(normalMob);

}

void InitNormalMob() {
	DeleteNormalMob();
	NormalMobInfo* normalMob = normalMobListHead;
	while (normalMob != nullptr) {
		normalMob = RemoveNormalMob(normalMob);
	}
}
void PrintingExplosion(NormalMobInfo* normalMob) {
	int normalMobPosX = normalMob->pos.X;
	int normalMobPosY = normalMob->pos.Y;

	int EXPLOSION_HIT = 0;
	for (int i = -4; i < 12; i += 2) {
		for (int j = -2; j < 6; j++) {
			int board_x = (normalMobPosX + i - GBOARD_ORIGIN_X) / 2;
			int board_y = normalMobPosY + j - GBOARD_ORIGIN_Y;
			if (gameBoardInfo[board_y][board_x] == MAP_BOUNDARY)
				continue;
			if (EXPLOSION_HIT == 0 && gameBoardInfo[board_y][board_x] == PLAYER) { //플레이어 피격 시
				EXPLOSION_HIT = 1;
			}
			SetCurrentCursorPos(normalMobPosX + i, normalMobPosY + j);
			printf("＠");
		}
	}
	if (EXPLOSION_HIT == 1) {
		AttackedPlayerProcessing(3);
	}
	//mciSendString(TEXT("C:\MP_Balloon Popping(online - audio - converter.com).wav"), NULL, 0, NULL);


}
void AfterExplosion(NormalMobInfo* normalMob) {
	int normalMobPosX = normalMob->pos.X;
	int normalMobPosY = normalMob->pos.Y;

	for (int i = -4; i < 12; i += 2) {
		for (int j = -2; j < 6; j++) {
			int board_x = (normalMobPosX + i - GBOARD_ORIGIN_X) / 2;
			int board_y = normalMobPosY + j - GBOARD_ORIGIN_Y;
			if (gameBoardInfo[board_y][board_x] == MAP_BOUNDARY)
				continue;

			SetCurrentCursorPos(normalMobPosX + i, normalMobPosY + j);
			printf("  ");
		}
	}
}




void MoveNormalMob(NormalMobInfo* normalMob) { // 랜덤하게 좌, 우로 움직이는 함수

	normalMob->mobIdleTime -= Time.deltaTime;
	if (normalMob->isExplosion == 1) {
		normalMob->explosionTime -= Time.deltaTime;
		if (normalMob->explosionTime < 0) {
			

			normalMob->delayExplosion -= Time.deltaTime;

			if (normalMob->delayExplosion < 0) {
				AfterExplosion(normalMob);
				RemoveNormalMob(normalMob);
				return;
			}
			if (normalMob->onceExplosion == 0) {
				DeleteOneNormalMob(normalMob);
				PrintingExplosion(normalMob);
				normalMob->onceExplosion = 1;
			}



		}
	}

	if (normalMob->mobIdleTime < 0) {
		normalMob->mobIdleTime = 0.2;
		if (normalMob->type == 1) { //일반 몹
			int num = rand() % 2;
			switch (num) {
			case 0:
				ShiftLeft(normalMob);
				break;
			case 1:
				ShiftRight(normalMob);
				break;
			}
		}
		else if (normalMob->type == 2) {// 폭탄 몹
			COORD playerPos = GetPlayerPos();
			int playerPosX = playerPos.X;
			int playerPosY = playerPos.Y;
			int normalMobPosX = normalMob->pos.X + 4;
			int normalMobPosY = normalMob->pos.Y + 1;
			double dif_x = (double)playerPosX - normalMobPosX;
			double dif_y = (double)playerPosY - normalMobPosY;

			int direction = rand() % 2; // 0 == 세로 이동,1 == 가로 이동

			if (sqrt(dif_x * dif_x + dif_y * dif_y) > 5 && normalMob->isExplosion == 0) {
				if (playerPosX == normalMobPosX) direction = 0;
				else if (playerPosY == normalMobPosY) direction = 1;

				if (direction == 0) {
					if (playerPosY - normalMobPosY < 0) ShiftUp(normalMob);
					else ShiftDown(normalMob);
				}
				else if (direction == 1) {
					if (playerPosX - normalMobPosX < 0) ShiftLeft(normalMob);
					else ShiftRight(normalMob);
				}

			}
			else {
				if (normalMob->isExplosion == 0)
					normalMob->isExplosion = 1;

			}

		}
	}

}
void ShiftDown(NormalMobInfo* normalMob) {
	if (NormalMobDetectedCollision(normalMob->pos.X, normalMob->pos.Y + 1, normalMob->numberingMob) == 1)
		return;
	DeleteOneNormalMob(normalMob);
	normalMob->pos.Y++;
	ShowOneNormalMob(normalMob);
}
void ShiftUp(NormalMobInfo* normalMob) {
	if (NormalMobDetectedCollision(normalMob->pos.X, normalMob->pos.Y - 1, normalMob->numberingMob) == 1)
		return;
	DeleteOneNormalMob(normalMob);
	normalMob->pos.Y--;
	ShowOneNormalMob(normalMob);
}
void NormalMobShoot(NormalMobInfo* normalMob) {

	normalMob->attackMobIdleTime -= Time.deltaTime;
	if (normalMob->attackMobIdleTime < 0) {
		SetCurrentCursorPos(normalMob->pos.X + 5, normalMob->pos.Y + 2);

		//double speed = 0.5 + ((double)rand() / RAND_MAX) * 0.05;
		MakeBullet(normalMob->pos.X + 5, normalMob->pos.Y + 2, 4, 0.05f);

		normalMob->attackMobIdleTime = 0.4;
	}




}
NormalMobInfo* DecreaseNormalMobHp(NormalMobInfo* normalMob) {
	// 현재 체력 한칸 줄이고 다시 UI에 표시
	for (int i = 0; i < normalMob->mobHp; i++)
	{
		SetCurrentCursorPos(normalMob->pos.X + i, normalMob->pos.Y - 1);
		printf(" ");
	}
	normalMob->mobHp--;
	if (normalMob->mobHp == 0) {
		DeleteOneNormalMob(normalMob);
		if (normalMob->type == 1) {
			COORD itemPos = normalMob->pos;
			itemPos.Y -= 1;
			DropItem(itemPos);
		}
		return RemoveNormalMob(normalMob);
	}
	ShowNormalMobHp(normalMob);
	return normalMob;

}
void ShowNormalMobHp(NormalMobInfo* normalMob) {
	int start = strlen(normalMob->hp) - normalMob->mobHp;
	int j = 0;
	for (int i = start; i < strlen(normalMob->hp); i++) {
		SetCurrentCursorPos(normalMob->pos.X + j, normalMob->pos.Y - 1);
		printf("%c", normalMob->hp[i]);
		j++;
	}
}
int NormalMobDetectedCollision(int posX, int posY, int numbering) {
	int arrX = (posX - GBOARD_ORIGIN_X) / 2;
	int arrY = posY - GBOARD_ORIGIN_Y;

	for (int y = 0; y < NORMALMOB_SIZE_Y; y++)
	{
		for (int x = 0; x < NORMALMOB_SIZE_X; x++)
		{
			if (NORMAL_MOB_MODEL[y][x] != 0 && gameBoardInfo[arrY + y][arrX + x] != 0 && gameBoardInfo[arrY + y][arrX + x] != NORMAL_MOB_1 + numbering - 1)
			{

				return 1;

			}
		}
	}
	return 0;
}
void UpdateIdleNormalMob(NormalMobInfo* normalMob) {


	if (normalMob->moveTime < 0) {
		normalMob->moveTime = 2 + rand() % 2;
		if (normalMob->type == 1)
			normalMob->state = 1;
	}
	else {
		MoveNormalMob(normalMob);
		normalMob->moveTime -= Time.deltaTime;
	}
}
void UpdateAttackNormalMob(NormalMobInfo* normalMob) {
	if (normalMob->attackTime < 0) {
		normalMob->attackTime = 2 + rand() % 2;
		normalMob->state = 0;
	}
	else {
		NormalMobShoot(normalMob);
		normalMob->attackTime -= Time.deltaTime;
	}
}

void NormalMobUpdate() {
	NormalMobInfo* normalMob = normalMobListHead;

	ShowNormalMob();

	while (normalMob != NULL) {
		if (NormalMobDetectedBulletCollision(normalMob) == 1) {
			normalMob = DecreaseNormalMobHp(normalMob);
			if (normalMob == NULL) break;
		}
		// 폭탄 몹의 경우 MoveNormalMob에서 몹을 삭제하기 때문에
		// 삭제 전의 next를 저장해놓아야 함

		NormalMobInfo* temp = normalMob->next;


		switch (normalMob->state) {
		case 0:
			UpdateIdleNormalMob(normalMob);
			break;
		case 1:
			UpdateAttackNormalMob(normalMob);
			break;
		}




		normalMob = temp;

	}

}
void ChangeMobStateToExpired() {
	NormalMobInfo* normalMob = normalMobListHead;
	while (normalMob != NULL) {
		normalMob->isExpired = 1;
		normalMob = normalMob->next;
	}
}

int NormalMobDetectedBulletCollision(NormalMobInfo* normalMob) {
	int arrX = (normalMob->pos.X - GBOARD_ORIGIN_X) / 2;
	int arrY = normalMob->pos.Y + 1 - GBOARD_ORIGIN_Y;

	int length = strlen(normalMob->hp);
	for (int y = 0; y < NORMALMOB_SIZE_Y; y++)
	{
		for (int x = 0; x < NORMALMOB_SIZE_X; x++)
		{
			if (NORMAL_MOB_MODEL[y][x] != 0)
			{
				if (gameBoardInfo[arrY + y][arrX + x] == int(normalMob->hp[length - normalMob->mobHp]) ||
					gameBoardInfo[arrY + y][arrX + x] - 32 == int(normalMob->hp[length - normalMob->mobHp]))
				{
					DeleteBullet(arrX + x, arrY + y);
					return 1;
				}
			}
		}
	}
	return 0;
}

int GetNormalMobCount() {
	return mobCount;
}

int EmptyNormalMob() {
	if (normalMobListHead == NULL)
		return 1;
	return 0;
}