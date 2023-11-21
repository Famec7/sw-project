#define _CRT_SECURE_NO_WARNINGS
#include "Render.h"
#include <time.h>
#include <stdio.h>

const int BUF_SIZE = 128;

static int g_nScreenIndex;//�ܼ� ���� �ε���
static HANDLE g_hScreen[2];//�ܼ�2��
int g_numOfFrame;//���� ������
int g_numOfFPS;//�д� ������

char* FPSTextInfo;//�ֿܼ� ����� char ������

clock_t CurTime;
clock_t OldTime;

void ScreenInit()
{
	FPSTextInfo = new char[BUF_SIZE];
	memset(FPSTextInfo, '\0', sizeof(char) * BUF_SIZE);
	OldTime = clock();

	CONSOLE_CURSOR_INFO cci;

	g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	// Ŀ���� �����.
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(g_hScreen[0], &cci);
	SetConsoleCursorInfo(g_hScreen[1], &cci);
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
	FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', 80 * 40, Coor, &dw);
}

void ScreenPrint(int x, int y, char* string)
{
	DWORD dw;
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
	WriteFile(g_hScreen[g_nScreenIndex], string, strlen(string), &dw, NULL);
}

void Render()
{
	ScreenClear();
	if (CurTime - OldTime >= 1000) // ��� �ڵ�
	{
		sprintf(FPSTextInfo, "FPS : %d", g_numOfFPS);
		OldTime = CurTime;
		g_numOfFrame = 0;
	}
	g_numOfFrame++;
	ScreenPrint(0, 0, FPSTextInfo);
	ScreenFlipping();
}