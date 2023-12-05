#include "GameManager.h"
#include "Init.h"
#include "Update.h"

int main() {
	srand(time(NULL));
	RemoveCursor();
	system("mode con:cols=100 lines=50");
	SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y);

	Init();
	while (1) {
		Render();
		Update();

		if(Gamestate == Exit)
			break;
	}
	// Release

	return 0;
}