#include "player.h"
#include "Bullet.h"

double imHit = 0;
int HP = MAX_HP;					//HP 초기화
double shield = MAX_SHIELD;		//실드 초기화
COORD playerCurPos;

int countTime1, countTime2;

int bulletNum = 1;			//초알의 개수

int isShield_Flag = 0;		//실드가 사용중인가 0 == 미사용, 1 == 사용중

int playerColor = 7;		//플레이어의 색 7 == gray, 9 == 파란색(실드), 4 == 빨간색(맞았을때)
int playerModel[5][5] = {		//충돌판정은 머리부분 3*3만
	{0, 2, 2, 2, 0},
	{0, 2, 2, 2, 0},
	{2, 2, 2, 2, 2},
	{0, 2, 2, 2, 0},
	{0, 2, 0, 2, 0}
};
//화면에 Player 상태 출력
char hpText[] = { 'P', 'l', 'a', 'y', 'e', 'r',
				'h', 'p',
				'i', 's',
				'f', 'u', 'l', 'l' };
char shieldText[] = { 's', 'h', 'i', 'e', 'l', 'd' };

void playerInit() {
	playerCurPos.X = 45;
	playerCurPos.Y = 35;
}
void PlayerShowModel() {
	SetCurrentCursorPos(playerCurPos.X, playerCurPos.Y);
	COORD curPos = GetCurrentCursorPos();
	if (imHit != 0)playerColor = 4;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), playerColor);	//gray
	int x, y;
	int arrCurX = (curPos.X - GBOARD_ORIGIN_X) / 2;
	int arrCurY = (curPos.Y - GBOARD_ORIGIN_Y);
	for (y = 0; y < 5; y++) {
		for (x = 0; x < 5; x++) {
			if (playerModel[y][x] == 2) {
				SetCurrentCursorPos(curPos.X + (x * 2), curPos.Y + y);
				printf("■");
				gameBoardInfo[arrCurY + y][arrCurX + x] = 2;
			}
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	//커서 색 초기화
}
void PlayerDeleteModel() {
	SetCurrentCursorPos(playerCurPos.X, playerCurPos.Y);
	COORD curPos = GetCurrentCursorPos();
	int x, y;
	int arrCurX = (curPos.X - GBOARD_ORIGIN_X) / 2;
	int arrCurY = (curPos.Y - GBOARD_ORIGIN_Y);
	for (y = 0; y < 5; y++) {
		for (x = 0; x < 5; x++) {
			SetCurrentCursorPos(curPos.X + (x * 2), curPos.Y + y);
			if (playerModel[y][x] == 2) {
				printf("  ");
				gameBoardInfo[arrCurY + y][arrCurX + x] = 0;
			}
		}
	}
}
int PlayerDetectedCollision(int x, int y) {
	int arrX = (x - GBOARD_ORIGIN_X) / 2;
	int arrY = y - GBOARD_ORIGIN_Y;
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			if (isShield_Flag == 0) {
				if (playerModel[y][x] != 0 && gameBoardInfo[arrY + y][arrX + x] == 4) {
					HP--;
					imHit = 1;
					PlayerDeleteModel();
					PlayerShowModel();
					return 1;	//총알 충돌
				}
			}
			if (playerModel[y][x] != 0 && gameBoardInfo[arrY + y][arrX + x] == 1)return 0;	//벽 충돌
			else if (playerModel[y][x] != 0 && gameBoardInfo[arrY + y][arrX + x] == 3)return 0;	//적 충돌
			else if (playerModel[y][x] != 0 && gameBoardInfo[arrY + y][arrX + x] == 5)return 0;	//아이템 충돌
			else if (playerModel[y][x] != 0 && gameBoardInfo[arrY + y][arrX + x] == 6)return 0;	//아이템 충돌
			else if (playerModel[y][x] != 0 && gameBoardInfo[arrY + y][arrX + x] == 7)return 0;	//보스 충돌
		}
	}
	return 1;
}
int PlayerShiftLeft() {
	if (!PlayerDetectedCollision(playerCurPos.X - 2, playerCurPos.Y))return 0;
	PlayerDeleteModel();
	playerCurPos.X -= 2;
	SetCurrentCursorPos(playerCurPos.X, playerCurPos.Y);
	PlayerShowModel();
	return 1;
}
int PlayerShiftRight() {
	if (!PlayerDetectedCollision(playerCurPos.X + 2, playerCurPos.Y))return 0;
	PlayerDeleteModel();
	playerCurPos.X += 2;
	SetCurrentCursorPos(playerCurPos.X, playerCurPos.Y);
	PlayerShowModel();
	return 1;
}
int PlayerShiftUp() {
	if (!PlayerDetectedCollision(playerCurPos.X, playerCurPos.Y - 1))return 0;
	PlayerDeleteModel();
	playerCurPos.Y -= 1;
	SetCurrentCursorPos(playerCurPos.X, playerCurPos.Y);
	PlayerShowModel();
	return 1;
}
int PlayerShiftDown() {
	if (!PlayerDetectedCollision(playerCurPos.X, playerCurPos.Y + 1))return 0;
	PlayerDeleteModel();
	playerCurPos.Y += 1;
	SetCurrentCursorPos(playerCurPos.X, playerCurPos.Y);
	PlayerShowModel();
	return 1;
}
void PlayerStatOutput() {
	SetCurrentCursorPos(10, 45);
	printf("                 ");
	SetCurrentCursorPos(10, 45);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	for (int i = 0; i < 14; i++) {
		if (i == HP)break;	//HP가 2이면 pl만 출력, i가 2이면 a를 출력하게되, 이를 못하게 막음
		if (i == 6 || i == 8 || i == 10) printf(" ");
		printf("%c", hpText[i]);
	}
	SetCurrentCursorPos(10, 46);
	printf("                 ");
	SetCurrentCursorPos(10, 46);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	for (int i = 0; i < 6; i++) {
		if (i == (int)shield)break;
		printf("%c", shieldText[i]);
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
/*
void Attack(int input) {
	COORD pos = playerCurPos;
	if (input == 97) {
		if (bulletNum == 1) {
			pos.Y = pos.Y - 1;
			pos.X = pos.X + 4;
			int arrCurX, arrCurY;
			arrCurX = (pos.X - GBOARD_ORIGIN_X) / 2;
			arrCurY = (pos.Y - GBOARD_ORIGIN_Y);
			gameBoardInfo[arrCurY][arrCurX] = input;
		}
		else if (bulletNum == 2) {
			pos.Y = pos.Y - 1;
			pos.X = pos.X + 4;
			int arrCurX, arrCurY;
			arrCurX = (pos.X - GBOARD_ORIGIN_X) / 2;
			arrCurY = (pos.Y - GBOARD_ORIGIN_Y);
			gameBoardInfo[arrCurY][arrCurX] = input;
			gameBoardInfo[arrCurY][arrCurX + 1] = input;
		}
		else if (bulletNum == 3) {
			pos.Y = pos.Y - 1;
			pos.X = pos.X + 4;
			int arrCurX, arrCurY;
			arrCurX = (pos.X) / 2;
			arrCurY = (pos.Y);
			gameBoardInfo[arrCurY][arrCurX - 2] = input;
			gameBoardInfo[arrCurY][arrCurX] = input;
			gameBoardInfo[arrCurY][arrCurX + 2] = input;
		}
		else if (bulletNum == 4) {
			pos.Y = pos.Y - 1;
			pos.X = pos.X + 4;
			int arrCurX, arrCurY;
			arrCurX = (pos.X - GBOARD_ORIGIN_X) / 2;
			arrCurY = (pos.Y - GBOARD_ORIGIN_Y);
			gameBoardInfo[arrCurY][arrCurX - 1] = input;
			gameBoardInfo[arrCurY][arrCurX] = input;
			gameBoardInfo[arrCurY][arrCurX + 1] = input;
			gameBoardInfo[arrCurY][arrCurX + 2] = input;
		}
		else if (bulletNum == 5) {
			pos.Y = pos.Y - 1;
			pos.X = pos.X + 4;
			int arrCurX, arrCurY;
			arrCurX = (pos.X - GBOARD_ORIGIN_X) / 2;
			arrCurY = (pos.Y - GBOARD_ORIGIN_Y);
			gameBoardInfo[arrCurY][arrCurX - 4] = input;
			gameBoardInfo[arrCurY][arrCurX - 2] = input;
			gameBoardInfo[arrCurY][arrCurX] = input;
			gameBoardInfo[arrCurY][arrCurX + 2] = input;
			gameBoardInfo[arrCurY][arrCurX + 4] = input;
		}
	}
}
*/
void ProcessKeyInput() { // GetAsyncKeyState
	if (_kbhit() == 0)
		return;

	if (GetAsyncKeyState(VK_LEFT)) {
		PlayerShiftLeft();
	}
	if (GetAsyncKeyState(VK_RIGHT)) {
		PlayerShiftRight();
	}
	if (GetAsyncKeyState(VK_DOWN)) {
		PlayerShiftDown();
	}
	if (GetAsyncKeyState(VK_UP)) {
		PlayerShiftUp();
	}
	if (GetAsyncKeyState(VK_RETURN))
		UseShield();

	for (int i = 0; i <= 'z' - 'a'; i++) {
		if (GetAsyncKeyState(0x41 + i)) {
			if (bulletNum == 1) {
				MakeBullet(playerCurPos.X + 3, playerCurPos.Y - 2, 'a' + i, 0.1f);
			}
			else if (bulletNum == 2) {
				MakeBullet(playerCurPos.X + 3, playerCurPos.Y - 2, 'a' + i, 0.1f);
				MakeBullet(playerCurPos.X + 5, playerCurPos.Y - 2, 'a' + i, 0.1f);
			}
			else if (bulletNum == 3) {
				MakeBullet(playerCurPos.X + 1, playerCurPos.Y - 2, 'a' + i, 0.1f);
				MakeBullet(playerCurPos.X + 3, playerCurPos.Y - 2, 'a' + i, 0.1f);
				MakeBullet(playerCurPos.X + 5, playerCurPos.Y - 2, 'a' + i, 0.1f);
			}
			else if (bulletNum == 4) {
				MakeBullet(playerCurPos.X + 1, playerCurPos.Y - 2, 'a' + i, 0.1f);
				MakeBullet(playerCurPos.X + 3, playerCurPos.Y - 2, 'a' + i, 0.1f);
				MakeBullet(playerCurPos.X + 5, playerCurPos.Y - 2, 'a' + i, 0.1f);
				MakeBullet(playerCurPos.X + 7, playerCurPos.Y - 2, 'a' + i, 0.1f);
			}
			else if (bulletNum == 5) {
				MakeBullet(playerCurPos.X - 1, playerCurPos.Y - 2, 'a' + i, 0.1f);
				MakeBullet(playerCurPos.X + 1, playerCurPos.Y - 2, 'a' + i, 0.1f);
				MakeBullet(playerCurPos.X + 3, playerCurPos.Y - 2, 'a' + i, 0.1f);
				MakeBullet(playerCurPos.X + 5, playerCurPos.Y - 2, 'a' + i, 0.1f);
				MakeBullet(playerCurPos.X + 7, playerCurPos.Y - 2, 'a' + i, 0.1f);
			}
		}
	}
}
void UseShield() {
	if (shield >= 6.0f) {
		isShield_Flag = 1;		//실드 사용중
		playerColor = 9;		//플레이어의 색은 파란색
		PlayerDeleteModel();
		PlayerShowModel();
	}
}
void ManageShield() {
	if (isShield_Flag == 1) {
		shield -= Time.deltaTime;
		if (shield <= 0) {
			isShield_Flag = 0;
			shield = 0;
			playerColor = 7;
		}
	}
	else {
		if (shield >= MAX_SHIELD)return;
		shield += Time.deltaTime;
		if (shield >= MAX_SHIELD)shield = MAX_SHIELD;
	}
}
/*
void ManageGameboard() {
	for (int i = 0; i < GBOARD_HEIGHT; i++) {
		for (int j = 0; j < GBOARD_WIDTH; j++) {
			if (gameBoardInfo[i][j] == 97) {
				SetCurrentCursorPos(j * 2, i);
				printf("a");
				//gameBoardInfo[i][j] = 0;
				//SetCurrentCursorPos(i + GBOARD_ORIGIN_Y, j + GBOARD_ORIGIN_X);
				//printf(" ");
				//gameBoardInfo[i - 1][j] = 97;
				//SetCurrentCursorPos(i + GBOARD_ORIGIN_Y - 1, j + GBOARD_ORIGIN_X);
				//printf("a");
			}
			if (gameBoardInfo[i][j] == 2) {
				SetCurrentCursorPos(j * 2, i);
				//printf("■");
				//gameBoardInfo[i][j] = 0;
				//SetCurrentCursorPos(i + GBOARD_ORIGIN_Y, j + GBOARD_ORIGIN_X);
				//printf(" ");
				//gameBoardInfo[i - 1][j] = 97;
				//SetCurrentCursorPos(i + GBOARD_ORIGIN_Y - 1, j + GBOARD_ORIGIN_X);
				//printf("a");
			}
		}
	}
}
*/
void PlayerUpdate() {
	PlayerDetectedCollision(playerCurPos.X, playerCurPos.Y - 1);
	if (imHit <= 0) {
		imHit = 0;
		if (isShield_Flag == 0) {
			playerColor = 7;
		}
	}
	else {
		imHit -= Time.deltaTime;
	}
	//PlayerDetectedCollision(playerCurPos.X - 2, playerCurPos.Y);
	//PlayerDetectedCollision(playerCurPos.X + 2, playerCurPos.Y);
	//PlayerDetectedCollision(playerCurPos.X, playerCurPos.Y + 1);
	//PlayerDetectedCollision(playerCurPos.X, playerCurPos.Y - 1);
}
int IsGameOver() {
	if (HP <= 0)return 1;
	else return 0;
}
