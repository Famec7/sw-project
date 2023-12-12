#include "Item.h"
#include "gameInfo.h"
#include "Time.h"
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

char itemModel[][3][3] = { {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}},
						  {{0, 0, 0}, {0, 2, 0}, {0, 0, 0}} };

char itemHpString[5] = "item";
int curCreateItem = 0;
ITEM itemList[maxCreateItem];

int itemPosX = 0, itemPosY = 0;
int item_id = 0;

void DropItem(COORD pos) {
	int itemId;
	if ((curCreateItem < maxCreateItem) && CreateItemRandom()) {
		itemId = ItemIdRandom();
		CreateItem(pos, itemId);
	}
}

int ItemDetectedCollision(ITEM item) {
	int x, y;
	for (x = 0; x < 3; x++) {
		if (gameBoardInfo[item.itemPos.Y - GBOARD_ORIGIN_Y + 3]
			[(item.itemPos.X - GBOARD_ORIGIN_X) / 2 + x] != 0) {
			if (gameBoardInfo[item.itemPos.Y - GBOARD_ORIGIN_Y + 3]
				[(item.itemPos.X - GBOARD_ORIGIN_X) / 2 + x] ==
				itemHpString[maxItemHp - item.itemHp])
				return 1;
		}
	}
	return 0;
}

void UpdateItem() {
	int i;
	for (i = 0; i < maxCreateItem; i++) {
		if (ItemDetectedCollision(itemList[i])) {
			DecreseItemHp(&itemList[i]);
		}
		if (itemList[i].time <= 0 && itemList[i].itemHp > 0) {
			itemList[i].itemHp = 0;
			DeleteItem(itemList[i]);
			EraseItemHp(itemList[i]);
			curCreateItem--;
		}
		else if (itemList[i].time > 0 && itemList[i].itemHp > 0) {
			itemList[i].time -= Time.deltaTime;
			ShowItem(itemList[i]);
		}
	}
}

void EraseItemHp(ITEM item) {
	int i;
	SetCurrentCursorPos(item.itemPos.X + 1, item.itemPos.Y - 1);
	for (i = 0; i < maxItemHp; i++) {
		printf(" ");
	}
}

void PrintItemHp(ITEM item) {
	int i;
	SetCurrentCursorPos(item.itemPos.X + 1, item.itemPos.Y - 1);
	for (i = maxItemHp - item.itemHp; i < maxItemHp; i++) {
		printf("%c", itemHpString[i]);
	}
}

void CreateItem(COORD pos, int itemId) {
	int i, x, y;
	for (i = 0; i < maxCreateItem; i++) {
		if (itemList[i].itemHp == 0) {
			itemList[i].itemHp = 4;
			itemList[i].itemId = itemId;
			itemList[i].itemPos = pos;
			itemList[i].time = itemTime;
			curCreateItem++;
			break;
		}
	}
	ShowItem(itemList[i]);
	PrintItemHp(itemList[i]);
	InsertGameBoardInfo(itemList[i]);
}

void ItemInit() {
	int i;
	for (i = 0; i < maxCreateItem; i++) {
		itemList[i].itemHp = 0;
	}
}

void DeleteItem(ITEM item) {
	int y, x;
	COORD curPos = item.itemPos;
	for (y = 0; y < 3; y++) {
		for (x = 0; x < 3; x++) {
			SetCurrentCursorPos(curPos.X + x * 2, curPos.Y + y);
			printf("  ");
		}
	}
	DeleteGameBoardInfo(item);
	SetCurrentCursorPos(curPos.X, curPos.Y);
}

void ShowItem(ITEM item) {
	int x, y;
	COORD curPos = item.itemPos;

	for (y = 0; y < 3; y++) {
		for (x = 0; x < 3; x++) {
			SetCurrentCursorPos(curPos.X + (x * 2), curPos.Y + y);
			if (itemModel[item.itemId][y][x] == 0)
				printf("¡á");
			else if (itemModel[item.itemId][y][x] == 1)
				printf("¢¾");
			else if (itemModel[item.itemId][y][x] == 2)
				printf("¡è");
		}
	}
	SetCurrentCursorPos(curPos.X, curPos.Y);
}

int CreateItemRandom() {
	int createItem;
	createItem = rand() % 100;
	if (createItem < 70 && (HP < MAX_HP || bulletNum < MAX_BULLET))
		return 1;
	else
		return 0;
}

int ItemIdRandom() {
	int createItemId;
	createItemId = rand() % 10;
	if (createItemId < 7 || HP < 7)
		return 0;
	else if (createItemId >= 7)
		return 1;
}

void PrintItemHp(ITEM* item) {
	int i;
	SetCurrentCursorPos(item->itemPos.X, item->itemPos.Y);
	for (i = 0; i < item->itemHp; i++) {
		printf("%c", itemHpString[i]);
	}
	SetCurrentCursorPos(item->itemPos.X, item->itemPos.Y);
}

void InsertGameBoardInfo(ITEM item) {
	int x, y;
	for (y = 0; y < 3; y++) {
		for (x = 0; x < 3; x++) {
			gameBoardInfo[item.itemPos.Y - GBOARD_ORIGIN_Y + y]
				[(item.itemPos.X - GBOARD_ORIGIN_X) / 2 + x] = 5;
		}
	}
}

void DeleteGameBoardInfo(ITEM item) {
	int x, y;
	for (y = 0; y < 3; y++) {
		for (x = 0; x < 3; x++) {
			gameBoardInfo[item.itemPos.Y - GBOARD_ORIGIN_Y + y]
				[(item.itemPos.X - GBOARD_ORIGIN_X) / 2 + x] = 0;
		}
	}
}

void DecreseItemHp(ITEM* item) {
	int x, y;
	item->itemHp--;
	if (item->itemHp == 0) {
		DeleteItem(*item);
		mciSendString(TEXT("play ./sound/getItem.wav"), NULL, 0, NULL);
		for (x = 0; x < 3; x++) {
			DeleteBullet((item->itemPos.X - GBOARD_ORIGIN_X) / 2 + x,
				item->itemPos.Y - GBOARD_ORIGIN_Y + 3);
		}
		if (item->itemId == 0) {
			if (HP < MAX_HP) {
				if (HP + 2 > MAX_HP) {
					HP = MAX_HP;
				}
				else {
					HP += 2;
				}
				PlayerStatOutput();
			}
		}
		else if (item->itemId == 1) {
			if (bulletNum < 5) {
				bulletNum++;
			}
		}
		curCreateItem--;
	}
	EraseItemHp(*item);
	PrintItemHp(*item);
}