#include "player.h"
#include "Bullet.h"

int HP = MAX_HP;            // HP ì´ˆê¸°?™”
double shield = MAX_SHIELD; // ?‹¤?“œ ì´ˆê¸°?™”
COORD playerCurPos;

int countTime1, countTime2;

int bulletNum = 3; // ì´ˆì•Œ?˜ ê°œìˆ˜

int isShield_Flag =
    0; // ?‹¤?“œê°? ?‚¬?š©ì¤‘ì¸ê°? 0 == ë¯¸ì‚¬?š©, 1 == ?‚¬?š©ì¤?

int playerColor = 7; // ?”Œ? ˆ?´?–´?˜ ?ƒ‰ 7 == gray, 9 == ?ŒŒ????ƒ‰(?‹¤?“œ), 4
                     // == ë¹¨ê°„?ƒ‰(ë§ì•˜?„?•Œ)
int playerModel[5][5] = { // ì¶©ëŒ?Œ? •??? ë¨¸ë¦¬ë¶?ë¶? 3*3ë§?
    {0, 2, 2, 2, 0},
    {0, 2, 2, 2, 0},
    {2, 2, 2, 2, 2},
    {0, 2, 2, 2, 0},
    {0, 2, 0, 2, 0}};
// ?™”ë©´ì— Player ?ƒ?ƒœ ì¶œë ¥
char hpText[] = {'P', 'l', 'a', 'y', 'e', 'r', 'h',
                 'p', 'i', 's', 'f', 'u', 'l', 'l'};
char shieldText[] = {'s', 'h', 'i', 'e', 'l', 'd'};

