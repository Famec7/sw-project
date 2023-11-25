#pragma once
#include "Bullet.h"
#include "Cursor.h"
#include "gameInfo.h"
#include "player.h"
#include <stdio.h>
#include <time.h>

#define maxCreateItem 5
#define maxItemHp 4
#define itemTime 10

typedef struct ITEM {
  int itemHp, itemId;
  double time;
  COORD itemPos;
} ITEM;

void DropItem(COORD pos);
int ItemDetectedCollision(ITEM item);
void UpdateItem();
void EraseItemHp(ITEM item);
void PrintItemHp(ITEM item);
void CreateItem(COORD pos, int itemId);
void ItemInit();
void DeleteItem(ITEM item);
void ShowItem(ITEM item);
int CreateItemRandom();
int ItemIdRandom();
void PrintItemHp(ITEM *item);
void DecreseItemHp(ITEM *item);
void InsertGameBoardInfo(ITEM item);
void DeleteGameBoardInfo(ITEM item);
