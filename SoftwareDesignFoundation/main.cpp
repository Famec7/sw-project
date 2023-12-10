#include "GameManager.h"
#include "Init.h"
#include "Update.h"
#include "Menu.h"

int main() {
	srand(time(NULL));
	RemoveCursor();
	system("mode con:cols=100 lines=50");

	InitMenu();
	while (1) {
		Render();
		Update();

		if(Gamestate == Exit)
			break;
	}
	// Release


	return 0;
}