#include "player.h"
#include "Bullet.h"

int HP = MAX_HP;					//HP �ʱ�ȭ
float shield = MAX_SHIELD;		//�ǵ� �ʱ�ȭ
COORD playerCurPos;

int countTime1, countTime2;

int bulletNum = 3;			//�ʾ��� ����

int isShield_Flag = 0;		//�ǵ尡 ������ΰ� 0 == �̻��, 1 == �����

int playerColor = 7;		//�÷��̾��� �� 7 == gray, 9 == �Ķ���(�ǵ�), 4 == ������(�¾�����)
int playerModel[5][5] = {		//�浹������ �Ӹ��κ� 3*3��
	{0, 2, 2, 2, 0},
	{0, 2, 2, 2, 0},
	{2, 2, 2, 2, 2},
	{0, 2, 2, 2, 0},
	{0, 2, 0, 2, 0}
};
//ȭ�鿡 Player ���� ���
char hpText[] = { 'P', 'l', 'a', 'y', 'e', 'r',
				'h', 'p',
				'i', 's',
				'f', 'u', 'l', 'l' };
char shieldText[] = { 's', 'h', 'i', 'e', 'l', 'd' };

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
			if (playerModel[y][x] == 2)printf("��");
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	//Ŀ�� �� �ʱ�ȭ
	int x, y, arrCurX, arrCurY;
	for (y = 0; y < 5; y++) {
		for (x = 0; x < 5; x++) {
			arrCurX = (curPos.X - GBOARD_ORIGIN_X) / 2;
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
				return 1;	//�Ѿ� �浹
			}
			else if (playerModel[y][x] != 0 && gameBoardInfo[arrY + y][arrX + x]
				== 1)return 0;	//�� �浹
			else if (playerModel[y][x] != 0 && gameBoardInfo[arrY + y][arrX + x]
				== 3)return 0;	//�� �浹
			else if (playerModel[y][x] != 0 && gameBoardInfo[arrY + y][arrX + x]
				== 5)return 0;	//������ �浹
			else if (playerModel[y][x] != 0 && gameBoardInfo[arrY + y][arrX + x]
				== 6)return 0;	//������ �浹
			else if (playerModel[y][x] != 0 && gameBoardInfo[arrY + y][arrX + x]
				== 7)return 0;	//���� �浹
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
		if (i == HP)break;	//HP�� 2�̸� pl�� ���, i�� 2�̸� a�� ����ϰԵ�, �̸� ���ϰ� ����
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
	if (_kbhit() == 0) return;

	if (GetAsyncKeyState(VK_LEFT)) { PlayerShiftLeft();}
	if (GetAsyncKeyState(VK_RIGHT)) { PlayerShiftRight();}
	if (GetAsyncKeyState(VK_DOWN)) { PlayerShiftDown();}
	if (GetAsyncKeyState(VK_UP)) { PlayerShiftUp();}
	
	for (int i = 0; i <= 'z' - 'a'; i++)
	{
		if (GetAsyncKeyState(0x41 + i))
		{
			MakeBullet(playerCurPos.X + 3, playerCurPos.Y - 2, 'a' + i, 0.1f);
		}
	}
	//return;

	//int key = 0;
	//if (_kbhit() != 0)
	//{
	//	key = _getch();
	//	switch (key) {
	//	//case 75:
	//	//	PlayerShiftLeft();
	//	//	break;
	//	//case 77:
	//	//	PlayerShiftRight();
	//	//	break;
	//	//case 72:
	//	//	PlayerShiftUp();
	//	//	break;
	//	//case 80:
	//	//	PlayerShiftDown();
	//	//	break;
	//	//case 13:		//enter
	//	//	//UseShield();
	//	//	break;
	//	default:
	//		
	//		break;
	//	}
	//}
	//Sleep(25);
}
void UseShield() {
	if (shield >= 6.0f) {
		isShield_Flag = 1;		//�ǵ� �����
		playerColor = 9;		//�÷��̾��� ���� �Ķ���
	}
}
void ManageShield() {
	if (isShield_Flag == 1) {
		//�ð��� ���鼭 �ǵ����ӽð��� �����
		//�ǵ� ���ӽð��� 0�� �����ϰ� �Ǹ� isShield_Flag = 0
	}
	else {
		//isShield_Flag == 0�̸� �ð��� ���鼭 �ǵ带 ��������
		//�ǵ� �������� 6�ʳ��� 5�ʸ� �����ʵ�����
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
				//printf("��");
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
