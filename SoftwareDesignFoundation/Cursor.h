#pragma once
#include <Windows.h>

void RemoveCursor();
COORD GetCurrentCursorPos();
void SetCurrentCursorPos(int x, int y);