#define _CRT_SECURE_NO_WARNINGS 
#include "NormalMob.h"
#include "Item.h"

NormalMobInfo* normalMobListHead = NULL;
int mobCount = 0;

char NORMAL_MOB_MODEL[2][5] = { // 모델링 미정
	{1,0,0,0,1},
	{1,1,1,1,1}
};
char NORMAL_MOB_HP_DATASET[3][10] = {
	{"scanf"},
	{"printf"},
	{"include"}
};

void CreateNormalMob() {
	if (mobCount > 2)
		return;
	NormalMobInfo* normalMob = (NormalMobInfo*)malloc(sizeof(NormalMobInfo));
	strcpy(normalMob->hp, NORMAL_MOB_HP_DATASET[rand() % 3]);
	int cnt = 1;
	normalMob->pos = MakeNormalMobPos();
	normalMob->mobHp = strlen(normalMob->hp);
	normalMob->state = rand() % 3;
	normalMob->next = NULL;
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
	mobCount++;
}
NormalMobInfo* RemoveNormalMob(NormalMobInfo* deadNormalMob) {
	NormalMobInfo* normalMob = normalMobListHead;
	NormalMobInfo* prev = NULL;

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
void MoveNormalMob() { // 랜덤하게 좌, 우로 움직이는 함수
	NormalMobInfo* normalMob = normalMobListHead;
	while (normalMob != NULL) {

		int num = rand() % 2;
		switch (num) {
		case 0:
			ShiftLeft(normalMob);
			break;
		case 1:
			ShiftRight(normalMob);
			break;
		}
		normalMob = normalMob->next;
	}
}
void ShiftDown(NormalMobInfo* normalMob) {
	if (NormalMobDetectedCollision(normalMob->pos.X, normalMob->pos.Y + 1, normalMob->numberingMob) == 1)
		return;
	DeleteOneNormalMob(normalMob);
	normalMob->pos.Y++;
	ShowOneNormalMob(normalMob);
}
void NormalMobShoot(NormalMobInfo* normalMob) {
	srand(time(NULL));


	SetCurrentCursorPos(normalMob->pos.X + 5, normalMob->pos.Y + 2);

	double speed = 0.1 + ((double)rand() / RAND_MAX) * 0.05;
	MakeBullet(normalMob->pos.X + 5, normalMob->pos.Y + 2, 4, speed);


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
		COORD itemPos = normalMob->pos;
		itemPos.Y -= 1;
		DropItem(itemPos);
		mobCount--;
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
COORD MakeNormalMobPos() {
	NormalMobInfo* normalMob = normalMobListHead;
	int cnt = 0;
	while (normalMob != NULL) {
		cnt++;
		normalMob = normalMob->next;

	}
	COORD pos = { 13 + 20 * cnt, 17 };
	return pos;
}



void NormalMobUpdate() {
	NormalMobInfo* normalMob = normalMobListHead;

	ShowNormalMob();

	while (normalMob != NULL) {
		if (NormalMobDetectedBulletCollision(normalMob) == 1) {
			normalMob = DecreaseNormalMobHp(normalMob);
			if (normalMob == NULL) break;
		}


		if (normalMob->moveTime > 0 && normalMob->state == 0)
			normalMob->moveTime -= Time.deltaTime;
		else if (normalMob->moveTime < 0) {
			normalMob->state = rand() % 2 + 1;
			normalMob->moveTime = 2;
		}

		if (normalMob->state == 1 && normalMob->attackTime > 0)
			normalMob->attackTime -= Time.deltaTime;
		else if (normalMob->attackTime < 0) {
			normalMob->state = (rand() % 2) * 2;
			normalMob->attackTime = 0.5;
		}

		if (normalMob->state == 2 && normalMob->mobIdleTime > 0)
			normalMob->mobIdleTime -= Time.deltaTime;
		else if (normalMob->mobIdleTime < 0) {
			normalMob->state = rand() % 2;
			normalMob->mobIdleTime = 10;
		}
		switch (normalMob->state) {
		case 0:
			MoveNormalMob();
			break;
		case 1:
			NormalMobShoot(normalMob);
			break;
		default:
			break;
		}
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