void playerInit() {
  playerCurPos.X = 20;
  playerCurPos.Y = 20;
}
void PlayerShowModel() {
  SetCurrentCursorPos(playerCurPos.X, playerCurPos.Y);
  COORD curPos = GetCurrentCursorPos();
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), playerColor); // gray
  int x, y;
  int arrCurX = (curPos.X - GBOARD_ORIGIN_X) / 2;
  int arrCurY = (curPos.Y - GBOARD_ORIGIN_Y);
  for (y = 0; y < 5; y++) {
    for (x = 0; x < 5; x++) {
      if (playerModel[y][x] == 2) {
        SetCurrentCursorPos(curPos.X + (x * 2), curPos.Y + y);
        printf("?– ");
        gameBoardInfo[arrCurY + y][arrCurX + x] = 2;
      }
    }
  }
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                          7); // ì»¤ì„œ ?ƒ‰ ì´ˆê¸°?™”
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
          return 1; // ì´ì•Œ ì¶©ëŒ
        } else if (playerModel[y][x] != 0 &&
                   gameBoardInfo[arrY + y][arrX + x] == 1)
          return 0; // ë²? ì¶©ëŒ
        else if (playerModel[y][x] != 0 &&
                 gameBoardInfo[arrY + y][arrX + x] == 3)
          return 0; // ?  ì¶©ëŒ
        else if (playerModel[y][x] != 0 &&
                 gameBoardInfo[arrY + y][arrX + x] == 5)
          return 0; // ?•„?´?…œ ì¶©ëŒ
        else if (playerModel[y][x] != 0 &&
                 gameBoardInfo[arrY + y][arrX + x] == 6)
          return 0; // ?•„?´?…œ ì¶©ëŒ
        else if (playerModel[y][x] != 0 &&
                 gameBoardInfo[arrY + y][arrX + x] == 7)
          return 0; // ë³´ìŠ¤ ì¶©ëŒ
      }
    }
  }
  return 1;
}
int PlayerShiftLeft() {
  if (!PlayerDetectedCollision(playerCurPos.X - 2, playerCurPos.Y))
    return 0;
  PlayerDeleteModel();
  playerCurPos.X -= 2;
  SetCurrentCursorPos(playerCurPos.X, playerCurPos.Y);
  PlayerShowModel();
  return 1;
}
int PlayerShiftRight() {
  if (!PlayerDetectedCollision(playerCurPos.X + 2, playerCurPos.Y))
    return 0;
  PlayerDeleteModel();
  playerCurPos.X += 2;
  SetCurrentCursorPos(playerCurPos.X, playerCurPos.Y);
  PlayerShowModel();
  return 1;
}
int PlayerShiftUp() {
  if (!PlayerDetectedCollision(playerCurPos.X, playerCurPos.Y - 1))
    return 0;
  PlayerDeleteModel();
  playerCurPos.Y -= 1;
  SetCurrentCursorPos(playerCurPos.X, playerCurPos.Y);
  PlayerShowModel();
  return 1;
}
int PlayerShiftDown() {
  if (!PlayerDetectedCollision(playerCurPos.X, playerCurPos.Y + 1))
    return 0;
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
    if (i == HP)
      break; // HPê°? 2?´ë©? plë§? ì¶œë ¥, iê°? 2?´ë©? aë¥? ì¶œë ¥?•˜ê²Œë˜,
             // ?´ë¥? ëª»í•˜ê²? ë§‰ìŒ
    if (i == 6 || i == 8 || i == 10)
      printf(" ");
    printf("%c", hpText[i]);
  }
  SetCurrentCursorPos(10, 46);
  printf("                 ");
  SetCurrentCursorPos(10, 46);
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
  for (int i = 0; i < 6; i++) {
    if (i == (int)shield)
      break;
    printf("%c", shieldText[i]);
  }
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
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
    } else if (bulletNum == 2) {
      pos.Y = pos.Y - 1;
      pos.X = pos.X + 4;
      int arrCurX, arrCurY;
      arrCurX = (pos.X - GBOARD_ORIGIN_X) / 2;
      arrCurY = (pos.Y - GBOARD_ORIGIN_Y);
      gameBoardInfo[arrCurY][arrCurX] = input;
      gameBoardInfo[arrCurY][arrCurX + 1] = input;
    } else if (bulletNum == 3) {
      pos.Y = pos.Y - 1;
      pos.X = pos.X + 4;
      int arrCurX, arrCurY;
      arrCurX = (pos.X) / 2;
      arrCurY = (pos.Y);
      gameBoardInfo[arrCurY][arrCurX - 2] = input;
      gameBoardInfo[arrCurY][arrCurX] = input;
      gameBoardInfo[arrCurY][arrCurX + 2] = input;
    } else if (bulletNum == 4) {
      pos.Y = pos.Y - 1;
      pos.X = pos.X + 4;
      int arrCurX, arrCurY;
      arrCurX = (pos.X - GBOARD_ORIGIN_X) / 2;
      arrCurY = (pos.Y - GBOARD_ORIGIN_Y);
      gameBoardInfo[arrCurY][arrCurX - 1] = input;
      gameBoardInfo[arrCurY][arrCurX] = input;
      gameBoardInfo[arrCurY][arrCurX + 1] = input;
      gameBoardInfo[arrCurY][arrCurX + 2] = input;
    } else if (bulletNum == 5) {
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

  for (int i = 0; i <= 'z' - 'a'; i++) {
    if (GetAsyncKeyState(0x41 + i)) {
      MakeBullet(playerCurPos.X + 3, playerCurPos.Y - 2, 'a' + i, 0.1f);
    }
  }
  // return;

  // int key = 0;
  // if (_kbhit() != 0)
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
  // }
  // Sleep(25);
}
void UseShield() {
  if (shield >= 6.0f) {
    isShield_Flag = 1; // ?‹¤?“œ ?‚¬?š©ì¤?
    playerColor = 9; // ?”Œ? ˆ?´?–´?˜ ?ƒ‰??? ?ŒŒ????ƒ‰
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
  } else {
    if (shield >= MAX_SHIELD)
      return;
    shield += Time.deltaTime;
    if (shield >= MAX_SHIELD)
      shield = MAX_SHIELD;
  }
}
void ManageGameboard() {
  for (int i = 0; i < GBOARD_HEIGHT; i++) {
    for (int j = 0; j < GBOARD_WIDTH; j++) {
      if (gameBoardInfo[i][j] == 97) {
        SetCurrentCursorPos(j * 2, i);
        printf("a");
        // gameBoardInfo[i][j] = 0;
        // SetCurrentCursorPos(i + GBOARD_ORIGIN_Y, j + GBOARD_ORIGIN_X);
        // printf(" ");
        // gameBoardInfo[i - 1][j] = 97;
        // SetCurrentCursorPos(i + GBOARD_ORIGIN_Y - 1, j + GBOARD_ORIGIN_X);
        // printf("a");
      }
      if (gameBoardInfo[i][j] == 2) {
        SetCurrentCursorPos(j * 2, i);
        // printf("?– ");
        // gameBoardInfo[i][j] = 0;
        // SetCurrentCursorPos(i + GBOARD_ORIGIN_Y, j + GBOARD_ORIGIN_X);
        // printf(" ");
        // gameBoardInfo[i - 1][j] = 97;
        // SetCurrentCursorPos(i + GBOARD_ORIGIN_Y - 1, j + GBOARD_ORIGIN_X);
        // printf("a");
      }
    }
  }
}
int IsGameOver() {
  if (HP <= 0)
    return 1;
  else
    return 0;
}
