#include "Boss.h"
#include "Bullet.h"
#include "NormalMob.h"
#include "Render.h"
#include "player.h"

int main() {
  RemoveCursor();
  SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y);
  system("mode con:cols=100 lines=50");

  ShowBossHpUI();
  InitTime();
  playerInit();
  PlayerShowModel();
  DrawGameBoard();
  ScreenInit();
  while (1) {
    ProcessKeyInput();
    UpdateTime();
    UpdateBullet();
    BossUpdate();
    PlayerUpdate();
    PlayerStatOutput();
    ManageShield();

    if (IsGameOver()) {
      SetCurrentCursorPos(25, 25);
      printf("GAME OVER!!");
      return 0;
    }
    Sleep(100);
  }
  getchar();

  return 0;
}
