#pragma once
#include "Cursor.h"
#include <stdio.h>
#include <time.h>

#define maxCreateItem 5

typedef struct ITEM {
    int itemHp, itemId;
    COORD itemPos;
}ITEM;

void DropItem(COORD pos);
void CreateItem(COORD pos, int itemId);
void ItemInit();
void DeleteItem(ITEM item);
void ShowItem(ITEM item);
int CreateItemRandom();
int ItemIdRandom();
void PrintItemHp(ITEM* item);
void DecreseItemHp(ITEM* item);