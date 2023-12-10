#include "SceneControl.h"
#include "Init.h"
#include "gameInfo.h"
#include "Menu.h"
#include "GameManager.h"

void SceneChange(enum GameState nextScene)
{
	Gamestate = nextScene;

	InitBoard();
	switch (Gamestate)
	{
	case Menu:
		InitMenu();
		break;
	case Game:
		Init();
		break;
	case GameOver:
		break;
	case GameClear:
		break;
	case Exit:
		break;
	default:
		break;
	}
}