//#define _CRT_SECURE_NO_WARNINGS 
//#include "NormalMob.h"
//
//
//NormalMobInfo* normalMobListHead = NULL;
//
//char NORMAL_MOB_MODEL[2][2] = { // 모델링 미정
//	{1,0},
//	{1,1}
//};
//char NORMAL_MOB_HP_DATASET[][10] = {
//	{"scanf"},
//	{"printf"},
//	{"include"}
//};
//
//void CreateNormalMob() {
//	NormalMobInfo* normalMob = (NormalMobInfo*)malloc(sizeof(NormalMobInfo));
//	strcpy(normalMob->hp, NORMAL_MOB_HP_DATASET[rand() % NORMAL_MOB_HP_DATASET_CNT]);
//	normalMob->pos = MakeNormalMobPos();
//	normalMob->next = NULL;
//	if (normalMobListHead == NULL) {
//		normalMobListHead = normalMob;
//		return;
//	}
//	NormalMobInfo* lastNormalMob = normalMobListHead;
//	while (lastNormalMob->next != NULL) {
//		lastNormalMob = lastNormalMob->next;
//	}
//	lastNormalMob->next = normalMob;
//}
//void RemoveNormalMob(NormalMobInfo* deadNormalMob) {
//	NormalMobInfo* normalMob = normalMobListHead;
//	NormalMobInfo* prev = NULL;
//
//	while (normalMob != deadNormalMob) {
//		prev = normalMob;
//		normalMob = normalMob->next;
//	}
//	if (prev == NULL) { //Head에 있는 몹을 제거하는 경우, 몹이 1마리인 경우
//		normalMobListHead = deadNormalMob->next;
//		free(deadNormalMob);
//		return;
//	}
//	prev->next = deadNormalMob->next;
//	free(deadNormalMob);
//
//
//}
//void PrintNormalMob(NormalMobInfo* printingNormalMob) {
//	int normalMob_x = printingNormalMob->pos.X;
//	int normalMob_y = printingNormalMob->pos.Y;
//	int arrX = (normalMob_x - GBOARD_ORIGIN_X) / 2;
//	int arrY = normalMob_y - GBOARD_ORIGIN_Y;
//
//	SetCurrentCursorPos(normalMob_x, normalMob_y - 1); // 일반 몹 모델 위에 체력을 띄움
//	printf(printingNormalMob->hp);
//
//	for (int y = 0; y < 2; y++) {
//		for (int x = 0; x < 2; x++) {
//
//			if (NORMAL_MOB_MODEL[y][x] == 1) {
//				SetCurrentCursorPos(normalMob_x + (x * 2), normalMob_y + y);
//				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
//				printf("◆");
//				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
//				gameBoardInfo[arrY + y][arrX + x] = NORMAL_MOB;
//			}
//
//		}
//	}
//	SetCurrentCursorPos(normalMob_x, normalMob_y);
//
//}
//void ShowNormalMob() {
//	NormalMobInfo* normalMob = normalMobListHead;
//	while (normalMob != NULL) {
//		ShowOneNormalMob(normalMob);
//		normalMob = normalMob->next;
//	}
//
//}
//void ShowOneNormalMob(NormalMobInfo* normalMob) {
//	SetCurrentCursorPos(normalMob->pos.X, normalMob->pos.Y);
//	PrintNormalMob(normalMob);
//}
//void DeletePrintedNormalMob(NormalMobInfo* normalMob) {
//	int normalMob_x = normalMob->pos.X;
//	int normalMob_y = normalMob->pos.Y;
//	int arrX = (normalMob_x - GBOARD_ORIGIN_X) / 2;
//	int arrY = normalMob_y - GBOARD_ORIGIN_Y;
//
//	for (int x = 0; x < strlen(normalMob->hp); x++) {
//		SetCurrentCursorPos(normalMob_x + x, normalMob_y - 1);
//		printf(" ");
//	}
//
//	for (int y = 0; y < 2; y++) {
//		for (int x = 0; x < 2; x++) {
//
//			if (NORMAL_MOB_MODEL[y][x] == 1) {
//				SetCurrentCursorPos(normalMob_x + (x * 2), normalMob_y + y);
//				printf("  ");
//				gameBoardInfo[arrY + y][arrX + x] = 0;
//			}
//
//		}
//	}
//	SetCurrentCursorPos(normalMob_x, normalMob_y);
//}
//void DeleteOneNormalMob(NormalMobInfo* normalMob) {
//	SetCurrentCursorPos(normalMob->pos.X, normalMob->pos.Y);
//	DeletePrintedNormalMob(normalMob);
//}
//void DeleteNormalMob() {
//	NormalMobInfo* normalMob = normalMobListHead;
//	while (normalMob != NULL) {
//		DeletePrintedNormalMob(normalMob);
//		normalMob = normalMob->next;
//	}
//}
//void ShiftLeft(NormalMobInfo* normalMob) {
//	//if (!NormalMobDetectedCollision(normalMob->pos.X - 1, normalMob->pos.Y)) return;
//	DeleteOneNormalMob(normalMob);
//	normalMob->pos.X--;
//	ShowOneNormalMob(normalMob);
//}
//void ShiftRight(NormalMobInfo* normalMob) {
//	//if (!NormalMobDetectedCollision(normalMob->pos.X + 1, normalMob->pos.Y)) return;
//	DeleteOneNormalMob(normalMob);
//	normalMob->pos.X++;
//	ShowOneNormalMob(normalMob);
//
//}
//void MoveNormalMob() { // 랜덤하게 좌, 우로 움직이는 함수
//	NormalMobInfo* normalMob = normalMobListHead;
//	while (normalMob != NULL) {
//
//		int num = rand() % 2;
//		switch (num) {
//		case 0:
//			ShiftLeft(normalMob);
//			break;
//		case 1:
//			ShiftRight(normalMob);
//			break;
//		}
//		normalMob = normalMob->next;
//	}
//}
//void ShiftDown(NormalMobInfo* normalMob) {
//	//if (!NormalMobDetectedCollision(normalMob->pos.X, normalMob->pos.Y + 1)) return;
//	DeleteOneNormalMob(normalMob);
//	normalMob->pos.Y++;
//	ShowOneNormalMob(normalMob);
//}
//void NormalMobShoot() {
//
//}
//NormalMobInfo* DecreaseNormalMobHp() { // 미구현
//	NormalMobInfo* temp = NULL;
//	return temp;
//}
//int NormalMobDetectedCollision(int posX, int posY) { //미구현, 충돌하면 1리턴 그렇지 않으면 0리턴
//	return 0;
//}
//COORD MakeNormalMobPos() {
//	NormalMobInfo* normalMob = normalMobListHead;
//	int cnt = 0; // 몹의 마릿수
//	while (normalMob != NULL) {
//		cnt++;
//		normalMob = normalMob->next;
//
//	}
//	COORD pos = { 20 * (cnt + 1), 20 }; // normalMob이 아직 만들어지기 전에 위치가 결정되므로 cnt에 +1을 해줌
//	return pos;
//}
