#define _CRT_SECURE_NO_WARNINGS
#include "Render.h"
#include <time.h>
#include <stdio.h>

const int BUF_SIZE = 128;

static int g_nScreenIndex;//콘솔 접근 인덱스
static HANDLE g_hScreen[2];//콘솔2개
int g_numOfFrame;//누적 프레임
int g_numOfFPS;//분당 프레임

char* FPSTextInfo;//콘솔에 출력할 char 포인터

clock_t CurTime;
clock_t OldTime;

void ScreenInit()
{
	g_nScreenIndex = 0;
	g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	g_numOfFrame = 0;
	g_numOfFPS = 0;
	FPSTextInfo = new char[BUF_SIZE];
	CurTime = clock();
	OldTime = clock();
}

void ScreenFlipping()
{
	SetConsoleActiveScreenBuffer(g_hScreen[g_nScreenIndex]);
	g_nScreenIndex = !g_nScreenIndex;
}

void ScreenClear()
{
	COORD Coor = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', 80 * 25, Coor, &dw);
}

void ScreenPrint(int x, int y, char* string)
{
	DWORD dw;
	COORD CursorPosition = { (short)x, (short)y };
	SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
	WriteFile(g_hScreen[g_nScreenIndex], string, strlen(string), &dw, NULL);
}

void Render()
{
	OldTime = CurTime;
	CurTime = clock();
	g_numOfFrame++;
	if (CurTime - OldTime > 1000)
	{
		g_numOfFPS = g_numOfFrame;
		g_numOfFrame = 0;
	}
	sprintf(FPSTextInfo, "FPS : %d", g_numOfFPS);
	ScreenPrint(0, 0, FPSTextInfo);
}
