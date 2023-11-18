#include "Item.h"

char itemModel[][3][3] = {
    {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0}
    },
    {
        {0, 0, 0},
        {0, 2, 0},
        {0, 0, 0}
    }
};

char itemHpString[5] = "item";
int curCreateItem = 0;
ITEM itemList[maxCreateItem];

int itemPosX = 0, itemPosY = 0;
int item_id = 0;

void DropItem(COORD pos) {
    int itemId;
    if (curCreateItem < maxCreateItem && CreateItemRandom()) {
        itemId = ItemIdRandom();
        CreateItem(pos, itemId);
    }
}

void CreateItem(COORD pos, int itemId) {
    int i;
    for (i = 0; i < maxCreateItem; i++) {
        if (itemList[i].itemHp == 0) {
            itemList[i].itemHp = 4;
            itemList[i].itemId = itemId;
            itemList[i].itemPos = pos;
            curCreateItem++;
            break;
        }
    }
    ShowItem(itemList[i]);
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
    for (y = 0; y < 3; y++)
    {
        for (x = 0; x < 3; x++)
        {
            SetCurrentCursorPos(curPos.X + x * 2, curPos.Y + y);
            printf("  ");
        }
    }
    SetCurrentCursorPos(curPos.X, curPos.Y);
}

void ShowItem(ITEM item) {
    int x, y;
    COORD curPos = item.itemPos;

    for (y = 0; y < 3; y++)
    {
        for (x = 0; x < 3; x++)
        {
            SetCurrentCursorPos(curPos.X + (x * 2), curPos.Y + y);
            if (itemModel[item.itemId][y][x] == 0) printf("¡á");
            else if (itemModel[item.itemId][y][x] == 1) printf("¢¾");
            else if (itemModel[item.itemId][y][x] == 2) printf("¡è");
        }
    }
    SetCurrentCursorPos(curPos.X, curPos.Y);
}

int CreateItemRandom() {
    int createItem;
    createItem = rand() % 100;
    if (createItem < 30) return 1;
    else return 0;
}

int ItemIdRandom() {
    int createItemId;
    createItemId = rand() % 2;
    if (createItemId == 0) return 0;
    else return 1;
}

void PrintItemHp(ITEM *item) {
    int i;
    SetCurrentCursorPos(item->itemPos.X, item->itemPos.Y);
    for (i = 0; i < item->itemHp; i++) {
        printf("%c", itemHpString[i]);
    }
    SetCurrentCursorPos(item->itemPos.X, item->itemPos.Y);
}

void DecreseItemHp(ITEM* item) {
    item->itemHp--;
    if (item->itemHp == 0) {
        DeleteItem(*item);
        curCreateItem--;
    }
}