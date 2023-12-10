#pragma once
#include <Windows.h>

#define MAX_TEXT_HP 9

void PrintG(COORD pos);
void PrintA(COORD pos);
void PrintM(COORD pos);
void PrintE(COORD pos);
void PrintS(COORD pos);
void PrintT(COORD pos);
void PrintR(COORD pos);
void DeleteG(COORD pos);
void DeleteA(COORD pos);
void DeleteM(COORD pos);
void DeleteE(COORD pos);
void DeleteS(COORD pos);
void DeleteT(COORD pos);
void DeleteR(COORD pos);
void InitTextPos();
void PrintText();
void BlinkText();
void InitTextGBoard();
int TextDetectedCollision();
int UpdateText();
void DeleteTextGboard();
void SetMoveBox();
void DeleteMoveBox();
void InitText();

void InitMenu();
void UpdateMenu();