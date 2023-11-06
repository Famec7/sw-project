#include <stdio.h>
#include "Cursor.h"
#include "Block.h"

int main()
{
	RemoveCursor();
	SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y);
	getchar();

	return 0;
}