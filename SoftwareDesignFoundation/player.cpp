#include "player.h"

void playerInit() {
	playerCurPos.X = 20;
	playerCurPos.Y = 20;
}
void PlayerShowModel() {
	SetCurrentCursorPos(playerCurPos.X, playerCurPos.Y);
	COORD curPos = GetCurrentCursorPos();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), playerColor);	//gray
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			SetCurrentCursorPos(curPos.X + (x * 2), curPos.Y + y);
			if (playerModel[y][x] == 2)printf("■");
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	//커서 색 초기화
	int x, y, arrCurX, arrCurY;
	for (y = 0; y < 5; y++) {
		for (x = 0; x < 5; x++) {
			arrCurX = (curPos.X - GBOARD_ORIGIN_X);
			arrCurY = (curPos.Y - GBOARD_ORIGIN_Y);
			if (playerModel[y][x] == 2)gameBoardInfo[arrCurY + y][arrCurX + x] = 2;
		}
	}
}
void PlayerDeleteModel() {
	SetCurrentCursorPos(playerCurPos.X, playerCurPos.Y);
	COORD curPos = GetCurrentCursorPos();
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			SetCurrentCursorPos(curPos.X + (x * 2), curPos.Y + y);
			if (playerModel[y][x] == 2)printf("  ");
		}
	}
	int x, y, arrCurX, arrCurY;
	for (y = 0; y < 5; y++) {
		for (x = 0; x < 5; x++) {
			arrCurX = (curPos.X - GBOARD_ORIGIN_X) / 2;
			arrCurY = (curPos.Y - GBOARD_ORIGIN_Y);
			if (playerModel[y][x] == 2)gameBoardInfo[arrCurY + y][arrCurX + x] = 0;
		}
	}
}
int PlayerDetectedCollision(int x, int y) {
	int arrX = (x - GBOARD_ORIGIN_X) / 2;
	int arrY = y - GBOARD_ORIGIN_Y;
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			if (playerModel[y][x] != 0 && gameBoardInfo[arrY + y][arrX + x] == 4) {
				HP--;
				return 1;	//총알 충돌
			}
			else if (playerModel[y][x] != 0 && gameBoardInfo[arrY + y][arrX + x]
				== 1)return 0;	//벽 충돌
			else if (playerModel[y][x] != 0 && gameBoardInfo[arrY + y][arrX + x]
				== 3)return 0;	//적 충돌
			else if (playerModel[y][x] != 0 && gameBoardInfo[arrY + y][arrX + x]
				== 5)return 0;	//아이템 충돌
			else if (playerModel[y][x] != 0 && gameBoardInfo[arrY + y][arrX + x]
				== 6)return 0;	//아이템 충돌
			else if (playerModel[y][x] != 0 && gameBoardInfo[arrY + y][arrX + x]
				== 7)return 0;	//보스 충돌
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
	SetCurrentCursorPos(10, 10);
	printf("                 ");
	SetCurrentCursorPos(10, 10);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	for (int i = 0; i < 14; i++) {
		if (i == HP)break;	//HP가 2이면 pl만 출력, i가 2이면 a를 출력하게되, 이를 못하게 막음
		if (i == 6 || i == 8 || i == 10) printf(" ");
		printf("%c", hpText[i]);
	}
	SetCurrentCursorPos(10, 16);
	printf("                 ");
	SetCurrentCursorPos(10, 16);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	for (int i = 0; i < 6; i++) {
		if (i == (int)shield)break;
		printf("%c", shieldText[i]);
	}
}
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
void ProcessKeyInput() {	//GetAsyncKeyState
	int key;
	for (int i = 0; i < 10; i++) {
		if (_kbhit() != 0) {
			key = _getch();
			switch (key) {
			case 75:
				PlayerShiftLeft();
				break;
			case 77:
				PlayerShiftRight();
				break;
			case 72:
				PlayerShiftUp();
				break;
			case 80:
				PlayerShiftDown();
				break;
			case 13:		//enter
				//UseShield();
				break;
			default:
				Attack(key);
				break;
			}
		}
		Sleep(25);
	}
}
void UseShield() {
	if (shield >= 6.0f) {
		isShield_Flag = 1;		//실드 사용중
		playerColor = 9;		//플레이어의 색은 파란색
	}
}
void ManageShield() {
	if (isShield_Flag == 1) {
		//시간을 제면서 실드지속시간을 계산함
		//실드 지속시간이 0에 수렴하게 되면 isShield_Flag = 0
	}
	else {
		//isShield_Flag == 0이면 시간에 제면서 실드를 재충전함
		//실드 충전량이 6초내지 5초를 넘지않도록함
	}
}
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
