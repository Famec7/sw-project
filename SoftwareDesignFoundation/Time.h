#pragma once

struct TimeStruct {
	double time;	// ������ �� �ð� ����
	double deltaTime;
};

extern TimeStruct Time;

void InitTime();
void UpdateTime();